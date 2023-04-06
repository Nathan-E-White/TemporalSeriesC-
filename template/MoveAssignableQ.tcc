#ifndef MOVE_ASSIGNABLE_Q_TCC
#define MOVE_ASSIGNABLE_Q_TCC

#include <concepts>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <utility>
#include "../defines.h++"
#include "SameQ.tcc"


/* A concept that is satisfied by types that can be move assigned */
template < class T >
concept MoveAssignableQ = requires (T t) {

    /* Nested: SameQ<...> evaluates to true if the types are the same */
    requires SameQ< T &, decltype (t = std::move (t)) >;

    /* Compound: t = std::move(t) is a valid expression with no throws */
    { t = std::move (t) } noexcept;
};

/* Move Assignable Type Helper */
template < class T > requires MoveAssignableQ< T >
struct MoveAssignableType {
    using type = T;
};


#endif
