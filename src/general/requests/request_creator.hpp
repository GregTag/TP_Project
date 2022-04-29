#pragma once
#include "requests/authorization/sign_in_request.hpp"
#include "requests/authorization/sign_up_request.hpp"
#include "requests/messages/messages_builder.hpp"

class RequestCreator {
   public:
    RequestCreator() = default;

    std::shared_ptr<Message> createChatMessage(size_t room, const std::string& sender,
                                               const std::string& text);
    std::shared_ptr<Message> createInfoMessage(const std::string& text);
    std::shared_ptr<Message> createErrorMessage(const std::string& text);
    std::shared_ptr<Message> createJoinMessage(size_t room, const std::string& name);
    std::shared_ptr<Message> createLeaveMessage(size_t room, const std::string& name);
    std::shared_ptr<Message> createUserListMessage(size_t room, const std::string& list = "");
    std::shared_ptr<Message> createHistoryMessage(size_t room);
    std::shared_ptr<Message> createManageMessage(size_t room, const std::string& cmd);

   private:
    MessagesBuilder message_facade;
};
