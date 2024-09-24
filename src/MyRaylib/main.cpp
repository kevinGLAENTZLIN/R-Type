#include <iostream>
#include "MyRaylib.hpp"

int main() {
    int a = 5;
    int b = 3;
    int result = myRaylib::add(a, b);

    std::cout << "Testing my_library::add function" << std::endl;
    std::cout << a << " + " << b << " = " << result << std::endl;

    if (result == 8) {
        std::cout << "Test passed!" << std::endl;
        return 0;
    } else {
        std::cout << "Test failed!" << std::endl;
        return 1;
    }
}
