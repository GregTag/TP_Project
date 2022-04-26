#include "permissions.hpp"

std::shared_ptr<PermissionsBank> PermissionsBank::getInstance() {
    return bank;
}

PermissionsBank::Permission PermissionsBank::get(size_t room, size_t client) {
    return permissions_set[room][client];
}

void PermissionsBank::setDefault(size_t room, Permission permission_set) {
    default_permissons_set[room] = permission_set;
}

void PermissionsBank::set(size_t room, size_t client, Permission permission_set) {
    permissions_set[room][client] = permission_set;
}

bool PermissionsBank::check(size_t room, size_t client, Permission permission) {
    auto iter = permissions_set.find(room);
    if (iter != permissions_set.end()) {
        auto it = iter->second.find(client);
        if (it != iter->second.end()) return (it->second & permission) == permission;
    }

    auto it = default_permissons_set.find(room);
    if (it != default_permissons_set.end()) return (it->second & permission) == permission;

    return (default_permissons_set[0] & permission) == permission;
}

std::shared_ptr<PermissionsBank> PermissionsBank::bank(nullptr);
