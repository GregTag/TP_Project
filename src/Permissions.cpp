#include "Permissions.h"

void PermissionsBank::setDefault(uint32_t room, PermissionsBank::PermissionsSet permission_set) {
    default_permissons_set[room] = permission_set;
}

void PermissionsBank::set(uint32_t room, uint32_t client,
                          PermissionsBank::PermissionsSet permission_set) {
    permissions_set[room][client] = permission_set;
}

PermissionsBank::PermissionsSet PermissionsBank::get(uint32_t room, uint32_t client) {
    return permissions_set[room][client];
}

bool PermissionsBank::check(uint32_t room, uint32_t client, Permissions permission) {
    uint32_t mask = 1UL << static_cast<uint32_t>(permission);
    {
        auto iter = permissions_set.find(room);
        if (iter != permissions_set.end()) {
            auto it = iter->second.find(client);
            if (it != iter->second.end()) return it->second & mask;
        }
    }
    {
        auto it = default_permissons_set.find(room);
        if (it != default_permissons_set.end()) return it->second & mask;
    }
    return default_permissons_set[0] & mask;
}
