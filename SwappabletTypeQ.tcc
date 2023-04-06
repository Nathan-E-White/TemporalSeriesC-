#ifndef SWAPPABLE_CONCEPT_TYPE_TCC
#define SWAPPABLE_CONCEPT_TYPE_TCC

#include <concepts>
#include <typeindex>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include "defines.h++"


template < class T, class U >
concept IsSwappableWithV = std::is_swappable_with_v< T, U > and std::is_swappable_with_v< U, T >;


template < class T, class U >
concept IsSwappableWith = requires (T t, U u)  {
    requires std::is_swappable_with< T, U >(t, u);
    requires std::is_swappable_with< U, T >(u, t);
};

template < class T, class U >
concept IsNoThrowSwappableWithV = std::is_nothrow_swappable_with_v< T, U > and std::is_nothrow_swappable_with_v< U, T >;

template < class T, class U >
concept IsNoThrowSwappableWith = requires (T t, U u) {
    requires std::is_nothrow_swappable_with< T, U >(t, u);
    requires std::is_nothrow_swappable_with< U, T >(u, t);
};

template < class T >
concept IsNoThrowSwappableV = std::is_nothrow_swappable_v< T >;

template < class T >
concept IsNoThrowSwappable = requires (T t) {
    requires std::is_nothrow_swappable< T >(t);
};

template < class T >
concept LValuesSwappableV = std::is_swappable_v< T > and std::is_swappable_v< T & > and std::is_swappable_v< T && >;

template < class T >
concept LValuesSwappable = requires (T t) {
    requires std::is_swappable< T >(t);
    requires std::is_swappable< T & >(t);
    requires std::is_swappable< T && >(t);
};

template < class T >
concept RValuesSwappableV = std::is_swappable_v< T > and std::is_swappable_v< T & > and std::is_swappable_v< T && >;

template < class T >
concept RValuesSwappable = requires (T t) {
    requires std::is_swappable< T >(t);
    requires std::is_swappable< T & >(t);
    requires std::is_swappable< T && >(t);
};



template < typename T, typename U >
concept SwappableTypeQ =
IsSwappableWithV< T, U > and
IsSwappableWithV< T, U > and
IsNoThrowSwappableV< T > and
IsNoThrowSwappableV< U > and
IsSwappableWithV< T, U > and
IsSwappableWithV< T, U > and
LValuesSwappableV< T > and
LValuesSwappableV< U > and
RValuesSwappableV< T > and
RValuesSwappableV< U > and
IsNoThrowSwappableWithV< T, U > and
IsNoThrowSwappableWithV< U, T > and requires (T t, U u) {
    requires std::type_index (typeid (T)) == std::type_index (typeid (U));
    requires std::type_info (typeid (T)) == std::type_info (typeid (U));
    requires std::is_swappable< T >::value;
    requires std::is_swappable< U >::value;

    requires IsNoThrowSwappable< T >;
    requires IsNoThrowSwappable< U >;

    requires LValuesSwappable< T >(t);
    requires LValuesSwappable< U >(u);
    requires RValuesSwappable< T >(t);
    requires RValuesSwappable< U >(u);

    requires IsSwappableWith< T, U >(t, u);
    requires IsSwappableWith< U, T >(u, t);


    requires IsNoThrowSwappableWith< T, U >(t, u);
    requires IsNoThrowSwappableWith< U, T >(u, t);

    { std::swap (t, u) };
    { std::swap (t, u) } -> std::same_as< void >;
    { std::swap (u, t) } -> std::same_as< void >;
};


template < class T, class U >
struct NOD SwappableTypeHelper {

    NS static const constinit bool
            value = SwappableTypeQ< T, U >;
};

template < class T, class U >
using SwappableType = SwappableTypeHelper< T, U >;

#endif
