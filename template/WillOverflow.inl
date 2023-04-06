#ifndef WILL_OVERFLOW_INL
#define WILL_OVERFLOW_INL


#include <functional>
#include <numeric>


template < typename N > requires std::is_arithmetic_v< N >
extern constinit std::function< bool (N, N) > AdditionOverflowQ;


extern "C++" int idx;

#endif
