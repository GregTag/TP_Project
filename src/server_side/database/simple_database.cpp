#include "simple_database.hpp"

#include "log.hpp"

void SimpleDatabase::initialize(const std::filesystem::path& path_to_db_file) {
    if (!database) database = std::shared_ptr<SimpleDatabase>(new SimpleDatabase(path_to_db_file));
}

SimpleDatabase::~SimpleDatabase() {
    saveToFile();
    db_file.close();
}

SimpleDatabase::SimpleDatabase(const std::filesystem::path& path) {
    bool exists = std::filesystem::exists(path);

    if (!exists) db_file.open(path, std::ios::out);
    db_file.open(path, std::ios::in | std::ios::out);
    if (exists) loadFromFile();

    if (db.empty()) db.push_back(std::make_shared<Account>());
    Logger::log() << "DB initialized. " << db.size() << " entries loaded." << std::endl;
}

std::shared_ptr<Account> SimpleDatabase::createAccount(const std::string& name,
                                                       const std::string& password_hash,
                                                       const std::set<size_t>& available_rooms) {
    if (findAccountByName(name)) return nullptr;
    db.push_back(std::make_shared<Account>(db.size(), name, password_hash, available_rooms));
    return db.back();
}

void SimpleDatabase::saveAccount(std::shared_ptr<Account> account) {
    db[account->getId()] = account;
}

std::shared_ptr<Account> SimpleDatabase::loadAccount(size_t id) {
    if (id >= db.size()) return nullptr;
    return db[id];
}

std::shared_ptr<Account> SimpleDatabase::findAccountByName(const std::string& name) {
    for (auto it = db.begin(); it != db.end(); ++it) {
        if ((*it)->getName() == name) return *it;
    }
    return nullptr;
}

std::shared_ptr<Account> SimpleDatabase::parseAccount(const std::string& line) {
    std::stringstream ss(line);
    size_t id;
    std::string name;
    std::string passw;
    std::set<size_t> rooms;
    ss >> id >> name >> passw;
    while (!ss.eof()) {
        size_t r;
        ss >> r;
        rooms.insert(r);
    }
    return std::make_shared<Account>(id, name, passw, rooms);
}

void SimpleDatabase::loadFromFile() {
    std::string line;
    while (!db_file.eof()) {
        std::getline(db_file, line, '\n');
        if (!line.empty()) db.push_back(parseAccount(line));
    }
}

void SimpleDatabase::saveToFile() {
    db_file.clear();
    db_file.seekp(0);
    for (auto& acc : db) {
        if (!acc) continue;
        db_file << acc->getId() << ' ' << acc->getName() << ' ' << acc->getPasswordHash();
        if (!acc->getAvailableRooms().empty()) {
            for (auto& n : acc->getAvailableRooms()) {
                db_file << ' ' << n;
            }
        }
        db_file << std::endl;
    }
}
