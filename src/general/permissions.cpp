#include "permissions.hpp"

PermissionsBank::PermissionsSet PermissionsBank::get(size_t room, size_t client) {
    return permissions_set[room][client];
}

void PermissionsBank::setDefault(size_t room, PermissionsBank::PermissionsSet permission_set) {
    default_permissons_set[room] = permission_set;
}

void PermissionsBank::set(size_t room, size_t client,
                          PermissionsBank::PermissionsSet permission_set) {
    permissions_set[room][client] = permission_set;
}

bool PermissionsBank::check(size_t room, size_t client, Permissions permission) {
    size_t mask = 1UL << static_cast<size_t>(permission);

    auto iter = permissions_set.find(room);
    if (iter != permissions_set.end()) {
        auto it = iter->second.find(client);
        if (it != iter->second.end()) return it->second & mask;
    }

    auto it = default_permissons_set.find(room);
    if (it != default_permissons_set.end()) return it->second & mask;

    return default_permissons_set[0] & mask;
}
