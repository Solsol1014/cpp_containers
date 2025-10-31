#ifndef RI_H
#define RI_H
#include "iterator_traits.h"

// namespace ft {
template <typename Iter>
class reverse_iterator {
    protected:
        Iter current

    public:
        typedef Iter iterator_type;
        typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
        typedef typename ft::iterator_traits<Iter>::value_type value_type;
        typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
        typedef typename ft::iterator_traits<Iter>::pointer pointer;
        typedef typename ft::iterator_traits<Iter>::reference reference;

        reverse_iterator() : current() {}

        explicit reverse_iterator(iterator_type x) : current(x) {}

        template <typename U>
        reverse_iterator(const reverse_iterator<U>& other) : current(other.base) {}

        template <typename U>
        reverse_iterator& operator=(const reverse_iterator<U>& other) {
            current = other.base();
            return *this;
        }

        
};
// }

#endif