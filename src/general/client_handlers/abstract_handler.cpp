#include "abstract_handler.hpp"

#include "requests/request_parser.hpp"

AbstractClientHandler::AbstractClientHandler(std::shared_ptr<Socket> connection)
        : socket(connection), account() {
            socket->setCallback([this](const std::string& data){

            });
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
