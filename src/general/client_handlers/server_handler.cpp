#include "server_handler.hpp"

#include "requests/request.hpp"

ServersideClientHandler::ServersideClientHandler(std::shared_ptr<Socket> client)
        : AbstractClientHandler(client) {}

std::shared_ptr<Room> ServersideClientHandler::getRoom(size_t room_id) {
    return std::shared_ptr<Room>(rooms.at(room_id));
}

std::unordered_map<size_t, std::weak_ptr<Room>>& ServersideClientHandler::getRooms() {
    return rooms;
}

void ServersideClientHandler::receive(std::shared_ptr<Request> request) {
    request->handle(shared_from_this());
}