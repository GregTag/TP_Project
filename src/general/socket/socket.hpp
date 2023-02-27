#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <functional>
#include <memory>
#include <string>

#include "log.hpp"

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
using ssl_socket = ssl::stream<tcp::socket>;

class Socket {
   public:
    Socket(boost::asio::io_context& io, ssl::context& context, ssl_socket::handshake_type type);
    Socket(boost::asio::io_context& io, ssl::context& context, ssl_socket::handshake_type type,
           const std::string& host, size_t port);

    Socket(Socket&&);
    Socket() = delete;
    Socket(const Socket&) = delete;

    ~Socket();

    void connect(const std::string& host, size_t port);
    tcp::socket& getSocket();
    void setCallback(const std::function<void(const std::string&)>& cb);

    void doHandshake();
    void startCommunicate();
    void send(const std::string& data);
    void close();

   private:
    boost::asio::strand<boost::asio::io_context::executor_type> strand;
    ssl_socket::handshake_type type;
    ssl_socket socket;
    std::function<void(std::string)> callback;
    boost::asio::streambuf buffer;
};
