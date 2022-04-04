#include <iostream>
#include <list>
#include <thread>

#include "socket/socket.hpp"

class Server {
   public:
    Server(boost::asio::io_context& io, size_t port)
            : acceptor(io, tcp::endpoint(tcp::v4(), port)) {
        startListen();
    }

    ~Server() {
        stopServer();
    }

    void createClientHandler(std::shared_ptr<Socket> handler);
    void serverBroadcast(const std::string& text) {
        for (auto& handler : anonymous) {
            handler->send(text);
        }
    }
    void stopServer() {}

   private:
    void startListen();

    tcp::acceptor acceptor;
    std::list<std::shared_ptr<Socket>> anonymous;
};

void Server::startListen() {
    std::shared_ptr<Socket> connection = std::make_shared<Socket>(acceptor.get_executor());
    connection->setCallback([](const std::string& text) { std::cout << text << std::endl; });
    acceptor.async_accept(connection->getSocket(),
                          [this, connection](const boost::system::error_code& error) {
                              if (!error) {
                                  anonymous.push_back(connection);
                                  connection->startCommunicate();
                                  std::cout << "Connected!" << std::endl;
                              } else {
                                  std::cerr << error.what() << std::endl;
                              }
                              startListen();
                          });
}

int main() {
    boost::asio::io_context io_service;
    Server server(io_service, 1234);
    std::thread t([&io_service]() { io_service.run(); });
    std::string text;
    while (true) {
        std::cin >> text;
        server.serverBroadcast(text);
    }
    t.join();
}
