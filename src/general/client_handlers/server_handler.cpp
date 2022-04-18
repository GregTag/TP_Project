#include "server_handler.hpp"

#include "requests/messages/private_decorator.hpp"
#include "requests/request.hpp"
#include "room.hpp"

ServersideHandler::ServersideHandler(std::shared_ptr<Socket> client, std::weak_ptr<Server> server)
        : AbstractHandler(client), server(server) {}

std::shared_ptr<Room> ServersideHandler::getRoom(size_t room_id) {
    return std::shared_ptr<Room>(rooms.at(room_id));
}

std::unordered_map<size_t, std::weak_ptr<Room>>& ServersideHandler::getRooms() {
    return rooms;
}

void ServersideHandler::onMessage(std::shared_ptr<Message> msg) {
    if (msg->getType() == MessageTypes::Join) {
        Logger::log() << "New member in room " << msg->getRoom() << std::endl;
        // But we have no rooms yet
    } else {
        getRoom(msg->getRoom())->broadcast(msg);
    }
}

void ServersideHandler::onPrivateMessage(std::shared_ptr<PrivateDecorator> msg) {
    getRoom(msg->getRoom())->getClient(msg->getAddressee())->sendRequest(msg);
}

void ServersideHandler::receive(std::shared_ptr<Request> request) {
    request->handle(std::static_pointer_cast<ServersideHandler>(shared_from_this()));
}
