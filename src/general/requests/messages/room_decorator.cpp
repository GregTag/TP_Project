#include "room_decorator.hpp"

RoomDecorator::RoomDecorator(std::shared_ptr<Message> message, size_t room)
        : PropertiesDecorator(message), room(room) {}

size_t RoomDecorator::getRoom() {
    return room;
}

std::string RoomDecorator::getQuery() {
    return wrapper->getQuery() + Request::separator +
           std::to_string(size_t(MessageProperties::Room)) + Request::separator +
           std::to_string(room);
}
