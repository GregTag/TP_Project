#pragma once

#include "Clients.h"

class Message : Request {};

class BaseMessage : Message {
   private:
    time_t timestamp;
    uint32_t room;

   public:
    explicit BaseMessage(uint32_t);
    std::string getQuery() override;
    void handle(ClientHandler) override;
    void handle(Client) override;
};

class InfoMessage : BaseMessage {
   private:
    std::string message;

   public:
    explicit InfoMessage(std::string);
    std::string getQuery() override;
    void handle(Client) override;
};

class UserMessage : BaseMessage {
   private:
    std::string sender;

   public:
    explicit UserMessage(std::string);
    std::string getQuery() override;
};

class TextMessage : UserMessage {
   private:
    std::string message;

   public:
    TextMessage(std::string sender, std::string message);
    std::string getQuery() override;
};

class ActionMessage : BaseMessage {
   protected:
    std::string actor;

   public:
    explicit ActionMessage(std::string actor);
};

class JoinMessage : ActionMessage {
   public:
    JoinMessage(std::string actor);
    std::string getQuery() override;
    void handle(Client) override;
};

class LeaveMessage : ActionMessage {
   public:
    LeaveMessage(std::string actor);
    std::string getQuery() override;
    void handle(Client) override;
};

class MessageDecorator : Message {
   private:
    std::shared_ptr<Message> wrappe;

   public:
    explicit MessageDecorator(std::shared_ptr<Message>);
    ~MessageDecorator() = default;
    std::string getQuery() override;
    void handle(ClientHandler) override;
    void handle(Client) override;
};

class PrivateDecorator : MessageDecorator {
   private:
    std::string addressee;

   public:
    PrivateDecorator(std::shared_ptr<Message>, std::string);
    std::string getQuery() override;
    void handle(ClientHandler) override;
};

class AuthorizationRequest : Request {
   protected:
    std::shared_ptr<Account> account;

   public:
    AuthorizationRequest(std::shared_ptr<Account> account);
};

class SignInRequest : AuthorizationRequest {
   public:
    SignInRequest(std::shared_ptr<Account>);
    std::string getQuery() override;
    void handle(ClientHandler) override;
    void handle(Client) override;
};

class SignUpRequest : AuthorizationRequest {
    SignUpRequest(std::shared_ptr<Account>);
    std::string getQuery() override;
    void handle(ClientHandler) override;
    void handle(Client) override;
};