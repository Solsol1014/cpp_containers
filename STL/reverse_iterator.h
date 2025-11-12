#ifndef RI_H
#define RI_H
#include "iterator.h"

namespace ft {
template <typename Iter>
class reverse_iterator {
    protected:
        Iter current;

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

        iterator_type base() const {
            return current;
        }

        reference operator*() const {
            Iter tmp = current;
            return *--tmp;
        }

        pointer operator->() const {
            return &(operator*());
        }

        reference operator[](difference_type n) const {
            return *(*this + n);
        }

        reverse_iterator& operator++() {
            --current;
            return *this;
        }

        reverse_iterator& operator--() {
            ++current;
            return *this;
        }

        reverse_iterator operator++(int) {
            reverse_iterator tmp = *this;
            --current;
            return tmp;
        }

        reverse_iterator operator--(int) {
            reverse_iterator tmp = *this;
            ++current;
            return tmp;
        }

        reverse_iterator operator+(difference_type n) const {
            return reverse_iterator(current - n);
        }

        reverse_iterator operator-(difference_type n) const {
            return reverse_iterator(current + n);
        }

        reverse_iterator& operator+=(difference_type n) {
            current -= n;
            return *this;
        }

        reverse_iterator& operator-=(difference_type n) {
            current += n;
            return *this;
        }
};

template <typename Iter1, typename Iter2>
bool operator==(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
    return lhs.base() == rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator!=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
    return lhs.base() != rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator<(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
    return lhs.base() > rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator<=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
    return lhs.base() >= rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator>(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
    return lhs.base() < rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator>=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
    return lhs.base() <= rhs.base();
}

template <typename Iter>
reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it) {
    return reverse_iterator<Iter>(it.base() - n);
}

template <typename Iter1, typename Iter2>
typename reverse_iterator<Iter1>::difference_type operator-(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
    return rhs.base() - lhs.base();
}
}

#endif