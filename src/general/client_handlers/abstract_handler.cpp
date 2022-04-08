#include "abstract_handler.hpp"

#include "requests/request_creator.hpp"
#include "requests/request_parser.hpp"

AbstractClientHandler::AbstractClientHandler(std::shared_ptr<Socket> connection)
        : account()
        , socket(connection)
        , parser(std::make_shared<RequestParser>())
        , creator(std::make_shared<RequestCreator>()) {
    socket->setCallback([this](const std::string& data) { receive(parser->parse(data)); });
}

std::shared_ptr<RequestCreator> AbstractClientHandler::getCreator() {
    return creator;
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

void AbstractClientHandler::startReceiving() {
    socket->startCommunicate();
}
