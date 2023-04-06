#include <iostream>


#include <functional>
#include <numeric>
#include <cmath>


template < typename R, typename I >
using unary_operator = std::function< R (I) >;

template < typename I >
using unary_predicate = std::function< bool (I) >;

template < typename R, typename LHS, typename RHS >
using binary_operator = std::function< R (LHS, RHS) >;

template < typename LHS, typename RHS >
using binary_predicate = std::function< bool (LHS, RHS) >;

template < typename R, typename ... Inp >
using variadic_operator = std::function< R (Inp...) >;

template < typename ... Inp >
using variadic_predicate = std::function< bool (Inp...) >;

template < typename N > requires std::is_arithmetic_v< N >
auto addition = binary_operator< N, N, N > (
        [] (N lhs, N rhs) -> N {
            return std::plus< N > () (lhs, rhs);
        }
);


// unary predicate: PositiveQ
// returns true iff the argument is positive
template < typename N > requires std::is_arithmetic_v< N >
auto positiveQ = unary_predicate< N > (
        [] (N n) -> bool {
            return n > 0;
        }
);

// unary predicate: NegativeQ
// returns true iff the argument is negative
template < typename N > requires std::is_arithmetic_v< N >
auto negativeQ = unary_predicate< N > (
        [] (N n) -> bool {
            return n < 0;
        }
);

// unary predicate: ZeroQ
// returns true iff the argument is zero
template < typename N > requires std::is_arithmetic_v< N >
auto zeroQ = unary_predicate< N > (
        [] (N n) -> bool {
            return n == 0;
        }
);

// unary predicate: NonZeroQ
// returns true iff the argument is non-zero
template < typename N > requires std::is_arithmetic_v< N >
auto nonZeroQ = unary_predicate< N > (
        [] (N n) -> bool {
            return n != 0;
        }
);

// unary predicate: EvenQ
// returns true iff the argument is even
template < typename N > requires std::is_arithmetic_v< N >
auto evenQ = unary_predicate< N > (
        [] (N n) -> bool {
            return n % 2 == 0;
        }
);

// unary predicate: OddQ
// returns true iff the argument is odd
template < typename N > requires std::is_arithmetic_v< N >
auto oddQ = unary_predicate< N > (
        [] (N n) -> bool {
            return n % 2 != 0;
        }
);

// unary predicate: NonPositiveQ
// returns true iff the argument is non-positive
template < typename N > requires std::is_arithmetic_v< N >
auto nonPositiveQ = unary_predicate< N > (
        [] (N n) -> bool {
            return n <= 0;
        }
);

// unary predicate: NonNegativeQ
// returns true iff the argument is non-negative
template < typename N > requires std::is_arithmetic_v< N >
auto nonNegativeQ = unary_predicate< N > (
        [] (N n) -> bool {
            return n >= 0;
        }
);

// unary predicate: IntegerQ
// returns true iff the argument is an integer
template < typename N > requires std::is_arithmetic_v< N >
auto integerQ = unary_predicate< N > (
        [] (N n) -> bool {
            return n == std::floor (n);
        }
);

// unary predicate: PositiveIntegerQ
// returns true iff the argument is a positive integer
template < typename N > requires std::is_arithmetic_v< N >
auto positiveIntegerQ = unary_predicate< N > (
        [] (N n) -> bool {
            return std::logical_and (integerQ< N > (n), positiveQ< N > (n));
        }
);

// unary predicate: NegativeIntegerQ
// returns true iff the argument is a negative integer
template < typename N > requires std::is_arithmetic_v< N >
auto negativeIntegerQ = unary_predicate< N > (
        [] (N n) -> bool {
            return std::logical_and (integerQ< N > (n), negativeQ< N > (n));
        }
);

// unary predicate: NonPositiveIntegerQ
// returns true iff the argument is a non-positive integer
template < typename N > requires std::is_arithmetic_v< N >
auto nonPositiveIntegerQ = unary_predicate< N > (
        [] (N n) -> bool {
            return std::logical_and (integerQ< N > (n), nonPositiveQ< N > (n));
        }
);

// unary predicate: NonNegativeIntegerQ
// returns true iff the argument is a non-negative integer
template < typename N > requires std::is_arithmetic_v< N >
auto nonNegativeIntegerQ = unary_predicate< N > (
        [] (N n) -> bool {
            return std::logical_and (integerQ< N > (n), nonNegativeQ< N > (n));
        }
);



int main () {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
