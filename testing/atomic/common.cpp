#include <atomic>
#include <iostream>

#include "account.hpp"

int main() {
    std::shared_ptr<Account> acc = std::make_shared<Account>();
    // std::cout << acc->getName() << std::endl;
    std::cout << std::atomic_load<Account>(&acc)->getName() << std::endl;
}