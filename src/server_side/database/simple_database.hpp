#pragma once
#include <deque>
#include <filesystem>
#include <fstream>
#include <sstream>

#include "accounts_database.hpp"

class SimpleDatabase : public AccountsDatabase {
   public:
    static void initialize(const std::filesystem::path& path_to_db_file);

    virtual ~SimpleDatabase();

    std::shared_ptr<Account> createAccount(const std::string& name,
                                           const std::string& password_hash,
                                           const std::set<size_t>& available_rooms) override;

    void saveAccount(std::shared_ptr<Account>) override;
    std::shared_ptr<Account> loadAccount(size_t id) override;
    std::shared_ptr<Account> findAccountByName(const std::string&) override;

   private:
    SimpleDatabase(const std::filesystem::path&);

    std::shared_ptr<Account> parseAccount(const std::string&);
    void loadFromFile();
    void saveToFile();

    std::fstream db_file;
    std::deque<std::shared_ptr<Account>> db;
};
