#pragma once

#include <memory>
#include <string>

class Socket {
   public:
    Socket();
    Socket(std::string, size_t);

    ~Socket();

    void bind(std::string, size_t);
    void listen();
    std::shared_ptr<Socket> accept();
    std::string recv();
    void send(std::string data);
    void close();
};
