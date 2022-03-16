#pragma once

#include <unordered_map>

#include "Account.h"
#include "Socket.h"

class ServersideClientHandler;
class ClientsideClientHandler;

class Request {
   public:
    virtual std::string getQuery() = 0;
    virtual void handle(ServersideClientHandler&) = 0;
    virtual void handle(ClientsideClientHandler&) = 0;
};

class Message : public Request {
   public:
    virtual uint32_t getRoom() = 0;
};

class AbstractClientHandler {
   private:
    std::shared_ptr<Socket> socket;

   protected:
    std::shared_ptr<Account> account;

   public:
    AbstractClientHandler(std::shared_ptr<Socket>);
    virtual ~AbstractClientHandler() = default;

    std::shared_ptr<Account> getAccount();
    virtual void receive(std::shared_ptr<Request>) = 0;
    void sendRequest(const Request&);
    void startReceiving();
};

class Room;

class ServersideClientHandler : public AbstractClientHandler {
   private:
    std::unordered_map<uint32_t, std::weak_ptr<Room>> rooms;

   public:
    ServersideClientHandler(std::shared_ptr<Socket>);
    virtual ~ServersideClientHandler() = default;

    std::shared_ptr<Room> getRoom(uint32_t);
    void receive(std::shared_ptr<Request>) override;
};

class ClientsideClientHandler : public AbstractClientHandler {
   public:
    ClientsideClientHandler(const std::string& host, uint32_t port);
    virtual ~ClientsideClientHandler() = default;

    void receive(std::shared_ptr<Request>) override;

    void sign_in(const std::string& name, const std::string& password);
    void sign_up(const std::string& name, const std::string& password);
    std::fstream getHistory(uint32_t);
    std::shared_ptr<std::vector<std::pair<uint32_t, std::string>>> getUsers(uint32_t room);
    void send(uint32_t room, const std::string& text);
    void sendPrivate(uint32_t room, uint32_t user, const std::string& text);

    virtual void renderMessage(const Message&) = 0;
};