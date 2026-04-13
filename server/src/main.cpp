#include <iostream>
#include <TcpServer.h>
#include "Database.h"

void registerServerRoutes();
void startAutoRefreshTimer(boost::asio::io_context& io_context);
int main(int argc, char* argv[]) {
    std::cout << "Server Started..." << std::endl;
    try {
        Database::getInstance();
        std::cout << "Database initialized" << std::endl;
        registerServerRoutes();

        boost::asio::io_context io_context;
        TcpServer server(io_context, 8080);
        startAutoRefreshTimer(io_context);
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}