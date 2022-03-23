#pragma once
#include "client_handlers/server_handler.hpp"
#include "permissions.hpp"
#include "room.hpp"

class Server {
   public:
    Server(const std::string& host, size_t port, const std::string& path);
    ~Server();

    void startListen();
    std::shared_ptr<Room> getRoom(size_t room_id);
    std::shared_ptr<Room> createRoom(size_t room_id);
    std::shared_ptr<PermissionsBank> getPermissonsBank();
    void createClientHandler(std::shared_ptr<ServersideClientHandler> handler);
    void serverBroadcast(const std::string& text);
    void stopServer();

   private:
    std::shared_ptr<Socket> socket;
    std::unordered_map<size_t, std::shared_ptr<Room>> rooms;
    std::unordered_map<size_t, std::shared_ptr<ServersideClientHandler>> clients;
    std::shared_ptr<PermissionsBank> permissons_bank;

    const std::string path_to_room_storage;
};
