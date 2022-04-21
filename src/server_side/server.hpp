#pragma once
#include <filesystem>
#include <list>

#include "database/simple_database.hpp"
#include "permissions.hpp"
#include "request_handlers/server_handler.hpp"
#include "requests/request_creator.hpp"
#include "room.hpp"

class Server : public std::enable_shared_from_this<Server> {
   public:
    Server(boost::asio::io_context& io, size_t port, const std::filesystem::path& path);
    ~Server();

    std::shared_ptr<Room> getRoom(size_t room_id);
    std::shared_ptr<Room> createRoom(size_t room_id);
    std::shared_ptr<PermissionsBank> getPermissonsBank();
    void registerClient(std::shared_ptr<ServersideHandler> handler);
    void eraseConnection(size_t);
    void serverBroadcast(const std::string& text);
    void stopServer();

   private:
    void startListen();

    const std::filesystem::path path_to_room_storage;
    bool running;
    tcp::acceptor acceptor;
    std::unordered_map<size_t, std::shared_ptr<Room>> rooms;
    std::unordered_map<size_t, std::shared_ptr<ServersideHandler>> connections;
    std::unordered_map<size_t, std::weak_ptr<ServersideHandler>> client_by_id;
    std::shared_ptr<PermissionsBank> permissons_bank;
    size_t last_connection;
};
