#pragma once
#include "message.hpp"

class PropertiesDecorator : public Message {
   public:
    explicit PropertiesDecorator(std::shared_ptr<Message> message);
    virtual ~PropertiesDecorator() = default;

    size_t getRoom() const override;
    MessageTypes getType() const override;
    std::string getQuery() const override;
    void handle(std::shared_ptr<ServersideHandler> handler) override;
    void handle(std::shared_ptr<ClientsideHandler> handler) override;

   protected:
    std::shared_ptr<Message> wrapper;
};
