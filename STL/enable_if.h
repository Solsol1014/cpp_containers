#ifndef EIF_H
#define EIF_H

namespace ft{
template <bool B, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> { typedef T type; };
}

#endif