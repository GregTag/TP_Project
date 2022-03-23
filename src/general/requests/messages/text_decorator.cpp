#include "text_decorator.hpp"

TextDecorator::TextDecorator(std::shared_ptr<Message> message, const std::string& text)
        : PropertiesDecorator(message), text(text) {}

std::string TextDecorator::getQuery() {
    return wrapper->getQuery() + Request::separator +
           std::to_string(size_t(MessageProperties::Text)) + Request::separator + text;
}
