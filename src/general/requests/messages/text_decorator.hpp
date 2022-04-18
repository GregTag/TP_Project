#pragma once
#include "properties_decorator.hpp"

class TextDecorator : public PropertiesDecorator {
   public:
    TextDecorator(std::shared_ptr<Message> message, const std::string& text);
    virtual ~TextDecorator() = default;

    std::string getQuery() const override;
    void handle(std::shared_ptr<ClientsideHandler> handler) override;

    const std::string& getText() const;

   private:
    std::string text;
};
