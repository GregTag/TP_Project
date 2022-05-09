#pragma once
#include "message.hpp"

class BaseMessage : public Message {
   public:
    explicit BaseMessage(MessageTypes type);
    virtual ~BaseMessage() = default;

    size_t getRoom() const override;
    MessageTypes getType() const override;
    std::string getQuery() const override;
    void handle(std::shared_ptr<ServersideHandler> handler) override;
    void handle(std::shared_ptr<ClientsideHandler> handler) override;

   private:
    MessageTypes type;
};
