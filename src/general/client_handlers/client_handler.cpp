#include "client_handler.hpp"

#include "requests/request_creators.hpp"

ClientsideHandler::ClientsideHandler(std::shared_ptr<Socket> socket,
                                     std::shared_ptr<MessageRenderer> renderer)
        : AbstractClientHandler(socket), renderer(renderer) {}

void ClientsideHandler::receive(std::shared_ptr<Request> request) {
    request->handle(shared_from_this());
}

void ClientsideHandler::signIn(const std::string& name, const std::string& password) {}

void ClientsideHandler::signUp(const std::string& name, const std::string& password) {}

std::string ClientsideHandler::getHistory(size_t) {
    return "history";
}

std::shared_ptr<std::vector<std::pair<size_t, std::string>>> ClientsideHandler::getUsers(
        size_t room) {
    return nullptr;
}

std::shared_ptr<MessageRenderer> ClientsideHandler::getRenderer() {
    return renderer;
}

void ClientsideHandler::send(size_t room, const std::string& text) {}

void ClientsideHandler::sendPrivate(size_t room, size_t user, const std::string& text) {}
