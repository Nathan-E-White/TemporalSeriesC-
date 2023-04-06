#ifndef SAME_Q_TCC
#define SAME_Q_TCC

#include "../defines.h++"
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <concepts>

template < class T, class U >
concept SameQ = std::same_as< T, U > and std::same_as< U, T >;

#endif
