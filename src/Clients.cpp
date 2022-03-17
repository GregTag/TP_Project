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
ClientsideHandler::ClientsideHandler(const std::string& host, uint32_t port)
        : AbstractClientHandler(std::make_shared<Socket>()) {}

void ClientsideHandler::receive(std::shared_ptr<Request> request) {
    request->handle(*this);
}

void ClientsideHandler::signIn(const std::string& name, const std::string& password) {}
void ClientsideHandler::signUp(const std::string& name, const std::string& password) {}
std::string ClientsideHandler::getHistory(uint32_t) {
    return "history";
}
std::shared_ptr<std::vector<std::pair<uint32_t, std::string>>> ClientsideHandler::getUsers(
        uint32_t room) {
    return nullptr;
}
void ClientsideHandler::send(uint32_t room, const std::string& text) {}
void ClientsideHandler::sendPrivate(uint32_t room, uint32_t user, const std::string& text) {}
