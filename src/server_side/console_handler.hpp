#pragma once

#include <iostream>

#include "server.hpp"

class ConsoleHandler {
   public:
    ConsoleHandler(std::shared_ptr<Server>);

    void start();

   private:
    void broadcast();

    std::shared_ptr<Server> server;
};
