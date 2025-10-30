#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "lexicographical_compare.h"
#include "equal.h"
#include "pair.h"

int main() {
    // ## 1. pair

    std::cout << "======================\n1. Pair\n======================\n- Information: pair1s are made by \"make_pair\" function.\n----------------------\n"; 

    while(1) {
        std::pair<int, int> stdpair1, stdpair2;
        ft::pair<int, int> ftpair1, ftpair2;

        std::cout << "Enter the two numbers that will be entered in pair1 (Ex: 1 2): ";
        int tmp1, tmp2;
        std::cin >> tmp1 >> tmp2;
        stdpair1 = std::make_pair(tmp1, tmp2);
        ftpair1 = ft::make_pair(tmp1, tmp2);

        std::cout << "Enter the two numbers that will be entered in pair2 (Ex: 5 3): ";
        std::cin >> tmp1 >> tmp2;
        stdpair2 = std::make_pair(tmp1, tmp2);
        ftpair2 = ft::make_pair(tmp1, tmp2);

        std::cout << "----------------------\n";

        std::cout << "1.1. Members\n";
        std::cout << "- std: {" << stdpair1.first << ", " << stdpair1.second << "}, {" << stdpair2.first << ", " << stdpair2.second << "}\n";
        std::cout << "- ft: {" << ftpair1.first << ", " << ftpair1.second << "}, {" << ftpair2.first << ", " << ftpair2.second << "}\n";

        std::cout << "----------------------\n";

        std::cout << "1.2. Comparison\n";
        std::cout << "- \"==\": std - " << (stdpair1==stdpair2) << ", ft - " << (ftpair1==ftpair2) << "\n";
        std::cout << "- \"!=\": std - " << (stdpair1!=stdpair2) << ", ft - " << (ftpair1!=ftpair2) << "\n";
        std::cout << "- \"<\": std - " << (stdpair1<stdpair2) << ", ft - " << (ftpair1<ftpair2) << "\n";
        std::cout << "- \">\": std - " << (stdpair1>stdpair2) << ", ft - " << (ftpair1>ftpair2) << "\n";
        std::cout << "- \"<=\": std - " << (stdpair1<=stdpair2) << ", ft - " << (ftpair1<=ftpair2) << "\n";
        std::cout << "- \">=\": std - " << (stdpair1>=stdpair2) << ", ft - " << (ftpair1>=ftpair2) << "\n";

        std::cout << "\nEnter 'Y' to proceed, 'N' to retest: ";
        char check;
        std::cin >> check;
        
        std::cout << "----------------------\n";

        if(check=='Y')
            break;
    }


    // ## 2. equal
    std::cout << "======================\n2. Equal\n======================\n";
    
    while(1) {
        std::string a, b;
        std::cout << "Enter the first string: ";
        std::cin >> a;
        std::cout << "Enter the second string: ";
        std::cin >> b;

        std::cout << "----------------------\n";

        std::cout << "- std::equal: " << std::equal(a.begin(), a.end(), b.begin()) << "\n";
        std::cout << "- ft::equal: " << ft::equal(a.begin(), a.end(), b.begin()) << "\n";

        std::cout << "\nEnter 'Y' to proceed, 'N' to retest: ";
        char check;
        std::cin >> check;

        std::cout << "----------------------\n";

        if(check=='Y')
            break;
    }

    // ## 3. lexicographical_compare
    std::cout << "======================\n3. Lexicographical Compare\n======================\n";

    while(1) {
        std::string a, b;
        std::cout << "Enter the first string: ";
        std::cin >> a;
        std::cout << "Enter the second string: ";
        std::cin >> b;

        std::cout << "----------------------\n";

        std::cout << "- std::lexicographical_compare: " << std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end()) << "\n";
        std::cout << "- ft::lexicographical_compare: " << ft::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end()) << "\n";

        std::cout << "\nEnter 'Y' to proceed, 'N' to retest: ";
        char check;
        std::cin >> check;

        std::cout << "----------------------\n";

        if(check=='Y')
            break;
    }

    std::cout << "END OF THE TEST\n";
    
    return 0;
}