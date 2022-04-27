#include "console_handler.hpp"

ConsoleHandler::ConsoleHandler(std::shared_ptr<Server> server) : server(server) {}

void ConsoleHandler::start() {
    std::string command;
    while (server->isRunning()) {
        std::cin >> command;
        if (std::cin.eof()) break;
        if (command == "broadcast" || command == "say") {
            broadcast();
        } else if (command == "stop") {
            break;
        } else if (!command.empty()) {
            std::cout << "Unknown command." << std::endl;
        }
    }
    if (server->isRunning()) {
        server->stopServer();
    }
}

void ConsoleHandler::broadcast() {
    std::string text;
    std::getline(std::cin, text);
    server->serverBroadcast(text);
}
