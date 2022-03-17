#include "Socket.h"

void Socket::bind(std::string, uint32_t) {}
void Socket::listen() {}
std::shared_ptr<Socket> Socket::accept() {
    return nullptr;
}
std::string Socket::recv() {
    return "data";
}
void Socket::send(std::string data) {}
void Socket::close() {}