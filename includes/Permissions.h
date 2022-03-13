#pragma once

#include <unordered_map>

enum class Permissions {
    CanReadHistory = 1,
    CanGetUsernamesList = 2,
    CanSendMessages = 4,
    CanSendPrivateMessages = 8
};

class PermissionsBank {
   private:
    std::unordered_map<std::pair<uint32_t, uint32_t>, uint32_t> permissions;
    std::unordered_map<uint32_t, uint32_t> default_permissons;

   public:
    PermissionsBank();
    ~PermissionsBank();

    void setDefault(uint32_t, uint32_t);
    void set(uint32_t, uint32_t, uint32_t);
    uint32_t get(uint32_t, uint32_t);
};