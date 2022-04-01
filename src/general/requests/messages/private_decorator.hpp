#pragma once
#include "properties_decorator.hpp"
#include "room.hpp"

class PrivateDecorator : public PropertiesDecorator {
   public:
    PrivateDecorator(std::shared_ptr<Message> message, size_t addressee_id);
    virtual ~PrivateDecorator() = default;

    std::string getQuery() override;
    void handle(std::shared_ptr<ServersideClientHandler> handler) override;

   private:
    size_t addressee_id;
};
