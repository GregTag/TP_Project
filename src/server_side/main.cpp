#include <iostream>

#include "log.hpp"
#include "server.hpp"

int main(int argc, char* argv[]) {
    DebugLogger::initialize("log.txt");
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <port> <path to rooms>\n";
        return 1;
    }

    std::vector<std::string> args(argc);
    for (char** it = argv; it != argv + argc; ++it) args.emplace_back(*it);

    boost::asio::io_context io;
    Server server(io, std::stoul(argv[1]), argv[2]);
}
