#ifndef ADDITION_NO_OVERFLOW_Q_TCC
#define ADDITION_NO_OVERFLOW_Q_TCC

#include "SameSizeVQ.tcc"
#include "../defines.h++"
#include "SameVQ.tcc"
#include <numeric>
#include <tuple>
#include <iostream>
#include <cerrno>
#include <cfloat>
#include <climits>
#include <cfenv>
#include <exception>
#include <functional>
#include <cmath>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <concepts>


namespace Concepts::AdditionNoOverflowQ {

    template < typename T >
    concept AdditionNoOverflowQ = requires (T lhs, T rhs) {
        // enforce that lhs + rhs will not overflow
        requires (std::numeric_limits< T >::max () - lhs) >= rhs;
    };
}


#endif