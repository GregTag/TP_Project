#include "account.hpp"

#include "socket/log.hpp"

Account::Account() : id(0), name("anonymous"), password_hash(""), available_rooms(nullptr) {}

Account::Account(size_t id, const std::string& name, const std::string& password_hash,
                 std::shared_ptr<std::vector<size_t>> available_rooms)
        : id(id), name(name), password_hash(password_hash), available_rooms(available_rooms) {}

size_t Account::getId() const {
    return id;
}

const std::string& Account::getName() const {
    return name;
}

const std::string& Account::getPasswordHash() const {
    return password_hash;
}

std::shared_ptr<std::vector<size_t>> Account::getAvailableRooms() const {
    return available_rooms;
}
