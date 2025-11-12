#ifndef IT_H
#define IT_H

#include <cstddef>
#include <iterator>

namespace ft {
template <typename Iter>
struct iterator_traits {
    typedef typename Iter::difference_type difference_type;
    typedef typename Iter::value_type value_type;
    typedef typename Iter::pointer pointer;
    typedef typename Iter::reference reference;
    typedef typename Iter::iterator_category iterator_category;
};

template <typename T>
struct iterator_traits<T*> {
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef std::random_access_iterator_tag iterator_category;
};

template <typename T>
struct iterator_traits<const T*> {
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef const T* pointer;
    typedef const T& reference;
    typedef std::random_access_iterator_tag iterator_category;
};

template <typename Category, typename T, typename Distance = std::ptrdiff_t, typename Pointer = T*, typename Reference = T&>
struct iterator {
    typedef Category iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
};

template <typename InputIt>
typename ft::iterator_traits<InputIt>::difference_type distance(InputIt first, InputIt last) {

}
}

#endif