#pragma once
#include <memory>
#include <string>

#include "request_handlers/client_handler.hpp"
#include "request_handlers/server_handler.hpp"

enum class RequestTypes { CompoundMessage, SignIn, SignUp };

class ServersideHandler;
class ClientsideHandler;

class Request : public std::enable_shared_from_this<Request> {
   public:
    static const char separator = 30;
    virtual std::string getQuery() const = 0;
    virtual void handle(std::shared_ptr<ServersideHandler>) = 0;
    virtual void handle(std::shared_ptr<ClientsideHandler>) = 0;
};
