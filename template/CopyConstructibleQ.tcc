#ifndef COPY_CONSTRUCTIBLE_Q_TCC
#define COPY_CONSTRUCTIBLE_Q_TCC

#include <concepts>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <utility>
#include "../defines.h++"
#include "SameQ.tcc"

template < class T >
concept CopyConstructibleQ = requires (T a) {
    requires SameQ< T, decltype (T (a)) >;
    requires SameQ< T &, decltype (a) >;
    requires SameQ< T &, decltype (T (a)) >;
    requires SameQ< T &, decltype (T (std::move (a))) >;
    requires SameQ< T &, decltype (T (std::declval< T & > ())) >;
    requires SameQ< T &, decltype (T (std::declval< T && > ())) >;

    requires SameQ< T &, decltype (T (std::declval< const T & > ())) >;
    requires SameQ< T &, decltype (T (std::declval< volatile T & > ())) >;
    requires SameQ< T &, decltype (T (std::declval< const volatile T & > ())) >;

    requires SameQ< T &, decltype (T (std::declval< const T && > ())) >;
    requires SameQ< T &, decltype (T (std::declval< volatile T && > ())) >;
    requires SameQ< T &, decltype (T (std::declval< const volatile T && > ())) >;

};

#endif
