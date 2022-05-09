#include "server_permissions.hpp"

void ServerPermissionsBank::initialize(const std::filesystem::path& storage_file) {
    if (!bank)
        bank = std::shared_ptr<ServerPermissionsBank>(new ServerPermissionsBank(storage_file));
}

ServerPermissionsBank::ServerPermissionsBank(const std::filesystem::path& storage_file) {
    bool exists = std::filesystem::exists(storage_file);

    if (!exists) storage.open(storage_file, std::ios::out);
    storage.open(storage_file, std::ios::in | std::ios::out);
    if (exists) loadFromFile();
    if (!default_permissons_set.count(0)) setDefault(0, PermissionsSet::DefaultPermissions);
}

ServerPermissionsBank::~ServerPermissionsBank() {
    saveToFile();
    storage.close();
}

void ServerPermissionsBank::parsePermission(const std::string& line) {
    std::stringstream ss(line);
    size_t room_id;
    ss >> room_id;
    auto& room = permissions_set[room_id];

    size_t user;
    Permission perm;
    while (!ss.eof()) {
        ss >> user >> perm;
        room.emplace(user, perm);
    }
}

void ServerPermissionsBank::loadFromFile() {
    std::string line;
    std::getline(storage, line, '\n');
    if (!line.empty()) {
        std::stringstream ss(line);
        size_t room;
        Permission perm;
        while (!ss.eof()) {
            ss >> room >> perm;
            default_permissons_set.emplace(room, perm);
        }
    }

    while (!storage.eof()) {
        std::getline(storage, line, '\n');
        if (!line.empty()) parsePermission(line);
    }
}

void ServerPermissionsBank::saveToFile() {
    storage.clear();
    storage.seekp(0);

    for (auto& [room, perm] : default_permissons_set) {
        storage << room << ' ' << perm << ' ';
    }
    storage << std::endl;

    for (auto& [room, perm_set] : permissions_set) {
        storage << room << ' ';
        for (auto& [user, perm] : perm_set) {
            storage << user << ' ' << perm << ' ';
        }
        storage << std::endl;
    }
}
