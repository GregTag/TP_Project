#pragma once
#include "properties_decorator.hpp"

class PrivateDecorator : public PropertiesDecorator {
   public:
    PrivateDecorator(std::shared_ptr<Message> message, const std::string& addressee);
    virtual ~PrivateDecorator() = default;

    std::string getQuery() const override;
    void handle(std::shared_ptr<ServersideHandler> handler) override;
    void handle(std::shared_ptr<ClientsideHandler> handler) override;

    const std::string& getAddressee() const;

   private:
    std::string addressee;
};
