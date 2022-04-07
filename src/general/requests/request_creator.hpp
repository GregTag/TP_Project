#pragma once
#include "requests/messages/messages_facade.hpp"

class RequestCreator {
   public:
    RequestCreator() = default;

    std::shared_ptr<Message> createChatMessage(size_t room, const std::string& sender,
                                               const std::string& text);
    std::shared_ptr<Message> createInfoMessage(const std::string& text);
    std::shared_ptr<Message> createErrorMessage(const std::string& text);
    std::shared_ptr<Message> createJoinMessage(size_t room, const std::string& name);
    std::shared_ptr<Message> createLeaveMessage(size_t room, const std::string& name);

   private:
    MessagesFacade message_facade;
};
