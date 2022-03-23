#include "sign_in_request.hpp"

SignInRequest::SignInRequest(const std::string& name, const std::string& password_hash)
        : AuthorizationRequest(name, password_hash) {}

std::string SignInRequest::getQuery() {
    return std::to_string(size_t(RequestTypes::SignIn)) + Request::separator +
           AuthorizationRequest::getQuery();
}
void SignInRequest::handle(std::shared_ptr<ServersideClientHandler> handler) {
    auto saved = AccountsDatabase::getInstance()->findAccountByName(account->getName());
    if (saved->getPasswordHash() == account->getPasswordHash()) {
        account = saved;
        handler->sendRequest(shared_from_this());
    }
    // TODO send error about wrong password
}
