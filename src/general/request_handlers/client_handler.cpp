#include "client_handler.hpp"

#include "requests/request_creator.hpp"

ClientsideHandler::ClientsideHandler(std::shared_ptr<Socket> socket,
                                     std::shared_ptr<MessageRenderer> renderer)
        : AbstractHandler(socket), renderer(renderer) {}

void ClientsideHandler::receive(std::shared_ptr<Request> request) {
    request->handle(std::static_pointer_cast<ClientsideHandler>(shared_from_this()));
}

void ClientsideHandler::signIn(const std::string& name, const std::string& password) {}

void ClientsideHandler::signUp(const std::string& name, const std::string& password) {}

void ClientsideHandler::join(size_t room) {
    sendRequest(getCreator()->createJoinMessage(room, getAccount()->getName()));
}

std::shared_ptr<std::vector<std::pair<size_t, std::string>>> ClientsideHandler::getUsers(
        size_t room) {
    return nullptr;
}

std::shared_ptr<MessageRenderer> ClientsideHandler::getRenderer() {
    return renderer;
}

void ClientsideHandler::send(size_t room, const std::string& text) {
    sendRequest(getCreator()->createChatMessage(room, getAccount()->getName(), text));
}

void ClientsideHandler::sendPrivate(size_t room, size_t user, const std::string& text) {
    sendRequest(std::make_shared<PrivateDecorator>(
            getCreator()->createChatMessage(room, getAccount()->getName(), text), user));
}