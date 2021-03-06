#include "base_message.hpp"

BaseMessage::BaseMessage(MessageTypes type) : type(type) {}

size_t BaseMessage::getRoom() const {
    return 0;
}

MessageTypes BaseMessage::getType() const {
    return type;
}

std::string BaseMessage::getQuery() const {
    return std::to_string(size_t(RequestTypes::CompoundMessage)) + Request::separator +
           std::to_string(size_t(MessageProperties::Type)) + Request::separator +
           std::to_string(size_t(type)) + Request::separator;
}
void BaseMessage::handle(std::shared_ptr<ServersideHandler> handler) {
    handler->onMessage(std::static_pointer_cast<Message>(shared_from_this()));
}
void BaseMessage::handle(std::shared_ptr<ClientsideHandler> handler) {
    handler->getRenderer()->baseMessageRender(
            std::static_pointer_cast<Message>(shared_from_this()));
}
