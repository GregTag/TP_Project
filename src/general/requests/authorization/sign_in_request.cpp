#include "sign_in_request.hpp"

SignInRequest::SignInRequest(const std::string& name, const std::string& password_hash)
        : AuthorizationRequest(name, password_hash) {}

std::string SignInRequest::getQuery() const {
    return std::to_string(size_t(RequestTypes::SignIn)) + Request::separator +
           AuthorizationRequest::getQuery();
}
void SignInRequest::handle(std::shared_ptr<ServersideHandler> handler) {
    handler->onSignIn(std::static_pointer_cast<SignInRequest>(shared_from_this()));
}
