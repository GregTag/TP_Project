#pragma once
#include "accounts_database.hpp"
#include "requests/request.hpp"

class AuthorizationRequest : public Request {
   public:
    AuthorizationRequest(const std::string& name, const std::string& password_hash);
    virtual ~AuthorizationRequest() = default;

    std::string getQuery() const override;
    void handle(std::shared_ptr<ClientsideHandler> handler) override;

   protected:
    std::shared_ptr<Account> account;
};
