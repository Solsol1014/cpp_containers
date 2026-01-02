#ifndef MAP_H
#define MAP_H

#include <functional>
#include "allocator.h"
#include "pair.h"
#include "rbt.h"
#include "reverse_iterator.h"
#include <cstddef>

// namespace ft {
template <typename Key, typename T, typename Compare = std::less<Key>, typename Allocator = ft::allocator<ft::pair<const Key, T> > >
class map {
    public:
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
    typedef ft::rb_tree_iterator iterator;
    typedef const ft::rb_tree_iterator const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    private:
    typedef ft::rb_tree<value_type, key_compare, allocator_type> tree_type;
    allocator_type _alloc;
    tree_type _rbt;
    Compare _comp;

    public:
    class value_compare {

    };

    map() { // 1. Constructs an empty container
        
    }

    explicit map(const Compare& comp, const Allocator& alloc = Allocator()) { // 2. Constructs an empty container

    }

    template <class InputIt>
    map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) { // 4. Constructs the conatiner with the contents of the range [first, last). If [first, last) is not a valid range, the behavior is undefined.

    }

    map(const map& other) { // 6. Constructs the container with the copy of the contents of other.

    }

    ~map() {

    }

    
};
// }

#endif