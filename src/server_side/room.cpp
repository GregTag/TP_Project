#include "room.hpp"

Room::Room(size_t room_id, const std::filesystem::path& file)
        : room_id(room_id)
        , output(file, std::ios_base::out | std::ios_base::app)
        , input(file, std::ios_base::in) {}

void Room::join(std::shared_ptr<ServersideHandler> client) {
    clients.emplace(client->getAccount()->getId(), client);
}

void Room::leave(std::shared_ptr<ServersideHandler> client) {
    clients.erase(client->getAccount()->getId());
}

void Room::broadcast(std::shared_ptr<Message> message) {
    for (auto& [id, client] : clients) {
        client.lock()->sendRequest(message);
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

std::string Room::getUsersList() {
    std::string res;
    for (auto& [id, weak] : clients) {
        if (weak.expired()) continue;
        res.append(weak.lock()->getAccount()->getName()).push_back(' ');
    }
    if (!res.empty()) res.pop_back();
    return res;
}

void Room::sendHistory(std::shared_ptr<ServersideHandler> handler) {
    input.clear();
    input.seekg(0, std::ios::beg);
    Logger::log() << "Inside sendHistory" << std::endl;
    std::string line;
    while (!input.eof()) {
        std::getline(input, line);
        Logger::log() << line << std::endl;
        if (!line.empty()) handler->sendRaw(line);
    }
}

void Room::writeToHistory(std::shared_ptr<Message> message) {
    output.clear();
    output << message->getQuery() << std::endl;
}
