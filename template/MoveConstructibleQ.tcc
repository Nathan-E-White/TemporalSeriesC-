//
// Created by Nathan White on 11/22/22.
//

#ifndef TEMPORAL_SERIES_CPP23_MOVECONSTRUCTIBLEQ_TCC
#define TEMPORAL_SERIES_CPP23_MOVECONSTRUCTIBLEQ_TCC

#include <concepts>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <utility>

#include "../defines.h++"
#include "SameQ.tcc"


template < class T >
concept MoveConstructibleQ = requires (T t) {
    requires SameQ< T, decltype (T (std::move (t))) >;
    requires std::is_nothrow_move_constructible_v< T >;
};

template < class T > requires MoveConstructibleQ< T >
struct MoveConstructibleType {
    using type = T;
};


#endif //TEMPORAL_SERIES_CPP23_MOVECONSTRUCTIBLEQ_TCC
