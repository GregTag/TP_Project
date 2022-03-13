#pragma once

#include <memory>
#include <string>
#include <vector>

struct Account {
    uint32_t id;
    std::string name;
    std::string password_hash;
    std::vector<uint32_t> available_rooms;
};

class AnonymousAccount : Account {
   private:
    static std::shared_ptr<AnonymousAccount> object;
    AnonymousAccount();

   public:
    static std::shared_ptr<AnonymousAccount> getInstance();
};