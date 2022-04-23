#pragma once

#include <memory>
#include <string>
#include <vector>

class Account {
   public:
    Account();

    Account(size_t id, const std::string& name, const std::string& password_hash,
            const std::vector<size_t>& available_rooms = std::vector<size_t>());

    ~Account() = default;

    size_t getId() const;
    const std::string& getName() const;
    const std::string& getPasswordHash() const;
    const std::vector<size_t>& getAvailableRooms() const;

   private:
    size_t id;
    std::string name;
    std::string password_hash;
    std::vector<size_t> available_rooms;
};
