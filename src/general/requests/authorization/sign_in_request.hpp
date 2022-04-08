#pragma once
#include "authorization_request.hpp"

class SignInRequest : public AuthorizationRequest {
   public:
    explicit SignInRequest(const std::string& name, const std::string& password_hash);
    virtual ~SignInRequest() = default;

    std::string getQuery() const override;
    void handle(std::shared_ptr<ServersideHandler> handler) override;
};
