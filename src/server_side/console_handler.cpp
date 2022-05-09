#include "console_handler.hpp"

ConsoleHandler::ConsoleHandler(std::shared_ptr<Server> server) : server(server) {}

void ConsoleHandler::start() {
    std::string command;
    while (server->isRunning()) {
        std::cin >> command;
        if (std::cin.eof()) break;
        if (command == "help") {
            helpCommand();
        } else if (command == "broadcast" || command == "say") {
            broadcastCommand();
        } else if (command == "account" || command == "db" || command == "database") {
            accountCommand();
        } else if (command == "permission" || command == "perm") {
            permissionCommand();
        } else if (command == "stop") {
            break;
        } else if (!command.empty()) {
            Logger::err() << "Unknown command. Type help for all available commands." << std::endl;
        }
    }
    if (server->isRunning()) {
        server->stopServer();
    }
}

void ConsoleHandler::helpCommand() {
    std::cout << "- help                              Print this.\n- broadcast/say <some text>     "
                 "    Send everyone info message with <some text>.\n- account/database/db "
                 "<subcommand>  Manage user's available rooms:\n    - get <name>                   "
                 "     get all avaialable rooms for user <name>,\n    - add <name> <room>          "
                 "       add <room> to user <name> to available rooms,\n    - remove <name> <room> "
                 "             remove <room> to user <name> to available rooms.\n- "
                 "permissions/perm <subcommand>     Manage user's permissions:\n    - get <room> "
                 "<name>                 get permissions user <name> in <room>,\n    - set <room> "
                 "<name> <permission>    set permissions user <name> in <room>,\n    - setdefault "
                 "<room> <permission>    set <permission> as default for <room>.\n- stop/Ctrl+D    "
                 "                   Save all data and safely stop the server."
              << std::endl;
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
        Logger::err() << "Wrong account's name." << std::endl;
    } else if (subcommand == "add") {
        std::cin >> room;
        account->getAvailableRooms().insert(room);
        server->relogin(account->getId());
    } else if (subcommand == "remove") {
        std::cin >> room;
        account->getAvailableRooms().erase(room);
        server->relogin(account->getId());
    } else if (subcommand == "get") {
        Logger::log() << "Available rooms: " << account->getRoomList() << std::endl;
    } else {
        Logger::err() << "Unknown subcommand." << std::endl;
    }
}

void ConsoleHandler::permissionCommand() {
    std::string subcommand;
    size_t room;
    typename PermissionsSet::Permission perm;

    std::cin >> subcommand >> room;
    if (subcommand == "setdefault") {
        std::cin >> perm;
        PermissionsBank::getInstance()->setDefault(room, perm);
        Logger::log() << "Success.";
        return;
    }

    std::string name;
    std::cin >> name;
    auto client = AccountsDatabase::getInstance()->findAccountByName(name);
    if (!client) {
        Logger::err() << "User with this name does not exist.";
        return;
    }

    if (subcommand == "get") {
        Logger::log() << "Permission: "
                      << PermissionsBank::getInstance()->get(room, client->getId()) << std::endl;
    } else if (subcommand == "set") {
        std::cin >> perm;
        PermissionsBank::getInstance()->set(room, client->getId(), perm);
        Logger::log() << "Success.";
    } else {
        Logger::err() << "Unknown subcommand." << std::endl;
    }
}
