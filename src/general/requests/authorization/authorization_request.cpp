#include "authorization_request.hpp"

#include "requests/request_creator.hpp"

AuthorizationRequest::AuthorizationRequest(std::shared_ptr<Account> account) : account(account) {}

std::string AuthorizationRequest::getQuery() const {
    return account->getName() + Request::separator + account->getPasswordHash() +
           Request::separator + account->getRoomList() + Request::separator;
}

void AuthorizationRequest::handle(std::shared_ptr<ClientsideHandler> handler) {
    handler->setAccount(account);
    handler->receive(handler->getCreator()->createInfoMessage("Authorizated succesfully."));
}

std::shared_ptr<Account> AuthorizationRequest::getAccount() {
    return account;
}

void AuthorizationRequest::setAccount(std::shared_ptr<Account> acc) {
    account = acc;
}
