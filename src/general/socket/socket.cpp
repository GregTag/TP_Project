#include "socket.hpp"

#include <iostream>

Socket::Socket(boost::asio::io_context& io) : strand(boost::asio::make_strand(io)), socket(io) {}

Socket::Socket(boost::asio::io_context& io, const std::string& host, size_t port) : Socket(io) {
    connect(host, port);
}

Socket::Socket(Socket&& other) : strand(std::move(other.strand)), socket(std::move(other.socket)) {}

Socket::~Socket() {
    if (socket.is_open()) close();
}

void Socket::connect(const std::string& host, size_t port) {
    socket.connect(tcp::endpoint(boost::asio::ip::make_address(host), port));
}

tcp::socket& Socket::getSocket() {
    return socket;
}

void Socket::setCallback(const std::function<void(const std::string&)>& cb) {
    callback = cb;
}

void Socket::startCommunicate() {
    boost::asio::async_read_until(
            socket, buffer, '\n',
            boost::asio::bind_executor(
                    strand, [this](const boost::system::error_code& error, size_t size) {
                        if (!error) {
                            std::istream is(&buffer);
                            std::string line;
                            std::getline(is, line, '\n');
                            // Logger::log() << "Recieved: " << line << std::endl;
                            boost::asio::post(boost::asio::bind_executor(
                                    strand, [this, line = std::move(line)]() {
                                        callback(std::move(line));
                                    }));
                            startCommunicate();
                        } else if (error == boost::asio::error::eof) {
                            Logger::log() << "Closing connection." << std::endl;
                            boost::asio::post(boost::asio::bind_executor(
                                    strand, [this]() { callback(std::string("eof")); }));
                        } else {
                            Logger::err() << error.what() << std::endl;
                        }
                    }));
}

void Socket::send(const std::string& data) {
    // Logger::log() << "Sended: " << data << std::endl;
    boost::asio::async_write(
            socket, boost::asio::buffer(data + '\n'),
            boost::asio::bind_executor(strand,
                                       [](const boost::system::error_code& error, size_t size) {
                                           if (error) {
                                               Logger::err() << error.what() << std::endl;
                                           }
                                       }));
}

void Socket::close() {
    socket.close();
}
