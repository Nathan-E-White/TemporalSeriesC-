#ifndef SAME_SIZE_VQ_TCC
#define SAME_SIZE_VQ_TCC

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


namespace Concepts::SameSizeVQ {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedConceptInspection"
    template < class T, class U >
    concept SameSizeVQ = requires (T t, U u) {
        requires sizeof (T) == sizeof (U);
        requires sizeof (U) == sizeof (T);
        requires sizeof (std::declval< T > (t)) == sizeof (T);
        requires sizeof (std::declval< U > (u)) == sizeof (U);
        requires sizeof (std::declval< T > (t)) == sizeof (U);
        requires sizeof (std::declval< U > (u)) == sizeof (T);
    };
#pragma clang diagnostic pop
}

#endif
