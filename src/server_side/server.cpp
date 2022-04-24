#include "server.hpp"

#include "client_connection.hpp"

Server::Server(boost::asio::io_context& io, size_t port, const std::filesystem::path& path)
        : path_to_rooms(path), running(true), acceptor(io, tcp::endpoint(tcp::v4(), port)) {
    startListen();
}

Server::~Server() {
    stopServer();
}

void Server::startListen() {
    std::shared_ptr<Socket> socket = std::make_shared<Socket>(acceptor.get_executor());
    acceptor.async_accept(
            socket->getSocket(), [this, socket](const boost::system::error_code& error) {
                if (!error) {
                    auto client = std::make_shared<ClientConnection>(last_connection, socket,
                                                                     weak_from_this());
                    connections.emplace(last_connection,
                                        std::static_pointer_cast<ServersideHandler>(client));
                    ++last_connection;
                    client->sendRequest(client->getCreator()->createInfoMessage("Welcome!"));
                    Logger::log() << "New socket" << std::endl;
                    socket->startCommunicate();
                }
                if (running) startListen();
            });
}

std::shared_ptr<Room> Server::getRoom(size_t room_id) {
    auto found = rooms.find(room_id);
    if (found == rooms.end()) return nullptr;
    return found->second;
}

std::shared_ptr<PermissionsBank> Server::getPermissonsBank() {
    // TODO
    return nullptr;
}

std::shared_ptr<Room> Server::getOrCreateRoom(size_t room_id) {
    auto room = getRoom(room_id);
    if (room) return room;
    return rooms
            .emplace(room_id,
                     std::make_shared<Room>(room_id, path_to_rooms / std::to_string(room_id)))
            .first->second;
}

void Server::registerClient(std::shared_ptr<ServersideHandler> handler) {
    client_by_id.emplace(handler->getAccount()->getId(), handler);
}

void Server::eraseConnection(size_t id) {
    connections.erase(id);
}

void Server::serverBroadcast(const std::string& text) {
    for (auto con = connections.begin(); con != connections.end(); ++con) {
        con->second->sendRequest(con->second->getCreator()->createInfoMessage(text));
    }
}

void Server::stopServer() {
    Logger::log() << "Stopping the server." << std::endl;
    running = false;
    acceptor.close();
    for (auto con = connections.begin(); con != connections.end(); ++con) {
        con->second->exit();
    }
    connections.clear();
}
