#include "Clients.h"

AbstractClientHandler::AbstractClientHandler(std::shared_ptr<Socket> client)
        : socket(client), account() {}

std::shared_ptr<Account> AbstractClientHandler::getAccount() {
    return account;
}

// void AbstractClient::sendRequest(std::shared_ptr<Request> request) {}

ServersideClientHandler::ServersideClientHandler(std::shared_ptr<Socket> client)
        : AbstractClientHandler(client) {}

std::shared_ptr<Room> ServersideClientHandler::getRoom(uint32_t room_id) {
    return std::shared_ptr<Room>(rooms.at(room_id));
}

void ServersideClientHandler::receive(std::shared_ptr<Request> request) {
    request->handle(*this);
}

void ClientsideClientHandler::receive(std::shared_ptr<Request> request) {
    request->handle(*this);
}
