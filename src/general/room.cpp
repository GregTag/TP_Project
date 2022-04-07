#include "room.hpp"

Room::Room(size_t room_id, const std::string& file) : room_id(room_id), history(file) {}

void Room::join(std::shared_ptr<ServersideClientHandler> client) {
    clients[client->getAccount()->getId()] = client;
}

void Room::leave(std::shared_ptr<ServersideClientHandler> client) {
    clients.erase(client->getAccount()->getId());
}

void Room::broadcast(std::shared_ptr<Message> message) {
    for (auto& client : clients) {
        client.second.lock()->sendRequest(std::static_pointer_cast<Request>(message));
    }
}

size_t Room::getId() {
    return room_id;
}

std::shared_ptr<ServersideClientHandler> Room::getClient(size_t id) {
    return clients.at(id).lock();
}

std::string Room::getClientsList() {
    return "ClientList";
}

std::string Room::readHistory(size_t lines) {
    return "";
}

void Room::writeToHistory(std::shared_ptr<Message> message) {
    history << message->getQuery() << '\n';
}
