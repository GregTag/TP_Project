#include <iostream>

#include "simple_database.hpp"

int main() {
    SimpleDatabase::initialize("db.txt");
    std::cout << "In main" << std::endl;
    AccountsDatabase::getInstance()->createAccount("test1", "test");
}
