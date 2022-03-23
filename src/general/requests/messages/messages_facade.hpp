#pragma once
#include "base_message.hpp"
#include "private_decorator.hpp"
#include "room_decorator.hpp"
#include "sender_decorator.hpp"
#include "text_decorator.hpp"
#include "time_decorator.hpp"

class MessagesFacade {
   public:
    void reset();
    std::shared_ptr<Message> getResult();

    MessagesFacade& createBase(MessageTypes);
    MessagesFacade& addTime();
    MessagesFacade& addRoom(size_t room);
    MessagesFacade& addSender(const std::string& name);
    MessagesFacade& addText(const std::string& text);
    MessagesFacade& makePrivate(size_t addressee);

   private:
    std::shared_ptr<Message> result;
};
