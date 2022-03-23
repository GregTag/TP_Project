#include "base_message.hpp"

BaseMessage::BaseMessage(MessageTypes type) : type(type) {}

size_t BaseMessage::getRoom() {
    return 0;
}

std::string BaseMessage::getQuery() {
    return std::to_string(size_t(RequestTypes::CompoundMessage)) + Request::separator +
           std::to_string(size_t(MessageProperties::Type)) + Request::separator +
           std::to_string(size_t(type));
}
void BaseMessage::handle(std::shared_ptr<ServersideClientHandler> handler) {
    handler->getRoom(getRoom())->broadcast(std::static_pointer_cast<Message>(shared_from_this()));
}
void BaseMessage::handle(std::shared_ptr<ClientsideHandler> handler) {
    handler->renderMessage(std::static_pointer_cast<Message>(shared_from_this()));
}

MessageTypes BaseMessage::getType() {
    return type;
}