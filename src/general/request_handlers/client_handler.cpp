#include "client_handler.hpp"

#include "requests/request_creator.hpp"

ClientsideHandler::ClientsideHandler(std::shared_ptr<Socket> socket,
                                     std::shared_ptr<MessageRenderer> renderer)
        : AbstractHandler(socket), renderer(renderer) {}

void ClientsideHandler::receive(std::shared_ptr<Request> request) {
    request->handle(std::static_pointer_cast<ClientsideHandler>(shared_from_this()));
}

void ClientsideHandler::signIn(const std::string& name, const std::string& password) {
    sendRequest(std::static_pointer_cast<Request>(
            std::make_shared<SignInRequest>(std::make_shared<Account>(0, name, password))));
}

void ClientsideHandler::signUp(const std::string& name, const std::string& password) {
    sendRequest(std::static_pointer_cast<Request>(
            std::make_shared<SignUpRequest>(std::make_shared<Account>(0, name, password))));
}

void ClientsideHandler::join(size_t room) {
    sendRequest(getCreator()->createJoinMessage(room, getAccount()->getName()));
}

void ClientsideHandler::leave(size_t room) {
    sendRequest(getCreator()->createLeaveMessage(room, getAccount()->getName()));
}

void ClientsideHandler::requestUserList(size_t room) {
    sendRequest(getCreator()->createUserListMessage(room));
}

void ClientsideHandler::requestHistory(size_t room) {
    sendRequest(getCreator()->createHistoryMessage(room));
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

void ClientsideHandler::sendPrivate(size_t room, const std::string& user, const std::string& text) {
    sendRequest(std::make_shared<PrivateDecorator>(
            getCreator()->createChatMessage(room, getAccount()->getName(), text), user));
}
