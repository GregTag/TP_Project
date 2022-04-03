#include "socket.hpp"

Socket::Socket(std::string host, size_t port) {
    bind(host, port);
}

void Socket::bind(std::string, size_t) {}

void Socket::listen() {}

std::shared_ptr<Socket> Socket::accept() {}

std::string Socket::recv() {}

void Socket::send(std::string data) {}

void Socket::close() {}
