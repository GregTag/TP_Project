#pragma once
#include "all_messages.hpp"

class MessagesBuilder {
   public:
    void reset();
    std::shared_ptr<Message> getResult();

    MessagesBuilder& createBase(MessageTypes);
    MessagesBuilder& addTime();
    MessagesBuilder& addTime(size_t ts);
    MessagesBuilder& addRoom(size_t room);
    MessagesBuilder& addSender(const std::string& name);
    MessagesBuilder& addText(const std::string& text);
    MessagesBuilder& makePrivate(size_t addressee);

   private:
    std::shared_ptr<Message> result;
};
