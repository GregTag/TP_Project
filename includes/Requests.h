#pragma once

#include <time.h>

#include "Room.h"

class BaseMessage : public Message {
   private:
    time_t timestamp;
    uint32_t room;

   public:
    explicit BaseMessage(uint32_t room);
    virtual ~BaseMessage() = default;

    uint32_t getRoom() override;
    std::string getQuery() override;
    void handle(ServersideClientHandler&) override;
    void handle(ClientsideClientHandler&) override;
};

class InfoMessage : public BaseMessage {
   private:
    std::string text;

   public:
    InfoMessage(uint32_t room, const std::string& text);
    virtual ~InfoMessage() = default;

    std::string getQuery() override;
};

class TextMessage : public BaseMessage {
   private:
    std::string text;

   public:
    TextMessage(uint32_t room, const std::string& text);
    virtual ~TextMessage() = default;

    std::string getQuery() override;
};

class JoinMessage : public BaseMessage {
   public:
    explicit JoinMessage(uint32_t room);
    virtual ~JoinMessage() = default;

    std::string getQuery() override;
    void handle(ClientsideClientHandler&) override;
};

class LeaveMessage : public BaseMessage {
   public:
    explicit LeaveMessage(uint32_t room);
    virtual ~LeaveMessage() = default;

    std::string getQuery() override;
    void handle(ClientsideClientHandler&) override;
};

class MessageDecorator : public Message {
   protected:
    std::shared_ptr<Message> wrappe;

   public:
    explicit MessageDecorator(std::shared_ptr<Message> message);
    virtual ~MessageDecorator() = default;

    uint32_t getRoom() override;
    std::string getQuery() override;
    void handle(ServersideClientHandler&) override;
    void handle(ClientsideClientHandler&) override;
};

class SenderDecorator : public MessageDecorator {
   private:
    std::string sender;

   public:
    SenderDecorator(std::shared_ptr<Message> message, const std::string& sender);
    virtual ~SenderDecorator() = default;

    std::string getQuery() override;
};

class PrivateDecorator : public MessageDecorator {
   private:
    uint32_t addressee_id;

   public:
    PrivateDecorator(std::shared_ptr<Message> message, uint32_t);
    virtual ~PrivateDecorator() = default;

    std::string getQuery() override;
    void handle(ServersideClientHandler&) override;
};

class AuthorizationRequest : public Request {
   protected:
    std::string name;
    std::string password_hash;

   public:
    AuthorizationRequest(const std::string& name, const std::string& password_hash);
    virtual ~AuthorizationRequest() = default;
};

class SignInRequest : public AuthorizationRequest {
   public:
    explicit SignInRequest(std::shared_ptr<Account> account);
    virtual ~SignInRequest() = default;

    std::string getQuery() override;
    void handle(ServersideClientHandler&) override;
    void handle(ClientsideClientHandler&) override;
};

class SignUpRequest : public AuthorizationRequest {
    explicit SignUpRequest(std::shared_ptr<Account> account);
    virtual ~SignUpRequest() = default;

    std::string getQuery() override;
    void handle(ServersideClientHandler&) override;
    void handle(ClientsideClientHandler&) override;
};