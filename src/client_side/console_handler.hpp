#pragma once

#include <iostream>

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
    void singUpCommand();
    void signInCommand();
    void sendCommand();
    void privateSendCommand();

    std::shared_ptr<ClientsideHandler> client;
    bool running;
};
