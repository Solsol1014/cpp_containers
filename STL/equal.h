#ifndef EQUAL_H
#define EQUAL_H

namespace ft {
template <typename InputIt1, typename InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
    bool answer = true;
    while(1) {
        if(first1==last1)
            break;

        if(*first1 != *first2) {
            answer = false;
            break;
        }

        first1++;
        first2++;
    }

    return answer;
}

template <typename InputIt1, typename InputIt2, typename BinaryPred>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPred p) {
    bool answer = true;

    while(1) {
        if(first1==last1)
            break;

        if(!p(*first1, *first2)) {
            answer = false;
            break;
        }

        first1++;
        first2++;
    }

    return answer;
}
}

#endif