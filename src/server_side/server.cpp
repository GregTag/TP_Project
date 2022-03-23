#include "server.hpp"

Server::Server(const std::string& host, size_t port, const std::string& path)
        : path_to_room_storage(path) {}

Server::~Server() {
    stopServer();
}

void Server::startListen() {}

std::shared_ptr<Room> Server::getRoom(size_t room_id) {
    return rooms.at(room_id);
}

std::shared_ptr<PermissionsBank> Server::getPermissonsBank() {
    return nullptr;
}

std::shared_ptr<Room> Server::createRoom(size_t room_id) {
    return rooms[room_id] =
                   std::make_shared<Room>(room_id, path_to_room_storage + std::to_string(room_id));
}

void Server::createClientHandler(std::shared_ptr<ServersideClientHandler> handler) {
    clients[handler->getAccount()->getId()] = handler;
}

void Server::serverBroadcast(const std::string& text) {}

void Server::stopServer() {}
