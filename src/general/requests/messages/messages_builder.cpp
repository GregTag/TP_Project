#include "messages_builder.hpp"

void MessagesBuilder::reset() {
    result = nullptr;
}

std::shared_ptr<Message> MessagesBuilder::getResult() {
    std::shared_ptr<Message> res = result;
    reset();
    return res;
}

MessagesBuilder& MessagesBuilder::createBase(MessageTypes type) {
    result = std::make_shared<BaseMessage>(type);
    return *this;
}

MessagesBuilder& MessagesBuilder::addTime() {
    result = std::make_shared<TimeDecorator>(result);
    return *this;
}

MessagesBuilder& MessagesBuilder::addTime(size_t ts) {
    result = std::make_shared<TimeDecorator>(result, ts);
    return *this;
}

MessagesBuilder& MessagesBuilder::addRoom(size_t room) {
    result = std::make_shared<RoomDecorator>(result, room);
    return *this;
}

MessagesBuilder& MessagesBuilder::addSender(const std::string& name) {
    result = std::make_shared<SenderDecorator>(result, name);
    return *this;
}

MessagesBuilder& MessagesBuilder::addText(const std::string& text) {
    result = std::make_shared<TextDecorator>(result, text);
    return *this;
}

MessagesBuilder& MessagesBuilder::makePrivate(size_t addressee) {
    result = std::make_shared<PrivateDecorator>(result, addressee);
    return *this;
}
