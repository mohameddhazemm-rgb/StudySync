#include "TcpClient.h"
#include <iostream>
#include <istream>

TcpClient::TcpClient(const std::string& host, const std::string& port, MessageHandler handler)
    : socket_(io_context_), resolver_(io_context_), reconnect_timer_(io_context_),
      host_(host), port_(port), on_message_(std::move(handler)) {
    
    connect();
    // based of chatgpt, run the io context on a seperate thread to not block the qt thread
    io_thread_ = std::thread([this]() { io_context_.run(); });
}

TcpClient::~TcpClient() {
    io_context_.stop();
    if (io_thread_.joinable()) io_thread_.join();
}

bool TcpClient::isConnected() const { return connected_; }

void TcpClient::send(const std::string& msg) {
    // ensure the message ends with a newline delimiter
    std::string formatted_msg = msg;
    if (formatted_msg.back() != '\n') formatted_msg += '\n';

    // push to the queueeu
    boost::asio::post(io_context_, [this, formatted_msg]() {
        bool write_in_progress = !write_queue_.empty();
        write_queue_.push(formatted_msg);
        if (!write_in_progress && connected_) {
            doWrite();
        }
    });
}

void TcpClient::connect() {
    std::cout << "connecting to " << host_ << ":" << port_ << std::endl;
    resolver_.async_resolve(host_, port_,
        [this](const boost::system::error_code& ec, boost::asio::ip::tcp::resolver::results_type results) {
            if (!ec) {
                boost::asio::async_connect(socket_, results,
                    [this](const boost::system::error_code& ec, const boost::asio::ip::tcp::endpoint& endpoint) {
                        if (!ec) {
                            std::cout << "connected successfully." << std::endl;
                            connected_ = true;
                            doRead();
                            if (!write_queue_.empty()) doWrite();
                        } else {
                            checkReconnect();
                        }
                    });
            } else {
                checkReconnect();
            }
        });
}

void TcpClient::checkReconnect() {
    connected_ = false;
    socket_.close();
    // reconnect every 3 seconds
    reconnect_timer_.expires_after(std::chrono::seconds(3));
    reconnect_timer_.async_wait([this](const boost::system::error_code& ec) {
        if (!ec) connect();
    });
}

void TcpClient::doRead() {
    // Read until a newline is found
    boost::asio::async_read_until(socket_, read_buffer_, '\n',
        [this](const boost::system::error_code& ec, std::size_t /*length*/) {
            if (!ec) {
                std::istream is(&read_buffer_);
                std::string message;
                std::getline(is, message); // extracts up to '\n'
                
                if (on_message_) on_message_(message);
                
                doRead(); // Queue the next read
            } else {
                std::cerr << "client disconnected: " << ec.message() << std::endl;
                checkReconnect();
            }
        });
}

void TcpClient::doWrite() {
    boost::asio::async_write(socket_,
        boost::asio::buffer(write_queue_.front()),
        [this](const boost::system::error_code& ec, std::size_t /*length*/) {
            if (!ec) {
                write_queue_.pop();
                if (!write_queue_.empty()) doWrite(); // write the next one
            } else {
                checkReconnect();
            }
        });
}