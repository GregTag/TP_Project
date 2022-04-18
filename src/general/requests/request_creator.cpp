#include "request_creator.hpp"

std::shared_ptr<Message> RequestCreator::createChatMessage(size_t room, const std::string& sender,
                                                           const std::string& text) {
    return message_facade.createBase(MessageTypes::Chat)
            .addTime()
            .addRoom(room)
            .addSender(sender)
            .addText(text)
            .getResult();
}

std::shared_ptr<Message> RequestCreator::createInfoMessage(const std::string& text) {
    return message_facade.createBase(MessageTypes::Info).addTime().addText(text).getResult();
}

std::shared_ptr<Message> RequestCreator::createErrorMessage(const std::string& text) {
    return message_facade.createBase(MessageTypes::Error).addText(text).getResult();
}

std::shared_ptr<Message> RequestCreator::createJoinMessage(size_t room, const std::string& name) {
    return message_facade.createBase(MessageTypes::Join)
            .addTime()
            .addRoom(room)
            .addSender(name)
            .getResult();
}

std::shared_ptr<Message> RequestCreator::createLeaveMessage(size_t room, const std::string& name) {
    return message_facade.createBase(MessageTypes::Leave)
            .addTime()
            .addRoom(room)
            .addSender(name)
            .getResult();
}
