#ifndef VEC_H
#define VEC_H

#include "allocator.h"
#include "reverse_iterator.h"
#include "iterator.h"
#include "is_integral.h"
#include "enable_if.h"
#include "lexicographical_compare.h"
#include <cstddef>
#include <stdexcept>
#include <iterator>
#include <limits>

namespace ft{
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
    // ## Constructors
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
        _alloc = Allocator();

        _data = _alloc.allocate(other.capacity());
        _capacity = other.capacity();
        _size = other.size();
        for(size_type i = 0 ; i<_size ; ++i) {
            _alloc.construct(_data+i, other[i]);
        }
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

    vector& operator=(const vector& other) {
        clear();

        reserve(other.capacity());
        _size = other.size();

        for(size_type i = 0 ; i<_size ; ++i) {
            _alloc.construct(other[i]);
        }

        return *this;
    }

    void assign(size_type count, const T& value) {
        T val_copy(value);

        clear();

        if(count>_capacity) {
            size_type new_cap = _capacity;
            if(new_cap==0)
                new_cap = 1;

            while(count>new_cap)
                new_cap *= 2;

            reserve(new_cap);
        }

        for(size_type i = 0 ; i<count ; ++i) {
            _alloc.construct(_data+i, val_copy);
        }

        _size = count;
    }

