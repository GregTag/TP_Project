#pragma once
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

#include "permissions.hpp"

class ServerPermissionsBank : public PermissionsBank {
   public:
    static void initialize(const std::filesystem::path& storage_file);

    virtual ~ServerPermissionsBank();

   private:
    ServerPermissionsBank(const std::filesystem::path& storage_file);

    void parsePermission(const std::string&);
    void loadFromFile();
    void saveToFile();

    std::fstream storage;
};
