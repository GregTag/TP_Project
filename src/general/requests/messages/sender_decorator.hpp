#pragma once
#include "properties_decorator.hpp"

class SenderDecorator : public PropertiesDecorator {
   public:
    SenderDecorator(std::shared_ptr<Message> message, const std::string& sender);
    virtual ~SenderDecorator() = default;

    std::string getQuery() const override;
    void handle(std::shared_ptr<ClientsideHandler> handler) override;

    const std::string getSender() const;

   private:
    std::string sender;
};
