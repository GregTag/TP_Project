#pragma once
#include "properties_decorator.hpp"

class TextDecorator : public PropertiesDecorator {
   public:
    TextDecorator(std::shared_ptr<Message> message, const std::string& text);
    virtual ~TextDecorator() = default;

    std::string getQuery() override;

   private:
    std::string text;
};
