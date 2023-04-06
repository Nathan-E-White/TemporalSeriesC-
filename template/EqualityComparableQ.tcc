#ifndef EQUALITY_COMPARABLE_Q_TCC
#define EQUALITY_COMPARABLE_Q_TCC

#include <concepts>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <utility>
#include "../defines.h++"
#include "SameQ.tcc"


/* A concept that is satisfied by types that can be compared for equality */
template < class T >
concept EqualityComparableQ = requires (T a, T b) {
    /* Nested: SameQ<...> evaluates to true if the types are the same */
    requires SameQ< bool, decltype (a == b) >;
    requires SameQ< bool, decltype (a != b) >;

    /* Compound: a == b is a valid expression with no throws */
    { a == b } noexcept;
    { a != b } noexcept;
};


/* A type helper that is satisfied by types that can be compared for equality */
template < class T > requires EqualityComparableQ< T >
struct EqualityComparableType {
    static constexpr bool value = true;
};


#endif
