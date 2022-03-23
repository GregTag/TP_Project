#include "abstract_handler.hpp"

#include "requests/request.hpp"

AbstractClientHandler::AbstractClientHandler(std::shared_ptr<Socket> client)
        : socket(client), account() {}

AbstractClientHandler::AbstractClientHandler(const std::string& host, size_t port)
        : AbstractClientHandler(std::make_shared<Socket>()) {
    socket->bind(host, port);
}

std::shared_ptr<Account> AbstractClientHandler::getAccount() {
    return account;
}

void AbstractClientHandler::setAccount(std::shared_ptr<Account> other) {
    account = other;
}

void AbstractClientHandler::sendRequest(std::shared_ptr<Request> request) {
    socket->send(request->getQuery());
}

void AbstractClientHandler::startReceiving() {}
