#pragma once
#include "properties_decorator.hpp"

class RoomDecorator : public PropertiesDecorator {
   public:
    RoomDecorator(std::shared_ptr<Message> message, size_t room);
    virtual ~RoomDecorator() = default;

    size_t getRoom() override;
    std::string getQuery() override;

   private:
    size_t room;
};
