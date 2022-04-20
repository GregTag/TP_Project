#include "server_handler.hpp"

#include "requests/request.hpp"

ServersideHandler::ServersideHandler(std::shared_ptr<Socket> client) : AbstractHandler(client) {}

void ServersideHandler::receive(std::shared_ptr<Request> request) {
    request->handle(std::static_pointer_cast<ServersideHandler>(shared_from_this()));
}
