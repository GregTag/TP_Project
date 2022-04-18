#include <iostream>
#include <thread>

#include "socket/socket.hpp"

int main() {
    boost::asio::io_context io_service;
    Socket socket(io_service.get_executor(), "127.0.0.1", 1234);
    socket.setCallback([](const std::string& text) { std::cout << text << std::endl; });
    socket.startCommunicate();

    std::thread t([&io_service]() { io_service.run(); });

        std::string text;
    while (true) {
        std::cin >> text;
        socket.send(text);
    }
    t.join();
}