#include "server.hpp"

Server::Server(boost::asio::io_context& io, size_t port, const std::string& path)
        : acceptor(io, tcp::endpoint(tcp::v4(), port)), path_to_room_storage(path) {
    startListen();
}

Server::~Server() {
    stopServer();
}

void Server::startListen() {
    std::shared_ptr<Socket> connection = std::make_shared<Socket>(acceptor.get_executor());
    acceptor.async_accept(connection->getSocket(), [this, connection](
                                                           const boost::system::error_code& error) {
        if (!error) {
            clients.push_back(std::make_shared<ServersideHandler>(connection, weak_from_this()));
            clients.back()->sendRequest(
                    clients.back()->getCreator()->createInfoMessage("Welcome!"));
            Logger::log() << "New connection" << std::endl;
        }
        startListen();
    });
}

std::shared_ptr<Room> Server::getRoom(size_t room_id) {
    return rooms.at(room_id);
}

std::shared_ptr<PermissionsBank> Server::getPermissonsBank() {
    return nullptr;
}

std::shared_ptr<Room> Server::createRoom(size_t room_id) {
    return rooms[room_id] =
                   std::make_shared<Room>(room_id, path_to_room_storage + std::to_string(room_id));
}

void Server::registerClient(std::shared_ptr<ServersideHandler> handler) {
    client_by_id.emplace(handler->getAccount()->getId(), handler);
}

void Server::serverBroadcast(const std::string& text) {
    for (auto& client : clients) {
        client->sendRequest(client->getCreator()->createInfoMessage(text));
    }
}

void Server::stopServer() {}
