#include "properties_decorator.hpp"

PropertiesDecorator::PropertiesDecorator(std::shared_ptr<Message> message) : wrapper(message) {}

size_t PropertiesDecorator::getRoom() {
    return wrapper->getRoom();
}

std::string PropertiesDecorator::getQuery() {
    return wrapper->getQuery();
}

void PropertiesDecorator::handle(std::shared_ptr<ServersideClientHandler> handler) {
    return wrapper->handle(handler);
}

void PropertiesDecorator::handle(std::shared_ptr<ClientsideHandler> handler) {
    return wrapper->handle(handler);
}
