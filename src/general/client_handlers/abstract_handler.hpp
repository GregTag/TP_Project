#pragma once
#include <memory>

#include "account.hpp"
#include "socket.hpp"

class Request;
class Message;

class AbstractClientHandler {
   public:
    AbstractClientHandler(std::shared_ptr<Socket>);
    AbstractClientHandler(const std::string& host, size_t port);
    virtual ~AbstractClientHandler() = default;

    std::shared_ptr<Account> getAccount();
    void setAccount(std::shared_ptr<Account>);

    void sendRequest(std::shared_ptr<Request>);
    void startReceiving();

    virtual void receive(std::shared_ptr<Request>) = 0;

   private:
    std::shared_ptr<Socket> socket;

   protected:
    std::shared_ptr<Account> account;
};
