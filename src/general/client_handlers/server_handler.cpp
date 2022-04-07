#include "server_handler.hpp"

#include "requests/request.hpp"

ServersideClientHandler::ServersideClientHandler(std::shared_ptr<Socket> client,
                                                 std::weak_ptr<Server> server)
        : AbstractClientHandler(client), server(server) {}

std::shared_ptr<Room> ServersideClientHandler::getRoom(size_t room_id) {
    return std::shared_ptr<Room>(rooms.at(room_id));
}

std::unordered_map<size_t, std::weak_ptr<Room>>& ServersideClientHandler::getRooms() {
    return rooms;
}

void ServersideClientHandler::receive(std::shared_ptr<Request> request) {
    request->handle(std::static_pointer_cast<ServersideClientHandler>(shared_from_this()));
}
