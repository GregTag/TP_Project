#pragma once

#include <memory>
#include <set>
#include <string>

class Account {
   public:
    Account();

    Account(size_t id, const std::string& name, const std::string& password_hash,
            const std::set<size_t>& available_rooms = std::set<size_t>());

    ~Account() = default;

    size_t getId() const;
    const std::string& getName() const;
    const std::string& getPasswordHash() const;
    const std::set<size_t>& getAvailableRooms() const;

   private:
    size_t id;
    std::string name;
    std::string password_hash;
    std::set<size_t> available_rooms;
};
