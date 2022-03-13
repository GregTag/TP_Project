#pragma once

#include "Account.h"
#include "Socket.h"

class ClientHandler;
class Client;

class Request {
    virtual std::string getQuery();
    virtual void handle(ClientHandler);
    virtual void handle(Client);
};

class AbstractClient {
   private:
    Socket socket;

   protected:
    Account account;

   public:
    AbstractClient(std::shared_ptr<Socket>);
    ~AbstractClient();

    std::shared_ptr<Account> getAccount();
    void receive(std::shared_ptr<Request>);
    void startReceiving();
};

class Room;

class ClientHandler : AbstractClient {
   private:
    std::vector<std::shared_ptr<Room>> rooms;

   public:
    ClientHandler(std::shared_ptr<Socket>);
    ~ClientHandler();
};

class Message;
class UserMessage;

class Client : AbstractClient {
   public:
    Client(const std::string& host, uint32_t port);
    ~Client();

    std::string prompt(const std::string&);
    void sign_in();
    void sign_up();
    void renderMessage(uint32_t, std::shared_ptr<Message>);
    std::fstream getHistory(uint32_t);
    std::vector<std::string> getUsers(uint32_t);
    void send(std::shared_ptr<UserMessage>);
    void sendPrivate(const std::string&, std::shared_ptr<UserMessage>);
};