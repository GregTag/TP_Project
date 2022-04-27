#pragma once
#include "authorization_request.hpp"

class SignInRequest : public AuthorizationRequest {
   public:
    explicit SignInRequest(std::shared_ptr<Account> account);
    virtual ~SignInRequest() = default;

    std::string getQuery() const override;
    void handle(std::shared_ptr<ServersideHandler> handler) override;
};
