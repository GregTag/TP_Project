#include "Account.h"

uint32_t Account::next_id = 1;

Account::Account() : id(0), name("anonymous") {}

Account::Account(uint32_t id, const std::string& name, const std::string& password_hash,
                 std::shared_ptr<std::vector<uint32_t>> available_rooms)
        : id(id), name(name), password_hash(password_hash), available_rooms(available_rooms) {}

void Account::constructId() {
    id = next_id++;
}

uint32_t Account::getId() {
    return id;
}