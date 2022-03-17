#pragma once

#include <unordered_map>

enum class Permissions {
    CanReadHistory = 1,
    CanGetUsernamesList = 2,
    CanSendMessages = 4,
    CanSendPrivateMessages = 8
};

class PermissionsBank {
   public:
    using PermissionsSet = uint32_t;

   private:
    std::unordered_map<uint32_t, std::unordered_map<uint32_t, PermissionsSet>> permissions_set;
    std::unordered_map<uint32_t, PermissionsSet> default_permissons_set;

   public:
    PermissionsBank() = default;
    ~PermissionsBank() = default;

    void setDefault(uint32_t room, PermissionsSet permission_set);
    void set(uint32_t room, uint32_t client, PermissionsSet permission_set);
    PermissionsSet get(uint32_t room, uint32_t client);
    bool check(uint32_t room, uint32_t client, Permissions permission);
};