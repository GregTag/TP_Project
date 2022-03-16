#pragma once

#include "Clients.h"
#include "Permissions.h"
#include "Requests.h"
#include "Room.h"
#include "Socket.h"

class Server {
   private:
    std::shared_ptr<Socket> socket;
    std::unordered_map<uint32_t, std::shared_ptr<Room>> rooms;
    std::unordered_map<uint32_t, std::shared_ptr<ServersideClientHandler>> clients;
    std::shared_ptr<PermissionsBank> permissons_bank;

   public:
    Server(const std::string& host, uint32_t port);
    ~Server();

    void startListen();
    std::shared_ptr<Room> getRoom(uint32_t room_id);
    std::shared_ptr<PermissionsBank> getPermissonsBank();
    void createRoom(std::shared_ptr<Room> room);
    void createClientHandler(std::shared_ptr<ServersideClientHandler> handler);
    void serverBroadcast(const std::string& text);
    void stopServer();
};