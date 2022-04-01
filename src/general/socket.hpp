#pragma once

#include <memory>
#include <string>

class Socket {
   public:
    Socket() = default;
    Socket(std::string, size_t);

    ~Socket() = default;

    void bind(std::string, size_t);
    void listen();
    std::shared_ptr<Socket> accept();
    std::string recv();
    void send(std::string data);
    void close();
};
