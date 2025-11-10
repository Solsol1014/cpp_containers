#ifndef PAIR_H
#define PAIR_H

namespace ft {
template <typename T1, typename T2>
class pair {
private:
public:
    typedef T1 first_type;
    typedef T2 second_type;
    T1 first;
    T2 second;

    // constructor
    pair() : first(), second() {}
    pair(const T1& x, const T2& y) : first(x), second(y) {}

    pair& operator=(const pair<T1, T2>& other) {
        first = other.first;
        second = other.second;
        return *this;
    }

    ~pair() {
        
    }
};

template <typename T1, typename T2>
pair<T1, T2> make_pair(T1 x, T2 y) {
    return pair<T1, T2>(x, y);
}

template <typename T1, typename T2, typename U1, typename U2>
bool operator==(const pair<T1, T2>& lhs, const pair<U1, U2>& rhs) {
    return (lhs.first==rhs.first)&&(lhs.second==rhs.second);
}

template <typename T1, typename T2, typename U1, typename U2>
bool operator!=(const pair<T1, T2>& lhs, const pair<U1, U2>& rhs) {
    return (lhs.first!=rhs.first)||(lhs.second!=rhs.second);
}

template <typename T1, typename T2, typename U1, typename U2>
bool operator<(const pair<T1, T2>& lhs, const pair<U1, U2>& rhs) {
    if(lhs.first==rhs.first)
        return lhs.second < rhs.second;
    else
        return lhs.first < rhs.first;
}

template <typename T1, typename T2, typename U1, typename U2>
bool operator>(const pair<T1, T2>& lhs, const pair<U1, U2>& rhs) {
    if(lhs.first==rhs.first)
        return lhs.second > rhs.second;
    else
        return lhs.first > rhs.first;
}

template <typename T1, typename T2, typename U1, typename U2>
bool operator<=(const pair<T1, T2>& lhs, const pair<U1, U2>& rhs) {
    return !operator>(lhs, rhs);
}

template <typename T1, typename T2, typename U1, typename U2>
bool operator>=(const pair<T1, T2>& lhs, const pair<U1, U2>& rhs) {
    return !operator<(lhs, rhs);
}
}

#endif