#ifndef ISI_H
#define ISI_H

namespace ft {
template <typename T, T v>
struct integral_constant {
    static const T value = v;
    typedef T value_type;
    typedef integral_constant<T, v> type;

    operator value_type() const { return value; }
};

template <bool B>
struct bool_constant: integral_constant<bool, B> {};

typedef bool_constant<true> true_type;
typedef bool_constant<false> false_type;

template <typename T> struct is_integral : bool_constant<false>{};

template <> struct is_integral<bool> : bool_constant<true> {};
template <> struct is_integral<char> : bool_constant<true> {};
template <> struct is_integral<signed char> : bool_constant<true> {};
template <> struct is_integral<unsigned char> : bool_constant<true> {};
// template <> struct is_integral<char16_t> : bool_constant<true> {};
// template <> struct is_integral<char32_t> : bool_constant<true> {};
template <> struct is_integral<wchar_t> : bool_constant<true> {};
template <> struct is_integral<short> : bool_constant<true> {};
template <> struct is_integral<unsigned short> : bool_constant<true> {};
template <> struct is_integral<int> : bool_constant<true> {};
template <> struct is_integral<unsigned int> : bool_constant<true> {};
template <> struct is_integral<long> : bool_constant<true> {};
template <> struct is_integral<unsigned long> : bool_constant<true> {};
template <> struct is_integral<long long> : bool_constant<true>{};

template <typename T> struct is_integral<const T> : is_integral<T> {};
template <typename T> struct is_integral<volatile T> : is_integral<T> {};
template <typename T> struct is_integral<const volatile T> : is_integral<T> {};
}

#endif