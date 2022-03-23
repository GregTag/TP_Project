#pragma once
#include "properties_decorator.hpp"

class SenderDecorator : public PropertiesDecorator {
   public:
    SenderDecorator(std::shared_ptr<Message> message, const std::string& sender);
    virtual ~SenderDecorator() = default;

    std::string getQuery() override;

   private:
    std::string sender;
};
