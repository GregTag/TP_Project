#include "socket.hpp"

#include <iostream>

Socket::Socket(const boost::asio::any_io_executor& io) : socket(io) {}

Socket::Socket(const boost::asio::any_io_executor& io, const std::string& host, size_t port)
        : socket(io) {
    connect(host, port);
}

Socket::Socket(Socket&& other) : socket(std::move(other.socket)) {}

void Socket::connect(const std::string& host, size_t port) {
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string(host), port));
}

void Socket::startCommunicate() {
    boost::asio::async_read_until(
            socket, buffer, '\n', [this](const boost::system::error_code& error, size_t size) {
                if (!error) {
                    std::istream is(&buffer);
                    std::string line;
                    std::getline(is, line, '\n');
                    boost::asio::post([this, line = std::move(line)]() { callback(line); });
                    startCommunicate();
                } else {
                    std::cerr << error.what() << std::endl;
                }
            });
}

void Socket::send(const std::string& data) {
    boost::asio::async_write(socket, boost::asio::buffer(data + '\n'),
                             [](const boost::system::error_code& error, size_t size) {
                                 if (error) {
                                     std::cerr << error.what() << std::endl;
                                 }
                                 std::cout << size << std::endl;
                             });
}

void Socket::close() {
    socket.close();
}
