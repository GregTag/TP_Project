#pragma once
#include <memory>

#include "account.hpp"
#include "socket/socket.hpp"

class Request;
class Message;
class RequestParser;
class RequestCreator;

class AbstractHandler : public std::enable_shared_from_this<AbstractHandler> {
   public:
    AbstractHandler(std::shared_ptr<Socket>);
    virtual ~AbstractHandler() = default;

    std::shared_ptr<RequestCreator> getCreator();
    std::shared_ptr<Account> getAccount();
    void setAccount(std::shared_ptr<Account>);

    void sendRequest(std::shared_ptr<Request>);
    void startReceiving();
    void exit();

    virtual void receive(std::shared_ptr<Request>) = 0;
    virtual void destroy();

   private:
    std::shared_ptr<Account> account;
    std::shared_ptr<Socket> socket;
    std::shared_ptr<RequestParser> parser;
    std::shared_ptr<RequestCreator> creator;
};
