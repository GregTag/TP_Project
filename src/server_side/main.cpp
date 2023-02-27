#include "console_handler.hpp"
#include "log.hpp"
#include "server.hpp"
#include "server_permissions.hpp"

int main(int argc, char* argv[]) {
    if (argc != 6) {
        std::cerr << "Usage: " << argv[0]
                  << " <port> <path/to/room_storage> <certificate.csr> "
                     "<private.key> <dhparam.pem>\n";
        return 1;
    }

    std::filesystem::path path_arg(argv[2]);
    ServerLogger::initialize(path_arg / "log_server.txt");
    SimpleDatabase::initialize(path_arg / "db.txt");
    ServerPermissionsBank::initialize(path_arg / "permissions.txt");

    boost::asio::io_context io;
    ssl::context ssl_context(ssl::context::sslv23);
    ssl_context.set_options(boost::asio::ssl::context::default_workarounds |
                            boost::asio::ssl::context::single_dh_use);
    ssl_context.set_default_verify_paths();
    ssl_context.use_certificate_chain_file(argv[3]);
    ssl_context.use_private_key_file(argv[4], ssl::context::pem);
    ssl_context.use_tmp_dh_file(argv[5]);

    auto server =
            std::make_shared<Server>(io, std::move(ssl_context), std::stoul(argv[1]), path_arg);

    Logger::log() << "Server initialized" << std::endl;

    auto command_handler = std::make_shared<ConsoleHandler>(server);

    std::thread thread([command_handler]() { command_handler->start(); });

    io.run();
    thread.join();
}
