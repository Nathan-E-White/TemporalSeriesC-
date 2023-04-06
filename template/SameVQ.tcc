#ifndef SAME_VQ_TCC
#define SAME_VQ_TCC

#include <concepts>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include "../defines.h++"
#include "SameQ.tcc"


/* A concept to check if two types are the same */
template < class T, class U >
concept SameVQ = requires (T t, U u) {

    /* Description:   */
    requires std::type_index (typeid (T)) == std::type_index (typeid (U));
    requires std::type_index (typeid (U)) == std::type_index (typeid (T));
    requires std::type_index (typeid (T)) == std::type_index (typeid (T));
    requires std::type_index (typeid (U)) == std::type_index (typeid (U));

    requires std::type_index (typeid (t)) == std::type_index (typeid (u));
    requires std::type_index (typeid (u)) == std::type_index (typeid (t));
    requires std::type_index (typeid (t)) == std::type_index (typeid (t));
    requires std::type_index (typeid (u)) == std::type_index (typeid (u));

    requires std::type_index (typeid (t)) == std::type_index (typeid (T));
    requires std::type_index (typeid (u)) == std::type_index (typeid (U));
    requires std::type_index (typeid (t)) == std::type_index (typeid (U));
    requires std::type_index (typeid (u)) == std::type_index (typeid (T));

    requires std::type_index (typeid (T)) == std::type_index (typeid (t));
    requires std::type_index (typeid (U)) == std::type_index (typeid (u));
    requires std::type_index (typeid (U)) == std::type_index (typeid (t));
    requires std::type_index (typeid (T)) == std::type_index (typeid (u));


    /* Description:   */
    requires std::type_info (typeid (T)) == std::type_info (typeid (U));
    requires std::type_info (typeid (U)) == std::type_info (typeid (T));
    requires std::type_info (typeid (T)) == std::type_info (typeid (T));
    requires std::type_info (typeid (U)) == std::type_info (typeid (U));

    requires std::type_info (typeid (t)) == std::type_info (typeid (u));
    requires std::type_info (typeid (u)) == std::type_info (typeid (t));
    requires std::type_info (typeid (t)) == std::type_info (typeid (t));
    requires std::type_info (typeid (u)) == std::type_info (typeid (u));

    requires std::type_info (typeid (t)) == std::type_info (typeid (T));
    requires std::type_info (typeid (u)) == std::type_info (typeid (U));
    requires std::type_info (typeid (t)) == std::type_info (typeid (U));
    requires std::type_info (typeid (u)) == std::type_info (typeid (T));

    requires std::type_info (typeid (T)) == std::type_info (typeid (t));
    requires std::type_info (typeid (U)) == std::type_info (typeid (u));
    requires std::type_info (typeid (U)) == std::type_info (typeid (t));
    requires std::type_info (typeid (T)) == std::type_info (typeid (u));


    /* Description:   */
    requires std::is_same< T, U >::value;

    /* Nested: SameQ<...> evaluates to true if the types are the same */
    requires SameQ< T *, decltype (& t) >;
    requires SameQ< U *, decltype (& u) >;
    requires SameQ< T *, decltype (& u) >;
    requires SameQ< U *, decltype (& t) >;

};

#endif