#pragma once
#include "requests/request.hpp"

class AuthorizationRequest : public Request {
   public:
    AuthorizationRequest(std::shared_ptr<Account> account);
    virtual ~AuthorizationRequest() = default;

    std::string getQuery() const override;
    void handle(std::shared_ptr<ClientsideHandler> handler) override;

    std::shared_ptr<Account> getAccount();
    void setAccount(std::shared_ptr<Account>);

   private:
    std::shared_ptr<Account> account;
};
