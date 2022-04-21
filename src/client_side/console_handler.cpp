#include "console_handler.hpp"

ConsoleHandler::ConsoleHandler(std::shared_ptr<ClientsideHandler> client)
        : client(client), running(true) {}

void ConsoleHandler::start() {
    std::string command;
    while (running) {
        std::cin >> command;
        if (std::cin.eof()) break;
        if (command == "join") {
            joinExecuted();
        } else if (!command.empty()) {
            std::cout << "Unknown command." << std::endl;
        }
    }
    if (running) {
        client->exit();
        running = false;
    }
}

void ConsoleHandler::stop() {
    if (running) {
        std::cout << "Server closed connection.\nYou can close a program." << std::endl;
    }
    running = false;
}

void ConsoleHandler::joinExecuted() {
    size_t room;
    std::cin >> room;
    client->join(room);
}
