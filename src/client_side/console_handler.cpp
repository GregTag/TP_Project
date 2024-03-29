#include "console_handler.hpp"

ConsoleHandler::ConsoleHandler(std::shared_ptr<ClientsideHandler> client)
        : client(client), running(true) {}

void ConsoleHandler::start() {
    std::string command;
    while (running) {
        std::cin >> command;
        if (std::cin.eof() || command == "exit" || command == "quit") {
            break;
        } else if (command == "help") {
            helpCommand();
        } else if (command == "register" || command == "signup") {
            singUpCommand();
        } else if (command == "login" || command == "signin") {
            signInCommand();
        } else if (command == "rooms") {
            roomsCommand();
        } else if (command == "join") {
            joinCommand();
        } else if (command == "leave") {
            leaveCommand();
        } else if (command == "users") {
            usersCommand();
        } else if (command == "history") {
            historyCommand();
        } else if (command == "send" || command == "s") {
            sendCommand();
        } else if (command == "whisper" || command == "w" || command == "tell") {
            privateSendCommand();
        } else if (command == "manage") {
            manageCommand();
        } else if (!command.empty()) {
            std::cout << "Unknown command. Type help for all avaialble commands." << std::endl;
        }
    }
    if (running) {
        running = false;
        client->exit();
    }
}

void ConsoleHandler::helpCommand() {
    std::cout << "- help                                      Print this.\n- register/signup "
                 "<name> <password>         Register account with <name> and <password>.\n- "
                 "login/signin  <name> <password>           Authorizate with account with <name> "
                 "and <password>.\n- rooms                                     Print available "
                 "rooms for you\n- join <room>                               Join to <room>.\n- "
                 "leave <room>                              Leave <room>.\n- users <room>          "
                 "                    Get all users, who are currently online in <room>.\n- "
                 "history <room>                            Get all messages in <room>.\n- send/s "
                 "<room> <some text>                 Send message with <some text> to <room>.\n- "
                 "whisper/tell/w <room> <name> <some text>  Send private message with <some text> "
                 "to user <name> in <room>.\n- manage <subcommand>                       Manage "
                 "user's permissions:\n    - get <room> <name>                         get "
                 "permissions user <name> in <room>,\n    - set <room> <name> <permission>         "
                 "   set permissions user <name> in <room>,\n    - setdefault <room> <permission>  "
                 "          set <permission> as default for <room>.\n- exit/quit/Ctrl+D            "
                 "              Close connection and exit from app."
              << std::endl;
}

void ConsoleHandler::stop() {
    if (running) {
        std::cout << "Server closed connection.\nYou can close a program." << std::endl;
        running = false;
        client->exit();
    }
}

void ConsoleHandler::roomsCommand() {
    std::string ans = client->getAccount()->getRoomList();
    if (ans.empty()) {
        std::cout << "There is no available rooms." << std::endl;
    } else {
        std::cout << "Available rooms: " << ans << std::endl;
    }
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

void ConsoleHandler::usersCommand() {
    size_t room;
    std::cin >> room;
    client->requestUserList(room);
}

void ConsoleHandler::historyCommand() {
    size_t room;
    std::cin >> room;
    client->requestHistory(room);
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

void ConsoleHandler::sendCommand() {
    size_t room;
    std::string text;
    std::cin >> room;
    std::getline(std::cin, text, '\n');
    client->send(room, text);
}

void ConsoleHandler::privateSendCommand() {
    size_t room;
    std::string user;
    std::string text;
    std::cin >> room >> user;
    std::getline(std::cin, text, '\n');
    client->sendPrivate(room, user, text);
}

void ConsoleHandler::manageCommand() {
    std::string subcommand;
    size_t room;
    std::string res;

    std::cin >> subcommand >> room;
    res.append(subcommand).push_back(' ');
    if (subcommand == "set" || subcommand == "get") {
        std::string user;
        std::cin >> user;
        res.append(user).push_back(' ');
    }
    if (subcommand == "set" || subcommand == "setdefault") {
        typename PermissionsSet::Permission perm;
        std::cin >> perm;
        res.append(std::to_string(perm)).push_back(' ');
    }
    res.pop_back();
    client->manage(room, res);
}
