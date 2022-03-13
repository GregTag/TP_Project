#pragma once;

#include <deque>
#include <list>

#include "Clients.h"

class Room {
   private:
    uint32_t room_id;
    std::list<std::shared_ptr<ClientHandler>> clients;
    std::deque<std::string> history;

   public:
    Room(uint32_t);
    ~Room();

    void join(std::shared_ptr<Account>);
    void leave(std::shared_ptr<Account>);
    void broadcast(std::shared_ptr<Message>);
    std::string getHistory();
    std::string getClients();
    void saveHistory();
};