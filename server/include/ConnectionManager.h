#pragma once
#include <unordered_map>
#include <memory>
#include <mutex>
#include "TcpServer.h"

class ConnectionManager {
public:
    static ConnectionManager& getInstance();

    void addConnection(int userId, std::shared_ptr<TcpConnection> conn);
    void removeConnection(int userId);
    std::shared_ptr<TcpConnection> getConnection(int userId);

private:
    ConnectionManager() = default;

    std::unordered_map<int, std::shared_ptr<TcpConnection>> connections_;
    std::mutex mutex_;
};