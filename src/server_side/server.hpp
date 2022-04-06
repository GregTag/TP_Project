#pragma once
#include <list>

#include "client_handlers/server_handler.hpp"
#include "permissions.hpp"
#include "room.hpp"

class Server : public std::enable_shared_from_this<Server> {
   public:
    Server(boost::asio::io_context& io, size_t port, const std::string& path);
    ~Server();

    std::shared_ptr<Room> getRoom(size_t room_id);
    std::shared_ptr<Room> createRoom(size_t room_id);
    std::shared_ptr<PermissionsBank> getPermissonsBank();
    void createClientHandler(std::shared_ptr<ServersideClientHandler> handler);
    void serverBroadcast(const std::string& text);
    void stopServer();

   private:
    void startListen();

    tcp::acceptor acceptor;
    std::unordered_map<size_t, std::shared_ptr<Room>> rooms;
    std::list<std::shared_ptr<ServersideClientHandler>> anonymous;
    std::unordered_map<size_t, std::shared_ptr<ServersideClientHandler>> clients;
    std::shared_ptr<PermissionsBank> permissons_bank;

    const std::string path_to_room_storage;
};
