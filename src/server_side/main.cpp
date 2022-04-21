#include "log.hpp"
#include "server.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <port> <path/to/room_storage>\n";
        return 1;
    }

    std::filesystem::path path_arg(argv[2]);
    ServerLogger::initialize(path_arg / "log_server.txt");
    SimpleDatabase::initialize(path_arg / "db.txt");

    boost::asio::io_context io;
    auto server = std::make_shared<Server>(io, std::stoul(argv[1]), path_arg);

    Logger::log() << "Server initialized" << std::endl;

    std::thread t([server]() {
        while (!std::cin.eof()) {
            std::cin.ignore(255, '\n');
        }
        server->stopServer();
    });
    io.run();
    t.join();
}
