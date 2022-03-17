#pragma once

#include "Clients.h"

class Room {
   private:
    uint32_t room_id;
    std::unordered_map<uint32_t, std::shared_ptr<ServersideClientHandler>> clients;
    std::string history;

   public:
    Room(uint32_t room_id);
    ~Room();

    void join(std::shared_ptr<ServersideClientHandler>);
    void leave(std::shared_ptr<ServersideClientHandler>);
    void broadcast(const Message&);
    uint32_t getId();
    std::shared_ptr<ServersideClientHandler> getClient(uint32_t id);
    std::string getHistory();
    std::string getClientsList();
    void saveHistory();
};