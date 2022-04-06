#pragma once
#include "properties_decorator.hpp"

class RoomDecorator : public PropertiesDecorator {
   public:
    RoomDecorator(std::shared_ptr<Message> message, size_t room);
    virtual ~RoomDecorator() = default;

    size_t getRoom() const override;
    std::string getQuery() const override;
    void handle(std::shared_ptr<ClientsideHandler> handler) override;

   private:
    size_t room;
};
