#ifndef NEW_H
#define NEW_H

#include <cstddef>

// namespace ft{
struct nothrow_t {};
extern const nothrow_t nothrow;

// Replaceable allocation functions
void* operator new(std::size_t count);
void* operator new[](std::size_t count);

// Replaceable non-throwing allocation functions
void* operator new(std::size_t count, const nothrow_t& tag);
void* operator new[](std::size_t count, const nothrow_t& tag);

// Non-allocating placement allocation functions
void* operator new(std::size_t count, void* ptr);
void* operator new[](std::size_t count, void* ptr);

// User-defined placement allocation functions
void* operator new(std::size_t count, )
// }

#endif