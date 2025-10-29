#include <iostream>
#include <vector>
#include "equal.h"

int main() {
    std::vector<int> vec1, vec2, vec3;

    for(int i = 0 ; i<10 ; i++) {
        vec1.push_back(i);
        vec2.push_back(i);
        vec3.push_back(i);
    }

    vec3[8] = 0;

    std::cout << "vec1, vec2: " << ft::equal(vec1.begin(), vec1.end(), vec2.begin()) << "\n";
    std::cout << "vec1, vec3: " << ft::equal(vec1.begin(), vec1.end(), vec3.begin()) << "\n";
}