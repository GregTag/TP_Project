#include "request_parser.hpp"

std::shared_ptr<Request> RequestParser::parse(std::string data) {
    data.pop_back();
    ss = std::stringstream(data);
    RequestTypes request_type = RequestTypes(readNumber());
    switch (request_type) {
        case RequestTypes::CompoundMessage:
            return parseMessage();
        case RequestTypes::SignIn:
            return std::make_shared<SignInRequest>(parseAccount());
        case RequestTypes::SignUp:
            return std::make_shared<SignUpRequest>(parseAccount());
    }
    Logger::err() << "Invalid requqest type" << std::endl;
    return nullptr;
}

size_t RequestParser::readNumber() {
    return std::stoul(readString());
}

std::string RequestParser::readString() {
    std::string field;
    std::getline(ss, field, Request::separator);
    return field;
}

std::set<size_t> RequestParser::parseSet() {
    std::string line = readString();
    if (line.empty()) return std::set<size_t>();
    std::stringstream stream(line);
    std::set<size_t> res;
    size_t room;
    while (!stream.eof()) {
        stream >> room;
        res.insert(room);
    }
    return res;
}

std::shared_ptr<Account> RequestParser::parseAccount() {
    std::string name = readString();
    std::string passw = readString();
    std::set<size_t> rooms = parseSet();
    return std::make_shared<Account>(0, name, passw, rooms);
}

std::shared_ptr<Message> RequestParser::parseMessage() {
    while (!ss.eof()) {
        switch (MessageProperties(readNumber())) {
            case MessageProperties::Type:
                message_facade.createBase(MessageTypes(readNumber()));
                break;
            case MessageProperties::Time:
                message_facade.addTime(readNumber());
                break;
            case MessageProperties::Room:
                message_facade.addRoom(readNumber());
                break;
            case MessageProperties::Sender:
                message_facade.addSender(readString());
                break;
            case MessageProperties::Text:
                message_facade.addText(readString());
                break;
            case MessageProperties::Private:
                message_facade.makePrivate(readString());
                break;
        }
    }
    return message_facade.getResult();
}