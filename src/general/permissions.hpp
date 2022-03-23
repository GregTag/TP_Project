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
    using PermissionsSet = size_t;

    PermissionsBank() = default;
    ~PermissionsBank() = default;

    PermissionsSet get(size_t room, size_t client);
    void setDefault(size_t room, PermissionsSet permission_set);
    void set(size_t room, size_t client, PermissionsSet permission_set);
    bool check(size_t room, size_t client, Permissions permission);

   private:
    std::unordered_map<size_t, std::unordered_map<size_t, PermissionsSet>> permissions_set;
    std::unordered_map<size_t, PermissionsSet> default_permissons_set;
};
