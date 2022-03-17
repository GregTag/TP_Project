#include "Clients.h"

// AbstractClientHandler
AbstractClientHandler::AbstractClientHandler(std::shared_ptr<Socket> client)
        : socket(client), account() {}

std::shared_ptr<Account> AbstractClientHandler::getAccount() {
    return account;
}

void AbstractClientHandler::sendRequest(const Request&) {}

void AbstractClientHandler::startReceiving() {}

// ServersideClientHandler
ServersideClientHandler::ServersideClientHandler(std::shared_ptr<Socket> client)
        : AbstractClientHandler(client) {}

std::shared_ptr<Room> ServersideClientHandler::getRoom(uint32_t room_id) {
    return std::shared_ptr<Room>(rooms.at(room_id));
}

void ServersideClientHandler::receive(std::shared_ptr<Request> request) {
    request->handle(*this);
}

// ClientsideClientHandler
ClientsideClientHandler::ClientsideClientHandler(const std::string& host, uint32_t port)
        : AbstractClientHandler(std::make_shared<Socket>()) {}

void ClientsideClientHandler::receive(std::shared_ptr<Request> request) {
    request->handle(*this);
}

void ClientsideClientHandler::sign_in(const std::string& name, const std::string& password) {}
void ClientsideClientHandler::sign_up(const std::string& name, const std::string& password) {}
std::string ClientsideClientHandler::getHistory(uint32_t) {
    return "history";
}
std::shared_ptr<std::vector<std::pair<uint32_t, std::string>>> ClientsideClientHandler::getUsers(
        uint32_t room) {
    return nullptr;
}
void ClientsideClientHandler::send(uint32_t room, const std::string& text) {}
void ClientsideClientHandler::sendPrivate(uint32_t room, uint32_t user, const std::string& text) {}
