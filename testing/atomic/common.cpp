#include <boost/make_shared.hpp>
#include <boost/smart_ptr/atomic_shared_ptr.hpp>
#include <iostream>

struct A {
    int a;

    A(int a) : a(a) {}
};

int main() {
    boost::atomic_shared_ptr<A> ptr = boost::make_shared<A>(5);
    std::cout << ptr.load()->a << "\n";
}