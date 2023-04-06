#ifndef SEMI_REGULAR_Q_TCC
#define SEMI_REGULAR_Q_TCC

#include <concepts>
#include <type_traits>
#include <typeindex>
#include <typeinfo>


#include "template/SameVQ.tcc"
#include "template/SameQ.tcc"

#include "template/DefaultConstructibleQ.tcc"
#include "template/CopyConstructibleQ.tcc"
#include "template/MoveConstructibleQ.tcc"
#include "template/CopyAssignableQ.tcc"
#include "template/MoveAssignableQ.tcc"
#include "template/DestructibleQ.tcc"
#include "template/EqualityComparableQ.tcc"

#include "defines.h++"


template < class T >
concept SemiregularQ =
DefaultConstructibleQ< T > and
CopyConstructibleQ< T > and
CopyAssignableQ< T > and
DestructibleQ< T > and requires (T a, std::size_t n) {

    /* nested: SameQ<...> evaluates to true if the types are the same */
    requires SameQ< T *, decltype (& a) >;

    /* Compound: a.~T() is a valid expression with no throws */
    { a.~T () } noexcept;

    /* Nested: Same<...> evaluates to true */
    requires SameQ< T *, decltype (new T) >;
    requires SameQ< T *, decltype (new T[n]) >;

    /* Compound */
    { delete new T };
    { delete new T[n] };
};

#endif
