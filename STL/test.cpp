#include <iostream>
#include "vector.h"

int main() {
    ft::vector<int> vec;
    vec.push_back(1);
    vec.resize(6);

    std::cout << vec.size();
    return 0;
}