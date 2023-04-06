//
// Created by Nathan White on 11/22/22.
//

#ifndef TEMPORAL_SERIES_CPP23_DEFAULTCONSTRUCTIBLEQ_TCC
#define TEMPORAL_SERIES_CPP23_DEFAULTCONSTRUCTIBLEQ_TCC

#include <concepts>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include "../defines.h++"
#include "SameQ.tcc"

// concept DefaultConstructibleQ
template < class T >
concept DefaultConstructibleQ = requires () {

    // Nested: SameQ<...> evaluates to true if the types are the same
    requires SameQ< T *, decltype (new T) >;

    // Compound: new T() is a valid expression with no throws
    { new T } noexcept;
};


#endif //TEMPORAL_SERIES_CPP23_DEFAULTCONSTRUCTIBLEQ_TCC
