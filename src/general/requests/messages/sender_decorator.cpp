#include "sender_decorator.hpp"

SenderDecorator::SenderDecorator(std::shared_ptr<Message> message, const std::string& sender)
        : PropertiesDecorator(message), sender(sender) {}

std::string SenderDecorator::getQuery() const {
    return wrapper->getQuery() + Request::separator +
           std::to_string(size_t(MessageProperties::Sender)) + Request::separator + sender;
}

void SenderDecorator::handle(std::shared_ptr<ClientsideHandler> handler) {
    handler->getRenderer()->senderRender(std::static_pointer_cast<Message>(shared_from_this()));
    PropertiesDecorator::handle(handler);
}

const std::string SenderDecorator::getSender() const {
    return sender;
}
