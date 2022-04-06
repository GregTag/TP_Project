#include "room_decorator.hpp"

RoomDecorator::RoomDecorator(std::shared_ptr<Message> message, size_t room)
        : PropertiesDecorator(message), room(room) {}

size_t RoomDecorator::getRoom() const {
    return room;
}

std::string RoomDecorator::getQuery() const {
    return wrapper->getQuery() + Request::separator +
           std::to_string(size_t(MessageProperties::Room)) + Request::separator +
           std::to_string(room);
}

void RoomDecorator::handle(std::shared_ptr<ClientsideHandler> handler) {
    handler->getRenderer()->roomRender(std::static_pointer_cast<Message>(shared_from_this()));
    PropertiesDecorator::handle(handler);
}
