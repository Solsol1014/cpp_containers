#ifndef LC_H
#define LC_H

namespace ft {
template <typename InputIt1, typename InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
    bool answer;
    while(1) {
        if(*first1<*first2) {
            answer = true;
            break;
        }
        else if(*first1>*first2) {
            answer = false;
            break;
        }

        if(first2==last2-1) {
            answer = false;
            break;
        }
        else if(first1==last1-1) {
            answer = true;
            break;
        }

        first1++;
        first2++;
    }

    return answer;
}
}

#endif