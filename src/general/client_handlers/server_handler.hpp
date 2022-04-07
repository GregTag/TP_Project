#pragma once
#include <unordered_map>

#include "abstract_handler.hpp"

class Room;
class Server;

class ServersideClientHandler : public AbstractClientHandler {
   public:
    ServersideClientHandler(std::shared_ptr<Socket>, std::weak_ptr<Server>);
    virtual ~ServersideClientHandler() = default;

    std::shared_ptr<Room> getRoom(size_t);

    std::unordered_map<size_t, std::weak_ptr<Room>>& getRooms();

    void receive(std::shared_ptr<Request>) override;

   private:
    std::weak_ptr<Server> server;
    std::unordered_map<size_t, std::weak_ptr<Room>> rooms;
};
