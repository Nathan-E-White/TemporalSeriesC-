#ifndef WILL_OVERFLOW_TCC
#define WILL_OVERFLOW_TCC

#include <concepts>
#include <functional>
#include <numeric>
#include <type_traits>
#include <utility>

#include "WillOverflow.inl"

template <typename N>
requires std::is_arithmetic_v< N >
auto WillOverflow() -> std::function< bool (N, N) >;

template <typename N>
requires std::is_arithmetic_v< N >
auto WillOverflow() -> std::function< bool (N, N) > {
    return will_overflow< N >;
};


#endif