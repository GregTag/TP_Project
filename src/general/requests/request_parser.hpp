#pragma once
#include <sstream>

#include "requests/authorization/sign_in_request.hpp"
#include "requests/authorization/sign_up_request.hpp"
#include "requests/messages/messages_builder.hpp"

class RequestParser {
   public:
    RequestParser() = default;
    ~RequestParser() = default;

    std::shared_ptr<Request> parse(std::string data);

   private:
    size_t readNumber();
    std::string readString();
    std::set<size_t> parseSet();
    std::shared_ptr<Account> parseAccount();
    std::shared_ptr<Message> parseMessage();

    std::stringstream ss;
    MessagesBuilder message_facade;
};
