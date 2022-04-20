#pragma once
#include "properties_decorator.hpp"

class PrivateDecorator : public PropertiesDecorator {
   public:
    PrivateDecorator(std::shared_ptr<Message> message, size_t addressee_id);
    virtual ~PrivateDecorator() = default;

    std::string getQuery() const override;
    void handle(std::shared_ptr<ServersideHandler> handler) override;
    void handle(std::shared_ptr<ClientsideHandler> handler) override;

    size_t getAddressee() const;

   private:
    size_t addressee_id;
};
