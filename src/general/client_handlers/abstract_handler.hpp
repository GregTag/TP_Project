#pragma once
#include <memory>

#include "account.hpp"
#include "socket/socket.hpp"

class Request;
class Message;
class RequestParser;
class RequestCreator;

class AbstractClientHandler : public std::enable_shared_from_this<AbstractClientHandler> {
   public:
    AbstractClientHandler(std::shared_ptr<Socket>);
    virtual ~AbstractClientHandler() = default;

    std::shared_ptr<RequestCreator> getCreator();
    std::shared_ptr<Account> getAccount();
    void setAccount(std::shared_ptr<Account>);

    void sendRequest(std::shared_ptr<Request>);
    void startReceiving();

    virtual void receive(std::shared_ptr<Request>) = 0;

   protected:
    std::shared_ptr<Account> account;

   private:
    std::shared_ptr<Socket> socket;
    std::shared_ptr<RequestParser> parser;
    std::shared_ptr<RequestCreator> creator;
};
