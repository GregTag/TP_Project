#pragma once

#include <filesystem>
#include <fstream>
#include <unordered_map>

#include "request_handlers/server_handler.hpp"
#include "requests/request_creator.hpp"

class Room {
   public:
    Room(size_t room_id, const std::filesystem::path& file);
    ~Room() = default;

    void join(std::shared_ptr<ServersideHandler> client);
    void leave(std::shared_ptr<ServersideHandler> client);
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
