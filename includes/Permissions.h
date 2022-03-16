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
    std::unordered_map<std::pair<uint32_t, uint32_t>, uint32_t> permissions_set;
    std::unordered_map<uint32_t, uint32_t> default_permissons_set;

   public:
    PermissionsBank();
    ~PermissionsBank();

    void setDefault(uint32_t room, uint32_t permission_set);
    void set(uint32_t room, uint32_t client, uint32_t permission_set);
    uint32_t get(uint32_t room, uint32_t client);
    bool check(uint32_t room, uint32_t client, Permissions permission);
};