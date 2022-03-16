#include "Room.h"

Room::Room(uint32_t room_id) : room_id(room_id) {}

void Room::join(std::shared_ptr<ServersideClientHandler> client) {
    clients[client->getAccount()->getId()] = client;
}

void Room::leave(std::shared_ptr<ServersideClientHandler> client) {
    clients.erase(client->getAccount()->getId());
}

void Room::broadcast(const Message& message) {
    for (auto client : clients) {
        client.second->sendRequest(dynamic_cast<const Request&>(message));
    }
}

uint32_t Room::getId() {
    return room_id;
}

std::shared_ptr<ServersideClientHandler> Room::getClient(uint32_t id) {
    return clients.at(id);
}

std::string Room::getHistory() {}

std::string Room::getClientsList() {}

void Room::saveHistory() {}
