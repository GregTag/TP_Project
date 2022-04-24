#include "console_handler.hpp"

ConsoleHandler::ConsoleHandler(std::shared_ptr<ClientsideHandler> client)
        : client(client), running(true) {}

void ConsoleHandler::start() {
    std::string command;
    while (running) {
        std::cin >> command;
        if (std::cin.eof()) break;
        if (command == "register" || command == "signup") {
            singUpCommand();
        } else if (command == "login" || command == "signin") {
            signInCommand();
        } else if (command == "join") {
            joinCommand();
        } else if (command == "leave") {
            leaveCommand();
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

void ConsoleHandler::joinCommand() {
    size_t room;
    std::cin >> room;
    client->join(room);
}

void ConsoleHandler::leaveCommand() {
    size_t room;
    std::cin >> room;
    client->leave(room);
}

void ConsoleHandler::singUpCommand() {
    std::string name, passw;
    std::cin >> name >> passw;
    client->signUp(name, passw);
}

void ConsoleHandler::signInCommand() {
    std::string name, passw;
    std::cin >> name >> passw;
    client->signIn(name, passw);
}
