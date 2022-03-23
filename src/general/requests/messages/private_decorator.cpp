#include "private_decorator.hpp"

PrivateDecorator::PrivateDecorator(std::shared_ptr<Message> message, size_t addressee_id)
        : PropertiesDecorator(message), addressee_id(addressee_id) {}

std::string PrivateDecorator::getQuery() {
    return wrapper->getQuery() + Request::separator +
           std::to_string(size_t(MessageProperties::Private)) + Request::separator +
           std::to_string(addressee_id);
}

void PrivateDecorator::handle(std::shared_ptr<ServersideClientHandler> handler) {
    handler->getRoom(wrapper->getRoom())->getClient(addressee_id)->sendRequest(shared_from_this());
}