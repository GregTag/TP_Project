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

std::shared_ptr<Message> RequestCreator::createUserListMessage(size_t room,
                                                               const std::string& list) {
    message_facade.createBase(MessageTypes::UserList).addRoom(room);
    if (!list.empty()) message_facade.addText(list);
    return message_facade.getResult();
}

std::shared_ptr<Message> RequestCreator::createHistoryMessage(size_t room) {
    return message_facade.createBase(MessageTypes::History).addRoom(room).getResult();
}

std::shared_ptr<Message> RequestCreator::createManageMessage(size_t room, const std::string& cmd) {
    return message_facade.createBase(MessageTypes::Manage).addRoom(room).addText(cmd).getResult();
}
