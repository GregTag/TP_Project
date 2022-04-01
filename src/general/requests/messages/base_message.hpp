#pragma once
#include "message.hpp"
#include "room.hpp"

enum class MessageTypes { Chat, Info, Error, Join, Leave };

class BaseMessage : public Message {
   public:
    explicit BaseMessage(MessageTypes type);
    virtual ~BaseMessage() = default;

    size_t getRoom() override;
    std::string getQuery() override;
    void handle(std::shared_ptr<ServersideClientHandler> handler) override;
    void handle(std::shared_ptr<ClientsideHandler> handler) override;

    MessageTypes getType();

   private:
    MessageTypes type;
};
