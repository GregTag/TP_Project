#pragma once
#include "account.hpp"

class AccountsDatabase {
   public:
    static std::shared_ptr<AccountsDatabase> getInstance();

    virtual ~AccountsDatabase() = default;

    virtual std::shared_ptr<Account> createAccount(
            const std::string& name, const std::string& password_hash,
            const std::vector<size_t>& available_rooms = std::vector<size_t>()) = 0;

    virtual void saveAccount(std::shared_ptr<Account>) = 0;
    virtual std::shared_ptr<Account> loadAccount(size_t id) = 0;
    virtual std::shared_ptr<Account> findAccountByName(const std::string&) = 0;

   protected:
    static std::shared_ptr<AccountsDatabase> database;
};
