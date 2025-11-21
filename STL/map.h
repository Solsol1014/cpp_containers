#ifndef MAP_H
#define MAP_H

#include <functional>
#include "allocator.h"
#include "pair.h"
#include <cstddef>

// namespace ft {
template <typename Key, typename T, typename Compare = std::less<Key>, typename Allocator = ft::allocator<ft::pair<const Key, T> > >
class map {
    typedef Key key_type;
    typedef T mapped_type;
    typedef typename ft::pair<const Key, T> value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Compare key_compare;
    typedef Allocator allocator_type;
    typedef value_type& reference;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    typedef 
};
// }

#endif