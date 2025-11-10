#ifndef ALLOC_H
#define ALLOC_H

#include <cstddef>
#include <type_traits>
#include <new>
#include <limits>

namespace ft{
template <typename T>
struct allocator {
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    template <typename U>
    struct rebind {
        typedef allocator<U> other;
    };

    allocator() throw() {}

    allocator(const allocator& other) throw() {}

    template <typename U>
    allocator(const allocator<U>& other) throw() {}

    ~allocator() {}

    pointer address(reference x) const {
        return &x;
    }

    const_pointer address(const_reference x) const {
        return &x;
    }

    pointer allocate(size_type n, const void* hint = 0) {
        return static_cast<pointer>(::operator new(n*sizeof(T)))
    }

    void deallocate(pointer p, std::size_t n) {
        ::operator delete(p);
    }

    size_type max_size() const throw() {
        return std::numeric_limits<size_type>::max()/sizeof(value_type);
    }

    void construct(pointer p, const_reference val) {
        ::new((void*)p) T(val);
    }

    void destroy(pointer p) {
        p->~T();
    }
};

template <typename T1, typename T2>
bool operator==(const allocator<T1>& lhs, const allocator<T2>& rhs) throw() {
    return true;
}

template <typename T1, typename T2>
bool operator!=(const allocator<T1>& lhs, const allocator<T2>& rhs) throw() {
    return false;
}

template <>
struct allocator<void> {
    typedef void value_type;
    typedef void* pointer;
    typedef const void* const_pointer;

    template <typename U>
    struct rebind {
        typedef allocator<U> other;
    };
};
}

#endif