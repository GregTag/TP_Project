#include <vector>

#include "client_handlers/client_handler.hpp"
#include "console_renderer.hpp"
#include "log.hpp"

int main(int argc, char* argv[]) {
    DebugLogger::initialize("log_client.txt");

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <host IPv4> <port>\n";
        return 1;
    }

    std::vector<std::string> args;
    for (char** it = argv; it != argv + argc; ++it) args.emplace_back(*it);

    boost::asio::io_context io;
    std::shared_ptr<ClientsideHandler> client = std::make_shared<ClientsideHandler>(
            std::make_shared<Socket>(io.get_executor(), args[1], std::stoul(args[2])),
            std::make_shared<ConsoleRenderer>());
    Logger::log() << "Client created" << std::endl;
    client->startReceiving();

    io.run();
}
