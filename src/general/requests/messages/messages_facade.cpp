#include "messages_facade.hpp"

void MessagesFacade::reset() {
    result = nullptr;
}

std::shared_ptr<Message> MessagesFacade::getResult() {
    std::shared_ptr<Message> res = result;
    Logger::log() << res->getQuery() << std::endl;
    reset();
    return res;
}

MessagesFacade& MessagesFacade::createBase(MessageTypes type) {
    result = std::make_shared<BaseMessage>(type);
    return *this;
}

MessagesFacade& MessagesFacade::addTime() {
    result = std::make_shared<TimeDecorator>(result);
    return *this;
}

MessagesFacade& MessagesFacade::addTime(size_t ts) {
    result = std::make_shared<TimeDecorator>(result, ts);
    return *this;
}

MessagesFacade& MessagesFacade::addRoom(size_t room) {
    result = std::make_shared<RoomDecorator>(result, room);
    return *this;
}

MessagesFacade& MessagesFacade::addSender(const std::string& name) {
    result = std::make_shared<SenderDecorator>(result, name);
    return *this;
}

MessagesFacade& MessagesFacade::addText(const std::string& text) {
    result = std::make_shared<TextDecorator>(result, text);
    return *this;
}

MessagesFacade& MessagesFacade::makePrivate(size_t addressee) {
    result = std::make_shared<PrivateDecorator>(result, addressee);
    return *this;
}
