#include "sign_up_request.hpp"

SignUpRequest::SignUpRequest(const std::string& name, const std::string& password_hash)
        : AuthorizationRequest(name, password_hash) {}

std::string SignUpRequest::getQuery() {
    return std::to_string(size_t(RequestTypes::SignIn)) + Request::separator +
           AuthorizationRequest::getQuery();
}
void SignUpRequest::handle(std::shared_ptr<ServersideClientHandler> handler) {
    account = AccountsDatabase::getInstance()->createAccount(account->getName(),
                                                             account->getPasswordHash());
    handler->setAccount(account);
    handler->sendRequest(shared_from_this());
}
