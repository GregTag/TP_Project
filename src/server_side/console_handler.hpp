#pragma once

#include <iostream>

#include "permissions.hpp"
#include "server.hpp"

class ConsoleHandler {
   public:
    ConsoleHandler(std::shared_ptr<Server>);

    void start();

   private:
    void helpCommand();
    void broadcastCommand();
    void accountCommand();
    void permissionCommand();

    std::shared_ptr<Server> server;
};
