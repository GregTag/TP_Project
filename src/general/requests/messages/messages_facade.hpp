#pragma once
#include "all_messages.hpp"

class MessagesFacade {
   public:
    void reset();
    std::shared_ptr<Message> getResult();

    MessagesFacade& createBase(MessageTypes);
    MessagesFacade& addTime();
    MessagesFacade& addTime(size_t ts);
    MessagesFacade& addRoom(size_t room);
    MessagesFacade& addSender(const std::string& name);
    MessagesFacade& addText(const std::string& text);
    MessagesFacade& makePrivate(size_t addressee);

   private:
    std::shared_ptr<Message> result;
};
