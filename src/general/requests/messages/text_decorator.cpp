#include "text_decorator.hpp"

TextDecorator::TextDecorator(std::shared_ptr<Message> message, const std::string& text)
        : PropertiesDecorator(message), text(text) {}

std::string TextDecorator::getQuery() const {
    return wrapper->getQuery() + Request::separator +
           std::to_string(size_t(MessageProperties::Text)) + Request::separator + text;
}

void TextDecorator::handle(std::shared_ptr<ClientsideHandler> handler) {
    handler->getRenderer()->textRender(std::static_pointer_cast<Message>(shared_from_this()));
    PropertiesDecorator::handle(handler);
}

const std::string& TextDecorator::getText() const {
    return text;
}
