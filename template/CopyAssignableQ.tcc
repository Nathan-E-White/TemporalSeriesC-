#ifndef COPY_ASSIGNABLE_Q_TCC
#define COPY_ASSIGNABLE_Q_TCC

#include <concepts>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <utility>
#include "../defines.h++"
#include "SameQ.tcc"


/* A concept that is satisfied by types that can be copy assigned */
template < class T >
concept CopyAssignableQ = requires (T t) {

    /* Nested: SameQ<...> evaluates to true if the types are the same */
    requires SameQ< T &, decltype (t = t) >;

    /* Compound: t = t is a valid expression with no throws */
    { t = t } noexcept;
};


/* Copy Assignable Type Helper */
template < class T > requires CopyAssignableQ< T >
struct CopyAssignableType {
    using type = T;
};

#endif