    template <typename InputIt>
    void assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, int>::type* = 0) {
        clear();

        InputIt first_copy = first;
        size_type count = static_cast<size_type>(std::distance(first_copy, last));

        if(count>_capacity) {
            size_type new_cap = _capacity;
            if(new_cap==0)
                new_cap = 1;

            while(count>new_cap)
                new_cap *= 2;

            reserve(new_cap);
        }

        for(size_type i = 0 ; i<count ; ++i) {
            _alloc.construct(_data+i, T(*first));
            ++first;
        }

        _size = count;
    }

    allocator_type get_allocator() const {
        return _alloc;
    }

    reference at(size_type pos) {
        if(pos >= _size)
            throw std::out_of_range("");
        else
            return _data[pos];
    }

    const_reference at(size_type pos) const {
        if(pos >= _size)
            throw std::out_of_range("ft::vector::at");
        else
            return _data[pos];
    }

    reference operator[](size_type pos) {
        return _data[pos];
    }

    const_reference operator[](size_type pos) const {
        return _data[pos];
    }

    reference front() {
        return *_data;
    }

    const_reference front() const {
        return *_data;
    }

    reference back() {
        return _data[_size-1];
    }

    const_reference back() {
        return _data[_size-1];
    }

    T* data() {
        return _data;
    }

    const T* data() const {
        return _data;
    }

    iterator begin() {
        return _data;
    }
    
    const_iterator begin() const {
        return _data;
    }

    iterator end() {
        return _data+_size;
    }

    const_iterator end() const {
        return _data+_size;
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const{
        return reverse_iterator(end());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    bool empty() const {
        if(_size==0)
            return true;
        else
            return false;
    }

    size_type size() const {
        return _size;
    }

    size_type max_size() const {
        size_type alloc_limit = _alloc.max_size();
        size_type diff_limit = static_cast<size_type>(std::numeric_limits<difference_type>::max());

        if (alloc_limit>diff_limit)
            return diff_limit;
        else
            return alloc_limit;
    }

    void reserve(size_type new_cap) {
        if(new_cap > max_size())
            throw std::length_error("ft::vector::reserve");

        if(new_cap <= _capacity)
            return;

        pointer new_data = _alloc.allocate(new_cap);
        size_type new_size = _size;
        size_type new_capacity = new_cap;
        
        size_type i = 0;
        try {
            for( ; i<_size ; ++i)
                _alloc.construct(new_data+i, _data[i]);
        }
        catch(...) {
            for(size_type j = 0 ; j<i ; ++j)
                _alloc.destroy(new_data+j);

            _alloc.deallocate(new_data, new_cap);

            throw;
        }

        while(_size) {
            --_size;
            _alloc.destroy(_data+_size);
        }

        if(_data) {
            _alloc.deallocate(_data, _capacity);
        }

        _data = new_data;
        _size = new_size;
        _capacity = new_capacity;
    }

    size_type capacity() const {
        return _capacity;
    }

    void shrink_to_fit() {
        if(_size==_capacity)
            return;
        
        pointer new_data = _alloc.allocate(_size);
        
        size_type i = 0;
        try {
            for( ; i<_size ; ++i)
                _alloc.construct(new_data+i, _data[i]);
        }
        catch(...) {
            for(size_type j = 0 ; j<i ; ++j)
                _alloc.destroy(new_data+j);

            _alloc.deallocate(new_data, _size);
            
            throw;
        }

        size_type minus = _size;
        while(minus) {
            --minus;
            _alloc.destroy(_data+minus);
        }

        _alloc.deallocate(_data, _capacity);

        _data = new_data;
        _capacity = _size;
    }

    void clear() {
        while(_size) {
            --_size;
            _alloc.destroy(_data+_size);
        }
    }

    iterator insert(const_iterator pos, const T& value) {
        T val_copy(value);
        size_type index = static_cast<size_type>(pos-_data);

        if(_capacity==_size)
            reserve(_capacity ? _capacity*2 : 1);
        
        if(_size) {
            _alloc.construct(_data+_size, _data[_size-1]);
            for(size_type i = _size-1 ; i>index ; --i)
                _data[i] = _data[i-1];

            _data[index] = val_copy;
        }
        else
            _alloc.construct(_data, val_copy);

        ++_size;
        return _data+index;
    }

    iterator insert(const_iterator pos, size_type count, const T& value) {
        size_type index = static_cast<size_type>(pos-_data);

        if(count==0)
            return _data+index;

        T val_copy(value);
        size_type origin_size = _size;

        if(_capacity-_size<count) {
            size_type new_cap = _capacity;
            if(new_cap==0)
                new_cap = 1;
            
            while(new_cap-_size<count)
                new_cap *= 2;

            reserve(new_cap);
        }

        if(_size) {
            for(size_type i = 0 ; i<count ; ++i)
                _alloc.construct(_data+_size+i, val_copy);

            for(size_type i = origin_size ; i-- > index ;) // index가 0이면 평소 하던대로 하면 i--하면 SIZE_MAX로 넘어가가지고 무한루프 걸림
                _data[i+count] = _data[i];

            for(size_type i = 0 ; i<count ; ++i)
                _data[index+i] = val_copy;

            _size += count;
        }
        else {
            for(size_type i = 0 ; i<count ; ++i)
                _alloc.construct(_data+i, val_copy);

            _size = count;
        }

        return _data+index;
    }

    template <typename InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, int>::type* = 0) {
        size_type index = static_cast<size_type>(pos-_data);

        InputIt first_copy = first;
        if(std::distance(first_copy, last)<=0)
            return _data+index;

        size_type origin_size = _size;
        first_copy = first;
        size_type count = static_cast<size_type>(std::distance(first_copy, last));

        if(_capacity-_size<count) {
            size_type new_cap = _capacity;
            if(new_cap==0)
                new_cap = 1;
            
            while(new_cap-_size<count)
                new_cap *= 2;

            reserve(new_cap);
        }

        if(_size) {
            for(size_type i = 0 ; i<count ; ++i)
                _alloc.construct(_data+_size+i, _data[_size-1]);

            for(size_type i = origin_size ; i-- > index ;) // index가 0이면 평소 하던대로 하면 i--하면 SIZE_MAX로 넘어가가지고 무한루프 걸림
                _data[i+count] = _data[i];

            for(size_type i = 0 ; i<count ; ++i) {
                _data[index+i] = T(*first);
                ++first;
            }

            _size += count;
        }
        else {
            for(size_type i = 0 ; i<count ; ++i) {
                _alloc.construct(_data+i, T(*first));
                ++first;
            }

            _size = count;
        }

        return _data+index;
    }

    iterator erase(iterator pos) {
        size_type index = static_cast<size_type>(pos-_data);
        for(size_type i = index ; i<_size-1 ; ++i) {
            _data[i] = _data[i+1];
        }

        --_size;
        _alloc.destroy(_data+_size);

        return _data+index;
    }

    iterator erase(iterator first, iterator last) {
        if(first==last)
            return last;

        size_type first_index = static_cast<size_type>(first-_data);
        size_type last_index = static_cast<size_type>(last-_data);
        size_type count = last_index - first_index;

        for(size_type i = 0 ; i<_size-last_index ; ++i) {
            _data[first_index+i] = _data[last_index+i];
        }

        for(size_type i = 0 ; i<count ; ++i, --_size) {
            _alloc.destroy(_data+_size-1);
        }

        return _data+first_index;
    }

    void push_back(const T& value) {
        T val_copy(value);

        if(_capacity==_size)
            reserve(_capacity ? _capacity*2 : 1);

        _alloc.construct(_data+_size, val_copy);
        ++_size;
    }

    void pop_back() {
        --_size;
        _alloc.destroy(_data+_size);
    }

    void resize(size_type count) {
        if(count==_size)
            return;
        else if(count<_size)
            erase(begin()+count, end());
        else {
            if(count>_capacity)
                reserve(count);

            for(size_type i = 0 ; i < count-_size ; ++i)
                push_back(T());
        }
    }

    void resize(size_type count, const value_type& value) {
        T val_copy(value);

        if(count==_size)
            return;
        else if(count<_size)
            erase(begin()+count, end());
        else {
            if(count>_capacity)
                reserve(count);

            for(size_type i = 0 ; i < count-_size ; ++i)
                push_back(val_copy);
        }
    }

    void swap(vector& other) {
        size_type tmp_size = _size;
        size_type tmp_capacity = _capacity;
        pointer tmp_data = _data;
        allocator_type tmp_alloc = _alloc;

        _size = other._size;
        _capacity = other._capacity;
        _data = other._data;
        _alloc = other._alloc;

        other._size = tmp_size;
        other._capacity = tmp_capacity;
        other._data = tmp_data;
        other._alloc = tmp_alloc;
    }
};

template <typename T, typename Alloc>
bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    if(lhs.size()!=rhs.size())
        return false;

    for(int i = 0 ; i<lhs.size() ; ++i) {
        if(lhs[i]!=rhs[i])
            return false;
    }

    return true;
}

template <typename T, typename Alloc>
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    return !(lhs==rhs);
}

template <typename T, typename Alloc>
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T, typename Alloc>
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template <typename T, typename Alloc>
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    return !(lhs>rhs);
}

template <typename T, typename Alloc>
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    return !(lhs<rhs);
}

template <typename T, typename Alloc>
void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs) {
    lhs.swap(rhs);
}

// template <>
// class vector<bool> {

// };
}

#endif