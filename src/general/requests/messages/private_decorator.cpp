#include "private_decorator.hpp"

PrivateDecorator::PrivateDecorator(std::shared_ptr<Message> message, size_t addressee_id)
        : PropertiesDecorator(message), addressee_id(addressee_id) {}

std::string PrivateDecorator::getQuery() const {
    return wrapper->getQuery() + std::to_string(size_t(MessageProperties::Private)) +
           Request::separator + std::to_string(addressee_id) + Request::separator;
}

void PrivateDecorator::handle(std::shared_ptr<ServersideClientHandler> handler) {
    handler->getRoom(wrapper->getRoom())->getClient(addressee_id)->sendRequest(shared_from_this());
}

void PrivateDecorator::handle(std::shared_ptr<ClientsideHandler> handler) {
    handler->getRenderer()->privateRender(std::static_pointer_cast<Message>(shared_from_this()));
    PropertiesDecorator::handle(handler);
}

size_t PrivateDecorator::getAddressee() const {
    return addressee_id;
}
