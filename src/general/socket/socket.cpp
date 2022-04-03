#include "socket.hpp"

Socket::Socket(const boost::asio::any_io_executor& io) : socket(io) {}

Socket::Socket(const boost::asio::any_io_executor& io, const std::string& host, size_t port)
        : socket(io) {}

Socket::Socket(Socket&& other) : socket(std::move(other.socket)) {}

void Socket::startCommunicate() {
    boost::asio::async_read_until(socket, buffer, '\n',
                                  [this](const boost::system::error_code& error, size_t size) {
                                      if (!error) {
                                          std::istream is(&buffer);
                                          std::string line;
                                          std::getline(is, line, '\n');
                                          // TODO: make it asynchronous
                                          callback(line);
                                          startCommunicate();
                                      }
                                  });
}

void Socket::send(const std::string& data) {
    boost::asio::async_write(socket, boost::asio::buffer(data + '\n'),
                             [](const boost::system::error_code& error, size_t size) {});
}

void Socket::close() {
    socket.close();
}
