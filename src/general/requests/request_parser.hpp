#pragma once
#include <sstream>

#include "requests/authorization/sign_in_request.hpp"
#include "requests/authorization/sign_up_request.hpp"
#include "requests/messages/messages_facade.hpp"

class RequestParser {
   public:
    RequestParser() = default;

    std::shared_ptr<Request> parse(const std::string& data);

   private:
    size_t readSize();
    std::string readString();
    std::shared_ptr<Message> parseMessage();

    std::stringstream ss;
    MessagesFacade message_facade;
};
