#pragma once
#include "authorization_request.hpp"

class SignUpRequest : public AuthorizationRequest {
   public:
    explicit SignUpRequest(std::shared_ptr<Account> account);
    virtual ~SignUpRequest() = default;

    std::string getQuery() const override;
    void handle(std::shared_ptr<ServersideHandler> handler) override;
};
