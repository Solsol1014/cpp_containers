#ifndef VEC_H
#define VEC_H

#include "allocator.h"
#include "reverse_iterator.h"
#include "iterator_traits.h"
#include "is_integral.h"
#include "enable_if.h"
#include <cstddef>

// namespace ft{
template <typename T, typename Allocator = ft::allocator<T>>
class vector {
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    private:
    allocator_type _alloc; // 할당자 (ex - ft::allocator<T>())
    pointer _data = NULL; // 시작 포인터
    size_type _size = 0; // 요소 개수
    size_type _capacity = 0; // 할당 공간

    public:
    // 2: The default constructor until C++11. Constructs an empty vector with the given allocator alloc.
    explicit vector(const Allocator& alloc = Allocator()): _alloc(alloc) {}

    // 4: Constructs a vector with count copies of elements with value value.
    explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()): _alloc(alloc) {
        if(count==0)
            return;
        
        _data = _alloc.allocate(count);
        _capacity = count;
        _size = count;

        for(size_type i = 0 ; i<count : i++) {
            _alloc.construct(_data+i, value);
        }
    }

    // 5: Constructs a vector with the contents of the range [first, last). Each iterator in [first, last) is dereferenced exactly once. If InputIt does not satisfy the requirements of LegacyInputIterator, overload (4) is called instead with arguments static_cast<size_type>(first), last and alloc.
    template <typename InputIt>
    vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIt>::value, int>::type* = 0): _alloc(alloc) {
        size_type n = 0;
        for(InputIt itr = first ; itr!=last ; itr++)
            n++;
        
        if(n) {
            _data = _alloc.allocate(n);
            _capacity = n;
            for(; first!=last ; first++, _size++)
                _alloc.construct(_data+_size, *first);
        }
    }

    // 7: The copy constructor. Constructs a vector with the contents of other.
    vector(const vector& other) {

    }

    // ## Destructor
    ~vector() {
        while(_size) {
            --_size;
            _alloc.destroy(_data + _size);
        }

        if(_data) {
            _alloc.deallocate(_data, _capacity);
        }
    }
};

template <>
class vector<bool> {

};
// }

#endif