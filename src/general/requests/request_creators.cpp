#include "request_creators.hpp"

std::shared_ptr<Message> RequestCreators::createChatMessage(size_t room, const std::string& sender,
                                                            const std::string& text) {
    return message_facade.createBase(MessageTypes::Chat)
            .addTime()
            .addRoom(room)
            .addSender(sender)
            .addText(text)
            .getResult();
}

std::shared_ptr<Message> RequestCreators::createInfoMessage(const std::string& text) {
    return message_facade.createBase(MessageTypes::Info).addTime().addText(text).getResult();
}

std::shared_ptr<Message> RequestCreators::createErrorMessage(const std::string& text) {
    return message_facade.createBase(MessageTypes::Error).addText(text).getResult();
}

std::shared_ptr<Message> RequestCreators::createJoinMessage(size_t room, const std::string& name) {
    return message_facade.createBase(MessageTypes::Join)
            .addTime()
            .addRoom(room)
            .addSender(name)
            .getResult();
}

std::shared_ptr<Message> RequestCreators::createLeaveMessage(size_t room, const std::string& name) {
    return message_facade.createBase(MessageTypes::Leave)
            .addTime()
            .addRoom(room)
            .addSender(name)
            .getResult();
}
