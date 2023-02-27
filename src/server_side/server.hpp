#pragma once
#include <filesystem>
#include <list>

#include "database/simple_database.hpp"
#include "request_handlers/server_handler.hpp"
#include "requests/request_creator.hpp"
#include "room.hpp"

class Server : public std::enable_shared_from_this<Server> {
   public:
    Server(boost::asio::io_context& io, ssl::context&& ssl_context, size_t port,
           const std::filesystem::path& path);
    ~Server();

    std::shared_ptr<Room> getRoom(size_t room_id);
    std::shared_ptr<Room> getOrCreateRoom(size_t room_id);
    bool registerClient(size_t id, std::shared_ptr<ServersideHandler> handler);
    void relogin(size_t id);
    void eraseConnection(size_t);
    void serverBroadcast(const std::string& text);
    void stopServer();
    bool isRunning();

   private:
    void startListen();

    const std::filesystem::path path_to_rooms;
    bool running;
    boost::asio::io_context& io;
    ssl::context ssl_context;
    tcp::acceptor acceptor;
    std::unordered_map<size_t, std::shared_ptr<Room>> rooms;
    std::unordered_map<size_t, std::shared_ptr<ServersideHandler>> connections;
    std::unordered_map<size_t, std::weak_ptr<ServersideHandler>> client_by_id;
    size_t last_connection;
};
