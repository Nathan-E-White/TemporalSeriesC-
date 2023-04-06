#ifndef DESTRUCTIBLE_Q_TCC
#define DESTRUCTIBLE_Q_TCC

#include <concepts>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <utility>
#include "../defines.h++"
#include "SameQ.tcc"


/* A concept that is satisfied by types that can be destructed */
template < class T >
concept DestructibleQ = requires (T a) {

    /* Nested: SameQ<...> evaluates to true if the types are the same */
    requires SameQ< T *, decltype (& a) >;

    /* Compound: a.~T() is a valid expression with no throws */
    { a.~T () } noexcept;
};


/* Type helper struct */
template < class T > requires DestructibleQ< T >
struct DestructibleType {
    using type = T;
};


#endif
