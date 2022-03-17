#pragma once

#include <memory>
#include <string>
#include <vector>

struct Account {
   private:
    static uint32_t next_id;
    uint32_t id;

   public:
    std::string name;
    std::string password_hash;
    std::shared_ptr<std::vector<uint32_t>> available_rooms;

   public:
    Account();
    Account(uint32_t id, const std::string& name, const std::string& password_hash,
            std::shared_ptr<std::vector<uint32_t>> available_rooms = nullptr);
    ~Account() = default;

    void constructId();
    uint32_t getId();
};