#include "Requests.h"

// BaseMessage
explicit BaseMessage::BaseMessage(uint32_t room) : timestamp(time(0)), room(room) {}

uint32_t BaseMessage::getRoom() {
    return room;
}

void BaseMessage::handle(ServersideClientHandler& client_handler) {
    client_handler.getRoom(room)->broadcast(*this);
}

void BaseMessage::handle(ClientsideClientHandler& client) {
    client.renderMessage(*this);
}

// InfoMessage
InfoMessage::InfoMessage(uint32_t room, const std::string& text) : BaseMessage(room), text(text) {}

// TextMessage
TextMessage::TextMessage(uint32_t room, const std::string& text) : BaseMessage(room), text(text) {}

// JoinMessage
JoinMessage::JoinMessage(uint32_t room) : BaseMessage(room) {}

// LeaveMessage
LeaveMessage::LeaveMessage(uint32_t room) : BaseMessage(room) {}

// MessageDecorator
explicit MessageDecorator::MessageDecorator(std::shared_ptr<Message> message) : wrappe(message) {}

uint32_t MessageDecorator::getRoom() {
    return wrappe->getRoom();
}

std::string MessageDecorator::getQuery() {
    return wrappe->getQuery();
}

void MessageDecorator::handle(ServersideClientHandler& client_handler) {
    wrappe->handle(client_handler);
}

void MessageDecorator::handle(ClientsideClientHandler& client) {
    wrappe->handle(client);
}

// SenderDecorator
SenderDecorator::SenderDecorator(std::shared_ptr<Message> message, const std::string& sender)
        : MessageDecorator(message), sender(sender) {}

// PrivateDecorator
PrivateDecorator::PrivateDecorator(std::shared_ptr<Message> message, uint32_t addressee_id)
        : MessageDecorator(message), addressee_id(addressee_id) {}

void PrivateDecorator::handle(ServersideClientHandler& client_handler) {
    client_handler.getRoom(wrappe->getRoom())->getClient(addressee_id)->sendRequest(*this);
}