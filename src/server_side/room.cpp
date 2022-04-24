#include "room.hpp"

Room::Room(size_t room_id, const std::filesystem::path& file)
        : room_id(room_id), history(file, std::ios_base::out) {
    history.open(file, std::ios_base::in | std::ios_base::out | std::ios_base::app);
    Logger::log() << "in room ctor" << std::endl;
}

void Room::join(std::shared_ptr<ServersideHandler> client) {
    clients.emplace(client->getAccount()->getId(), client);
}

void Room::leave(std::shared_ptr<ServersideHandler> client) {
    clients.erase(client->getAccount()->getId());
}

void Room::broadcast(std::shared_ptr<Message> message) {
    for (auto& client : clients) {
        client.second.lock()->sendRequest(message);
    }
    writeToHistory(message);
}

size_t Room::getId() {
    return room_id;
}

std::shared_ptr<ServersideHandler> Room::getClient(size_t id) {
    auto found = clients.find(id);
    if (found == clients.end()) return nullptr;
    return found->second.lock();
}

std::string Room::getClientsList() {
    return "ClientList";
}

std::string Room::readHistory(size_t lines) {
    return "";
}

void Room::writeToHistory(std::shared_ptr<Message> message) {
    history << message->getQuery() << std::endl;
}
