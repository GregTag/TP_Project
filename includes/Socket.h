#pragma once

#include <memory>
#include <string>

class Socket {
   private:
    std::string ip_address;
    uint32_t port;

   public:
    Socket();
    ~Socket() = default;

    void bind(std::string, uint32_t);
    void listen();
    std::shared_ptr<Socket> accept();
    std::string recv();
    void send(std::string data);
    void close();
};