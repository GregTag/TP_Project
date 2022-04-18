#pragma once

#include <fstream>
#include <unordered_map>

#include "client_handlers/server_handler.hpp"
#include "requests/messages/message.hpp"

class Room {
   public:
    Room(size_t room_id, const std::string& file);

    ~Room() = default;

    void join(std::shared_ptr<ServersideHandler>);
    void leave(std::shared_ptr<ServersideHandler>);
    void broadcast(std::shared_ptr<Message>);
    size_t getId();
    std::shared_ptr<ServersideHandler> getClient(size_t id);
    std::string getClientsList();
    std::string readHistory(size_t lines);
    void writeToHistory(std::shared_ptr<Message> message);

   private:
    size_t room_id;
    std::fstream history;
    std::unordered_map<size_t, std::weak_ptr<ServersideHandler>> clients;
};
