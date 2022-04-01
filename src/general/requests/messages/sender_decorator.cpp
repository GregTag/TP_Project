#include "sender_decorator.hpp"

SenderDecorator::SenderDecorator(std::shared_ptr<Message> message, const std::string& sender)
        : PropertiesDecorator(message), sender(sender) {}

std::string SenderDecorator::getQuery() {
    return wrapper->getQuery() + Request::separator +
           std::to_string(size_t(MessageProperties::Sender)) + Request::separator + sender;
}
