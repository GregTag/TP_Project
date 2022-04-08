#include "properties_decorator.hpp"

PropertiesDecorator::PropertiesDecorator(std::shared_ptr<Message> message) : wrapper(message) {}

size_t PropertiesDecorator::getRoom() const {
    return wrapper->getRoom();
}

MessageTypes PropertiesDecorator::getType() const {
    return wrapper->getType();
}

std::string PropertiesDecorator::getQuery() const {
    return wrapper->getQuery();
}

void PropertiesDecorator::handle(std::shared_ptr<ServersideHandler> handler) {
    handler->onMessage(std::static_pointer_cast<Message>(shared_from_this()));
}

void PropertiesDecorator::handle(std::shared_ptr<ClientsideHandler> handler) {
    return wrapper->handle(handler);
}
