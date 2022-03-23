#include "authorization_request.hpp"

AuthorizationRequest::AuthorizationRequest(const std::string& name, const std::string& password)
        : account(std::make_shared<Account>(0, name, password)) {}

std::string AuthorizationRequest::getQuery() {
    return account->getName() + Request::separator + account->getPasswordHash();
}

void AuthorizationRequest::handle(std::shared_ptr<ClientsideHandler> handler) {
    handler->setAccount(account);
}
