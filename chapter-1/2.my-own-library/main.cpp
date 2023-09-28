#include <iostream>
#include "libs/mylib/mylib.h"

int main() {
    int a = 10, b = 5;

    int sum = add(a, b);
    int difference = subtract(a, b);

    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Difference: " << difference << std::endl;

    return 0;
}