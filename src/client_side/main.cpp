#include <vector>

#include "console_handler.hpp"
#include "console_renderer.hpp"
#include "log.hpp"

int main(int argc, char* argv[]) {
    DebugLogger::initialize("log_client.txt");

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <host IP> <port>\n";
        return 1;
    }

    std::vector<std::string> args;
    for (char** it = argv; it != argv + argc; ++it) args.emplace_back(*it);

    boost::asio::io_context io;
    auto client = std::make_shared<ClientsideHandler>(
            std::make_shared<Socket>(io, args[1], std::stoul(args[2])),
            std::make_shared<ConsoleRenderer>());
    Logger::log() << "Client created" << std::endl;
    client->startReceiving();

    auto command_handler = std::make_shared<ConsoleHandler>(client);

    std::thread t([command_handler]() { command_handler->start(); });

    io.run();
    command_handler->stop();
    t.join();
}
