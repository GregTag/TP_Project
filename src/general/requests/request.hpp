#pragma once
#include <memory>
#include <string>

#include "client_handlers/client_handler.hpp"
#include "client_handlers/server_handler.hpp"

enum class RequestTypes { CompoundMessage, SignIn, SignUp };

class ServersideClientHandler;
class ClientsideHandler;

class Request : public std::enable_shared_from_this<Request> {
   public:
    static const char separator = 1;
    virtual std::string getQuery() const = 0;
    virtual void handle(std::shared_ptr<ServersideClientHandler>) = 0;
    virtual void handle(std::shared_ptr<ClientsideHandler>) = 0;
};
