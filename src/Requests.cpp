#include "Requests.h"

// BaseMessage
BaseMessage::BaseMessage(MessageTypes type) : type(type) {}

uint32_t BaseMessage::getRoom() {
    return 0;
}

std::string BaseMessage::getQuery() {
    return std::to_string(uint32_t(RequestTypes::CompoundMessage)) + Request::separator +
           std::to_string(uint32_t(MessageProperties::Type)) + Request::separator +
           std::to_string(uint32_t(type));
}
void BaseMessage::handle(ServersideClientHandler& handler) {
    handler.getRoom(getRoom())->broadcast(*this);
}
void BaseMessage::handle(ClientsideHandler& handler) {
    handler.renderMessage(*this);
}

MessageTypes BaseMessage::getType() {
    return type;
}

// PropertiesDecorator
PropertiesDecorator::PropertiesDecorator(std::shared_ptr<Message> message) : wrappe(message) {}

uint32_t PropertiesDecorator::getRoom() {
    return wrappe->getRoom();
}

std::string PropertiesDecorator::getQuery() {
    return wrappe->getQuery();
}

void PropertiesDecorator::handle(ServersideClientHandler& handler) {
    return wrappe->handle(handler);
}

void PropertiesDecorator::handle(ClientsideHandler& handler) {
    return wrappe->handle(handler);
}

// TimeDecorator
TimeDecorator::TimeDecorator(std::shared_ptr<Message> message, time_t timestamp)
        : PropertiesDecorator(message), timestamp(timestamp) {}

std::string TimeDecorator::getQuery() {
    return wrappe->getQuery() + Request::separator +
           std::to_string(uint32_t(MessageProperties::Time)) + Request::separator +
           std::to_string(timestamp);
}

// RoomDecorator
RoomDecorator::RoomDecorator(std::shared_ptr<Message> message, uint32_t room)
        : PropertiesDecorator(message), room(room) {}

uint32_t RoomDecorator::getRoom() {
    return room;
}

std::string RoomDecorator::getQuery() {
    return wrappe->getQuery() + Request::separator +
           std::to_string(uint32_t(MessageProperties::Room)) + Request::separator +
           std::to_string(room);
}

// SenderDecorator
SenderDecorator::SenderDecorator(std::shared_ptr<Message> message, const std::string& sender)
        : PropertiesDecorator(message), sender(sender) {}

std::string SenderDecorator::getQuery() {
    return wrappe->getQuery() + Request::separator +
           std::to_string(uint32_t(MessageProperties::Sender)) + Request::separator + sender;
}

// TextDecorator
TextDecorator::TextDecorator(std::shared_ptr<Message> message, const std::string& text)
        : PropertiesDecorator(message), text(text) {}

std::string TextDecorator::getQuery() {
    return wrappe->getQuery() + Request::separator +
           std::to_string(uint32_t(MessageProperties::Text)) + Request::separator + text;
}

// PrivateDecorator
PrivateDecorator::PrivateDecorator(std::shared_ptr<Message> message, uint32_t addressee_id)
        : PropertiesDecorator(message), addressee_id(addressee_id) {}

std::string PrivateDecorator::getQuery() {
    return wrappe->getQuery() + Request::separator +
           std::to_string(uint32_t(MessageProperties::Private)) + Request::separator +
           std::to_string(addressee_id);
}

void PrivateDecorator::handle(ServersideClientHandler& handler) {
    handler.getRoom(wrappe->getRoom())->getClient(addressee_id)->sendRequest(*this);
}

// AuthorizationRequest
AuthorizationRequest::AuthorizationRequest(const std::string& name, const std::string& password)
        : account(std::make_shared<Account>(0, name, password)) {}

std::string AuthorizationRequest::getQuery() {
    return account->name + Request::separator + account->password_hash;
}
// SignInRequest
SignInRequest::SignInRequest(const std::string& name, const std::string& password_hash)
        : AuthorizationRequest(name, password_hash) {}

std::string SignInRequest::getQuery() {
    return std::to_string(uint32_t(RequestTypes::SignIn)) + Request::separator +
           AuthorizationRequest::getQuery();
}
void SignInRequest::handle(ServersideClientHandler& handler) {}
void SignInRequest::handle(ClientsideHandler& handler) {}

// SignUpRequest
SignUpRequest::SignUpRequest(const std::string& name, const std::string& password_hash)
        : AuthorizationRequest(name, password_hash) {}

std::string SignUpRequest::getQuery() {
    return std::to_string(uint32_t(RequestTypes::SignIn)) + Request::separator +
           AuthorizationRequest::getQuery();
}
void SignUpRequest::handle(ServersideClientHandler& handler) {}
void SignUpRequest::handle(ClientsideHandler& handler) {}
