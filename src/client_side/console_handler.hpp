#pragma once

#include <iostream>

#include "request_handlers/client_handler.hpp"

class ConsoleHandler {
   public:
    ConsoleHandler(std::shared_ptr<ClientsideHandler>);

    void start();
    void stop();

   private:
    void joinExecuted();
    // TODO: implement all remaining commands

    std::shared_ptr<ClientsideHandler> client;
    bool running;
};
