#include "simple_database.hpp"

void SimpleDatabase::initialize(const std::string& path_to_db_file) {
    if (!database) database = std::shared_ptr<SimpleDatabase>(new SimpleDatabase(path_to_db_file));
}

SimpleDatabase::~SimpleDatabase() {
    saveToFile();
    db_file.close();
}

SimpleDatabase::SimpleDatabase(const std::string& path)
        : db_file(path, std::ios::in | std::ios::out) {
    loadFromFile();
}

std::shared_ptr<Account> SimpleDatabase::createAccount(
        const std::string& name, const std::string& password_hash,
        std::shared_ptr<std::vector<size_t>> available_rooms = nullptr) {
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
    auto rooms = std::make_shared<std::vector<size_t>>();
    ss >> id >> name >> passw;
    while (!ss.eof()) {
        size_t r;
        ss >> r;
        rooms->push_back(r);
    }
    return std::make_shared<Account>(id, name, passw, std::move(rooms));
}

void SimpleDatabase::loadFromFile() {
    std::string line;
    while (!db_file.eof()) {
        std::getline(db_file, line, '\n');
        if (!line.empty()) db.push_back(parseAccount(line));
    }
    if (db.empty()) db.push_back(std::make_shared<Account>());
}

void SimpleDatabase::saveToFile() {
    db_file.clear();
    db_file.seekp(0);
    for (auto& acc : db) {
        if (!acc) continue;
        db_file << acc->getId() << ' ' << acc->getName() << ' ' << acc->getPasswordHash();
        if (acc->getAvailableRooms()) {
            for (auto& n : *acc->getAvailableRooms()) {
                db_file << ' ' << n;
            }
        }
        db_file << std::endl;
    }
}
