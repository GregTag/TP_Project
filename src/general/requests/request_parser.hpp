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
    MessagesFacade message_facade;
};
