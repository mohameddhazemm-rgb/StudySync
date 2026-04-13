#include "ConnectionManager.h"

ConnectionManager& ConnectionManager::getInstance() {
    static ConnectionManager instance;
    return instance;
}

void ConnectionManager::addConnection(int userId, std::shared_ptr<TcpConnection> conn) {
    std::lock_guard<std::mutex> lock(mutex_);
    connections_[userId] = conn;
}

void ConnectionManager::removeConnection(int userId) {
    std::lock_guard<std::mutex> lock(mutex_);
    connections_.erase(userId);
}

std::shared_ptr<TcpConnection> ConnectionManager::getConnection(int userId) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = connections_.find(userId);
    if (it != connections_.end())
        return it->second;
    return nullptr;
}