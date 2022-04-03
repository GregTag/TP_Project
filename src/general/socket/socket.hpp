#pragma once

#include <boost/asio.hpp>
#include <functional>
#include <memory>
#include <string>

using boost::asio::ip::tcp;

class Socket {
   public:
    Socket(const boost::asio::any_io_executor& io);
    Socket(const boost::asio::any_io_executor& io, const std::string& host, size_t port);

    Socket(Socket&&);
    Socket() = delete;
    Socket(const Socket&) = delete;

    ~Socket() = default;

    tcp::socket& getSocket() {
        return socket;
    }

    void setCallback(const std::function<void(const std::string&)>& cb) {
        callback = cb;
    }

    void startCommunicate();
    void send(const std::string& data);
    void close();

   private:
    tcp::socket socket;
    std::function<void(std::string)> callback;
    boost::asio::streambuf buffer;
};
