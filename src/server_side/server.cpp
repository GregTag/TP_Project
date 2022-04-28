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

std::shared_ptr<Room> Server::getOrCreateRoom(size_t room_id) {
    auto room = getRoom(room_id);
    if (room) return room;
    return rooms
            .emplace(room_id,
                     std::make_shared<Room>(room_id, path_to_rooms / std::to_string(room_id)))
            .first->second;
}

bool Server::registerClient(size_t id, std::shared_ptr<ServersideHandler> handler) {
    return client_by_id.emplace(id, handler).second;
}

void Server::relogin(size_t id) {
    Logger::log() << "In relogin with id " << id << std::endl;
    auto found = client_by_id.find(id);
    if (found == client_by_id.end()) {
        Logger::err() << "Client not found." << std::endl;
        return;
    }
    if (found->second.expired()) {
        Logger::err() << "Client expired." << std::endl;
        return;
    }
    auto handler = found->second.lock();
    handler->sendRequest(std::static_pointer_cast<Request>(
            std::make_shared<SignInRequest>(handler->getAccount())));
}

void Server::eraseConnection(size_t id) {
    auto found = connections.find(id);
    if (found == connections.end()) {
        Logger::err() << "Erasing a nonexistent connection." << std::endl;
        return;
    }

    size_t account_id = found->second->getAccount()->getId();
    if (account_id) client_by_id.erase(account_id);
    connections.erase(found);
}

void Server::serverBroadcast(const std::string& text) {
    for (auto con = connections.begin(); con != connections.end(); ++con) {
        con->second->sendRequest(con->second->getCreator()->createInfoMessage(text));
    }
}

void Server::stopServer() {
    if (!running) return;
    Logger::log() << "Stopping the server." << std::endl;
    running = false;
    acceptor.close();
    for (auto con = connections.begin(); con != connections.end(); ++con) {
        con->second->exit();
    }
    connections.clear();
}

bool Server::isRunning() {
    return running;
}
