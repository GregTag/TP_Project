#pragma once

#include <time.h>

#include "Room.h"

enum class MessageProperties { Type, Time, Room, Sender, Text, Private };

enum class RequestTypes { Common, Info, Error, Join, Leave, SignIn, SignUp };

class BaseMessage : public Message {
   private:
    RequestTypes type;

   public:
    explicit BaseMessage(RequestTypes type);
    virtual ~BaseMessage() = default;

    uint32_t getRoom() override;
    std::string getQuery() override;
    void handle(ServersideClientHandler& handler) override;
    void handle(ClientsideClientHandler& handler) override;

    RequestTypes getType();
};

class PropertiesDecorator : public Message {
   protected:
    std::shared_ptr<Message> wrappe;

   public:
    explicit PropertiesDecorator(std::shared_ptr<Message> message);
    virtual ~PropertiesDecorator() = default;

    uint32_t getRoom() override;
    std::string getQuery() override;
    void handle(ServersideClientHandler& handler) override;
    void handle(ClientsideClientHandler& handler) override;
};

class TimeDecorator : public PropertiesDecorator {
   private:
    time_t timestamp;

   public:
    TimeDecorator(std::shared_ptr<Message> message, time_t timestamp);
    virtual ~TimeDecorator() = default;

    std::string getQuery() override;
};

class RoomDecorator : public PropertiesDecorator {
   private:
    uint32_t room;

   public:
    RoomDecorator(std::shared_ptr<Message> message, uint32_t room);
    virtual ~RoomDecorator() = default;

    uint32_t getRoom() override;
    std::string getQuery() override;
};

class SenderDecorator : public PropertiesDecorator {
   private:
    std::string sender;

   public:
    SenderDecorator(std::shared_ptr<Message> message, const std::string& sender);
    virtual ~SenderDecorator() = default;

    std::string getQuery() override;
};

class TextDecorator : public PropertiesDecorator {
   private:
    std::string text;

   public:
    TextDecorator(std::shared_ptr<Message> message, const std::string& text);
    virtual ~TextDecorator() = default;

    std::string getQuery() override;
};

class PrivateDecorator : public PropertiesDecorator {
   private:
    uint32_t addressee_id;

   public:
    PrivateDecorator(std::shared_ptr<Message> message, uint32_t addressee_id);
    virtual ~PrivateDecorator() = default;

    std::string getQuery() override;
    void handle(ServersideClientHandler& handler) override;
};

class AuthorizationRequest : public Request {
   protected:
    std::shared_ptr<Account> account;

   public:
    AuthorizationRequest(const std::string& name, const std::string& password_hash);
    virtual ~AuthorizationRequest() = default;

    std::string getQuery() override;
};

class SignInRequest : public AuthorizationRequest {
   public:
    explicit SignInRequest(const std::string& name, const std::string& password_hash);
    virtual ~SignInRequest() = default;

    std::string getQuery() override;
    void handle(ServersideClientHandler& handler) override;
    void handle(ClientsideClientHandler& handler) override;
};

class SignUpRequest : public AuthorizationRequest {
    explicit SignUpRequest(const std::string& name, const std::string& password_hash);
    virtual ~SignUpRequest() = default;

    std::string getQuery() override;
    void handle(ServersideClientHandler& handler) override;
    void handle(ClientsideClientHandler& handler) override;
};