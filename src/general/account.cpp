#include "account.hpp"

#include "socket/log.hpp"

Account::Account() : id(0), name("anonymous"), password_hash(""), available_rooms() {}

Account::Account(size_t id, const std::string& name, const std::string& password_hash,
                 const std::set<size_t>& available_rooms)
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

std::set<size_t>& Account::getAvailableRooms() {
    return available_rooms;
}

std::string Account::getRoomList() const {
    std::stringstream ss;
    for (const size_t& room : available_rooms) {
        ss << room << ' ';
    }

    std::string res;
    std::getline(ss, res);
    if (!res.empty()) res.pop_back();
    return res;
}
