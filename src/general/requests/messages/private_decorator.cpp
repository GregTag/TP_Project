#include "private_decorator.hpp"

PrivateDecorator::PrivateDecorator(std::shared_ptr<Message> message, const std::string& addressee)
        : PropertiesDecorator(message), addressee(addressee) {}

std::string PrivateDecorator::getQuery() const {
    return wrapper->getQuery() + std::to_string(size_t(MessageProperties::Private)) +
           Request::separator + addressee + Request::separator;
}

void PrivateDecorator::handle(std::shared_ptr<ServersideHandler> handler) {
    handler->onPrivateMessage(std::static_pointer_cast<PrivateDecorator>(shared_from_this()));
}

void PrivateDecorator::handle(std::shared_ptr<ClientsideHandler> handler) {
    handler->getRenderer()->privateRender(std::static_pointer_cast<Message>(shared_from_this()));
    PropertiesDecorator::handle(handler);
}

const std::string& PrivateDecorator::getAddressee() const {
    return addressee;
}
