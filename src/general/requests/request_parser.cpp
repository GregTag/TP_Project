#include "request_parser.hpp"

std::shared_ptr<Request> RequestParser::parse(std::string data) {
    data.pop_back();
    ss = std::stringstream(data);
    RequestTypes request_type = RequestTypes(readNumber());
    std::string arg1;
    switch (request_type) {
        case RequestTypes::CompoundMessage:
            return parseMessage();
        case RequestTypes::SignIn:
            arg1 = readString();
            return std::make_shared<SignInRequest>(arg1, readString());
        case RequestTypes::SignUp:
            arg1 = readString();
            return std::make_shared<SignUpRequest>(arg1, readString());
    }
    Logger::err() << "Invalid requqest type" << std::endl;
}

size_t RequestParser::readNumber() {
    try {
        return std::stoul(readString());
    } catch (const std::exception& e) {
        Logger::err() << e.what() << std::endl;
    }
}

std::string RequestParser::readString() {
    std::string field;
    std::getline(ss, field, Request::separator);
    return field;
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