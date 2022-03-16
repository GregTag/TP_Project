#include "Room.h"

void Room::join(std::shared_ptr<ServersideClientHandler> client) {
    clients[client->getAccount()->getId()] = client;
}

void Room::leave(std::shared_ptr<ServersideClientHandler> client) {
    clients.erase(client->getAccount()->getId());
}

std::shared_ptr<ServersideClientHandler> Room::getClient(uint32_t id) {
    return clients.at(id);
}

void Room::broadcast(const Message& message) {
    for (auto client : clients) {
        client.second->sendRequest(dynamic_cast<const Request&>(message));
    }
}
