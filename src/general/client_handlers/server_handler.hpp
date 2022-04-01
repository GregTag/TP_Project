#pragma once
#include <unordered_map>

#include "abstract_handler.hpp"

class Room;

class ServersideClientHandler : public AbstractClientHandler,
                                std::enable_shared_from_this<ServersideClientHandler> {
   public:
    ServersideClientHandler(std::shared_ptr<Socket>);
    virtual ~ServersideClientHandler() = default;

    std::shared_ptr<Room> getRoom(size_t);

    std::unordered_map<size_t, std::weak_ptr<Room>>& getRooms();

    void receive(std::shared_ptr<Request>) override;

   private:
    std::unordered_map<size_t, std::weak_ptr<Room>> rooms;
};
