#include "properties_decorator.hpp"

PropertiesDecorator::PropertiesDecorator(std::shared_ptr<Message> message) : wrapper(message) {}

size_t PropertiesDecorator::getRoom() const {
    return wrapper->getRoom();
}

std::string PropertiesDecorator::getQuery() const {
    return wrapper->getQuery();
}

void PropertiesDecorator::handle(std::shared_ptr<ServersideClientHandler> handler) {
    return wrapper->handle(handler);
}

void PropertiesDecorator::handle(std::shared_ptr<ClientsideHandler> handler) {
    return wrapper->handle(handler);
}
