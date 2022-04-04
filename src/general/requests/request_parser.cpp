#include "request_parser.hpp"

std::shared_ptr<Request> RequestParser::parse(const std::string& data) {
    ss = std::stringstream(data);
    RequestTypes request_type = RequestTypes(readSize());
    switch (request_type) {
        case RequestTypes::CompoundMessage:
            return parseMessage();
        case RequestTypes::SignIn:
            return std::make_shared<SignInRequest>(readString(), readString());

        case RequestTypes::SignUp:
            return std::make_shared<SignUpRequest>(readString(), readString());
    }
}

size_t RequestParser::readSize() {
    return std::stoul(readString());
}

std::string RequestParser::readString() {
    std::string field;
    std::getline(ss, field, Request::separator);
    return field;
}

std::shared_ptr<Message> RequestParser::parseMessage() {
    while (ss) {
        switch (MessageProperties(readSize())) {
            case MessageProperties::Type:
                message_facade.createBase(MessageTypes(readSize()));
                break;
            case MessageProperties::Time:
                message_facade.addTime(readSize());
                break;
            case MessageProperties::Room:
                message_facade.addRoom(readSize());
                break;
            case MessageProperties::Sender:
                message_facade.addSender(readString());
                break;
            case MessageProperties::Text:
                message_facade.addText(readString());
                break;
            case MessageProperties::Private:
                message_facade.makePrivate(readSize());
                break;
        }
    }
    return message_facade.getResult();
}