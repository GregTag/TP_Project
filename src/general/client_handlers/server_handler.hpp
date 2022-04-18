#pragma once
#include <unordered_map>

#include "abstract_handler.hpp"

class Room;
class Server;
class PrivateDecorator;

class ServersideHandler : public AbstractHandler {
   public:
    ServersideHandler(std::shared_ptr<Socket>, std::weak_ptr<Server>);
    virtual ~ServersideHandler() = default;

    std::shared_ptr<Room> getRoom(size_t);
    std::unordered_map<size_t, std::weak_ptr<Room>>& getRooms();

    void onMessage(std::shared_ptr<Message>);
    void onPrivateMessage(std::shared_ptr<PrivateDecorator>);

    void receive(std::shared_ptr<Request>) override;

   private:
    std::weak_ptr<Server> server;
    std::unordered_map<size_t, std::weak_ptr<Room>> rooms;
};
