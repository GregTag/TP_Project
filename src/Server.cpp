#include "Server.h"

Server::Server(const std::string& host, uint32_t port) {}

Server::~Server() {
    stopServer();
}

void Server::startListen() {}

std::shared_ptr<Room> Server::getRoom(uint32_t room_id) {
    return rooms.at(room_id);
}

std::shared_ptr<PermissionsBank> Server::getPermissonsBank() {}

void Server::createRoom(std::shared_ptr<Room> room) {
    rooms[room->getId()] = room;
}

void Server::createClientHandler(std::shared_ptr<ServersideClientHandler> handler) {
    clients[handler->getAccount()->getId()] = handler;
}

void Server::serverBroadcast(const std::string& text) {}

void Server::stopServer() {}
