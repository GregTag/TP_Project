#include "abstract_handler.hpp"

#include "requests/request_creator.hpp"
#include "requests/request_parser.hpp"

AbstractHandler::AbstractHandler(std::shared_ptr<Socket> connection)
        : account(std::make_shared<Account>())
        , socket(connection)
        , parser(std::make_shared<RequestParser>())
        , creator(std::make_shared<RequestCreator>()) {
    socket->setCallback([this](const std::string& data) {
        if (data != "eof") {
            receive(parser->parse(data));
        } else {
            destroy();
        }
    });
}

std::shared_ptr<RequestCreator> AbstractHandler::getCreator() {
    return creator;
}

std::shared_ptr<Account> AbstractHandler::getAccount() {
    return account;
}

void AbstractHandler::setAccount(std::shared_ptr<Account> other) {
    account = other;
}

void AbstractHandler::sendRaw(const std::string& data) {
    socket->send(data);
}

void AbstractHandler::sendRequest(std::shared_ptr<Request> request) {
    socket->send(request->getQuery());
}

void AbstractHandler::startReceiving() {
    socket->startCommunicate();
}

void AbstractHandler::exit() {
    socket->close();
}

void AbstractHandler::destroy() {}
