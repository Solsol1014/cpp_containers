#include <iostream>
#include <vector>
#include <typeinfo>
#include "enable_if.h"
#include "is_integral.h"
#include "iterator_traits.h"

template <typename T>
void print_category(T it) {
    typedef typename ft::iterator_traits<T>::iterator_category category;

    if (typeid(category) == typeid(std::input_iterator_tag))
        std::cout << "input_iterator_tag\n";
    else if (typeid(category) == typeid(std::output_iterator_tag))
        std::cout << "output_iterator_tag\n";
    else if (typeid(category) == typeid(std::forward_iterator_tag))
        std::cout << "forward_iterator_tag\n";
    else if (typeid(category) == typeid(std::bidirectional_iterator_tag))
        std::cout << "bidirectional_iterator_tag\n";
    else if (typeid(category) == typeid(std::random_access_iterator_tag))
        std::cout << "random_access_iterator_tag\n";
    else
        std::cout << "unknown category\n";

    std::cout << *it << "\n";
}

template <typename T>
typename ft::enable_if<ft::is_integral<T>::value>::type test(const T& t) {
    std::cout << "t: " << t << "\n";
}

struct A {};

int main() {
    test(1);
    test(false);
    test('c');

    // A a;
    // test(a);

    std::cout << ft::is_integral<bool>::value << "\n";
    std::cout << ft::is_integral<A>::value << "\n";

    std::vector<int> vec(5, 0);
    print_category(vec.begin()); 

    return 0;
}