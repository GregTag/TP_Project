#include "accounts_database.hpp"

std::shared_ptr<AccountsDatabase> AccountsDatabase::getInstance() {
    return database;
}
