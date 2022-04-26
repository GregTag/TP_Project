#pragma once

#include <memory>
#include <unordered_map>

class PermissionsSet {
   public:
    using Permission = size_t;

    static const Permission CanReadHistory = 1;
    static const Permission CanGetUsernamesList = 2;
    static const Permission CanSendMessages = 4;
    static const Permission CanSendPrivateMessages = 8;

    static const Permission AllPermissions = 15;
};

class PermissionsBank {
   public:
    using Permission = typename PermissionsSet::Permission;

    static std::shared_ptr<PermissionsBank> getInstance();

    virtual ~PermissionsBank() = default;

    Permission get(size_t room, size_t client);
    void setDefault(size_t room, Permission permission_set);
    void set(size_t room, size_t client, Permission permission_set);
    bool check(size_t room, size_t client, Permission permission);

   protected:
    static std::shared_ptr<PermissionsBank> bank;

    std::unordered_map<size_t, std::unordered_map<size_t, Permission>> permissions_set;
    std::unordered_map<size_t, Permission> default_permissons_set;
};
