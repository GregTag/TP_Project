#include "console_handler.hpp"

ConsoleHandler::ConsoleHandler(std::shared_ptr<Server> server) : server(server) {}

void ConsoleHandler::start() {
    std::string command;
    while (server->isRunning()) {
        std::cin >> command;
        if (std::cin.eof()) break;
        if (command == "broadcast" || command == "say") {
            broadcastCommand();
        } else if (command == "account" || command == "db" || command == "database") {
            accountCommand();
        } else if (command == "permission" || command == "perm") {
            permissionCommand();
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

void ConsoleHandler::broadcastCommand() {
    std::string text;
    std::getline(std::cin, text);
    server->serverBroadcast(text);
}

void ConsoleHandler::accountCommand() {
    std::string subcommand;
    std::string name;
    size_t room;

    std::cin >> subcommand >> name;
    auto account = AccountsDatabase::getInstance()->findAccountByName(name);
    if (!account) {
        std::cout << "Wrong account's name." << std::endl;
    } else if (subcommand == "add") {
        std::cin >> room;
        account->getAvailableRooms().insert(room);
        server->relogin(account->getId());
    } else if (subcommand == "remove") {
        std::cin >> room;
        account->getAvailableRooms().erase(room);
        server->relogin(account->getId());
    } else if (subcommand == "get") {
        std::cout << "Available rooms: " << account->getRoomList() << std::endl;
    } else {
        std::cout << "Unknown subcommand." << std::endl;
    }
}

void ConsoleHandler::permissionCommand() {
    std::string subcommand;
    size_t room;
    size_t client;
    typename PermissionsSet::Permission perm;

    std::cin >> subcommand >> room;
    if (subcommand == "get") {
        std::cin >> client;
        std::cout << PermissionsBank::getInstance()->get(room, client) << std::endl;
    } else if (subcommand == "set") {
        std::cin >> client >> perm;
        PermissionsBank::getInstance()->set(room, client, perm);
    } else if (subcommand == "setdefault") {
        std::cin >> perm;
        PermissionsBank::getInstance()->setDefault(room, perm);
    } else {
        std::cout << "Unknown subcommand." << std::endl;
    }
}
