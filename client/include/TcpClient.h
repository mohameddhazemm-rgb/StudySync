#pragma once
#include <boost/asio.hpp>
#include <string>
#include <thread>
#include <functional>
#include <queue>
#include <mutex>

// with much help from these sources
// https://stackoverflow.com/questions/77880466/boost-asio-async-client
// https://github.com/alejandrofsevilla/boost-tcp-server-client/blob/main/TcpClient.hpp
// also partly modified by chatgpt in the TcpClient constructor
class TcpClient {
public:
    // the callback is run when a string that ends in a \n is found
    using MessageHandler = std::function<void(const std::string&)>;

    TcpClient(const std::string& host, const std::string& port, MessageHandler handler);
    ~TcpClient();

    void send(const std::string& msg);
    bool isConnected() const;

private:
    void connect();
    void doRead();
    void doWrite();
    void checkReconnect();

    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::ip::tcp::resolver resolver_;
    boost::asio::steady_timer reconnect_timer_;
    std::thread io_thread_;

    std::string host_;
    std::string port_;
    MessageHandler on_message_;
    bool connected_ = false;

    boost::asio::streambuf read_buffer_;
    std::queue<std::string> write_queue_;
    std::mutex write_mutex_;
};