#pragma once
#include "authorization_request.hpp"

class SignUpRequest : public AuthorizationRequest {
   public:
    explicit SignUpRequest(const std::string& name, const std::string& password_hash);
    virtual ~SignUpRequest() = default;

    std::string getQuery() const override;
    void handle(std::shared_ptr<ServersideClientHandler> handler) override;
};
