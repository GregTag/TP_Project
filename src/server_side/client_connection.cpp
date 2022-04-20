#include "client_connection.hpp"

ClientConnection::ClientConnection(size_t id, std::shared_ptr<Socket> socket,
                                   std::weak_ptr<Server> server)
        : ServersideHandler(socket), id(id), server(server) {}

ClientConnection::~ClientConnection() {}

std::shared_ptr<Room> ClientConnection::getRoom(size_t room_id) {
    try {
        return std::shared_ptr<Room>(rooms.at(room_id));
    } catch (std::exception& e) {
        Logger::err() << e.what() << std::endl;
    }
}

void ClientConnection::destroy() {
    if (server.expired()) {
        Logger::err() << "No server?" << std::endl;
        return;
    }
    // TODO: Add leaving from rooms.
    server.lock()->eraseConnection(id);
}

void ClientConnection::onSignUp(std::shared_ptr<SignUpRequest> request) {}

void ClientConnection::onSignIn(std::shared_ptr<SignInRequest> request) {}

void ClientConnection::onMessage(std::shared_ptr<Message> request) {}

void ClientConnection::onPrivateMessage(std::shared_ptr<PrivateDecorator> request) {}

// std::unordered_map<size_t, std::weak_ptr<Room>>& ServersideHandler::getRooms() {
//     return rooms;
// }

// void ServersideHandler::onMessage(std::shared_ptr<Message> msg) {
//     if (msg->getType() == MessageTypes::Join) {
//         Logger::log() << "New member in room " << msg->getRoom() << std::endl;
//         // But we have no rooms yet
//     } else {
//         getRoom(msg->getRoom())->broadcast(msg);
//     }
// }

// void ServersideHandler::onPrivateMessage(std::shared_ptr<PrivateDecorator> msg) {
//     getRoom(msg->getRoom())->getClient(msg->getAddressee())->sendRequest(msg);
// }
