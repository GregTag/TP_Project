#include "sign_up_request.hpp"

SignUpRequest::SignUpRequest(std::shared_ptr<Account> account) : AuthorizationRequest(account) {}

std::string SignUpRequest::getQuery() const {
    return std::to_string(size_t(RequestTypes::SignUp)) + Request::separator +
           AuthorizationRequest::getQuery();
}
void SignUpRequest::handle(std::shared_ptr<ServersideHandler> handler) {
    handler->onSignUp(std::static_pointer_cast<SignUpRequest>(shared_from_this()));
}
