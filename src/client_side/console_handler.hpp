#pragma once

#include <iostream>

#include "permissions.hpp"
#include "request_handlers/client_handler.hpp"

class ConsoleHandler {
   public:
    ConsoleHandler(std::shared_ptr<ClientsideHandler>);

    void start();
    void stop();

   private:
    void roomsCommand();
    void joinCommand();
    void leaveCommand();
    void usersCommand();
    void historyCommand();
    void singUpCommand();
    void signInCommand();
    void sendCommand();
    void privateSendCommand();
    void manageCommand();

    std::shared_ptr<ClientsideHandler> client;
    bool running;
};
