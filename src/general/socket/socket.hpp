#pragma once

#include <boost/asio.hpp>
#include <functional>
#include <memory>
#include <string>

#include "log.hpp"

using boost::asio::ip::tcp;

class Socket {
   public:
    Socket(boost::asio::io_context& io);
    Socket(boost::asio::io_context& io, const std::string& host, size_t port);

    Socket(Socket&&);
    Socket() = delete;
    Socket(const Socket&) = delete;

    ~Socket();

    void connect(const std::string& host, size_t port);
    tcp::socket& getSocket();
    void setCallback(const std::function<void(const std::string&)>& cb);

    void startCommunicate();
    void send(const std::string& data);
    void close();

   private:
    boost::asio::strand<boost::asio::io_context::executor_type> strand;
    tcp::socket socket;
    std::function<void(std::string)> callback;
    boost::asio::streambuf buffer;
};
