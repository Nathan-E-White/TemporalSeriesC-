#ifndef ADDABLE_Q_TCC
#define ADDABLE_Q_TCC

#include <concepts>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <cmath>
#include <functional>
#include <exception>
#include <cfenv>
#include <climits>
#include <cfloat>
#include <cerrno>
#include <iostream>
#include <tuple>
#include <numeric>
#include "SameVQ.tcc"
#include "../defines.h++"
#include "SameSizeVQ.tcc"
#include "AdditionNoOverflowQ.tcc"
#include "SameQ.tcc"


namespace Concepts::CastableToQ {
    template < class LHS, class RHS >
    concept CastableToQ = requires (LHS lhs, RHS rhs) {
        requires Concepts::SameSizeVQ::SameSizeVQ< LHS, RHS >
                 or SameQ< LHS, RHS >
                 or SameQ< LHS, std::decay_t< RHS>>
                 or SameQ< LHS, std::remove_cv_t< RHS>>
                 or SameQ< LHS, std::remove_reference_t< RHS>>
                 or SameQ< LHS, std::remove_cvref_t< RHS>>
                 or SameQ< LHS, std::remove_cvref_t< std::decay_t< RHS>> >;

    };
}


namespace Concepts::AddableQ {
    template < class LHS, class RHS >
    concept AddableQ =
    std::is_arithmetic_v< LHS > and std::is_arithmetic_v< RHS > and requires (LHS lhs, RHS rhs) {

        requires Concepts::SameSizeVQ::SameSizeVQ< LHS, RHS > or Concepts::CastableToQ::CastableToQ< LHS, RHS >;

        requires (SameQ< LHS, RHS > and
                  Concepts::AdditionNoOverflowQ::AdditionNoOverflowQ< LHS > (lhs, rhs))
                 or (Concepts::CastableToQ::CastableToQ< LHS, RHS >
                     and Concepts::AdditionNoOverflowQ::AdditionNoOverflowQ< LHS >
                             (lhs, rhs));
    };
}

inline auto will_overflow = [] (auto lhs, auto rhs) -> bool {
    return (std::numeric_limits< decltype (lhs) >::max () - lhs) < rhs;
};

inline auto will_underflow = [] (auto lhs, auto rhs) -> bool {
    return (std::numeric_limits< decltype (lhs) >::min () - lhs) > rhs;
};

// TODO(Nate) Move this to a separate file
struct rational_t {

    int64_t numerator;
    int64_t denominator;

    rational_t (std::int64_t numerator, std::int64_t denominator) : numerator (numerator), denominator (denominator) {
        if (denominator == 0) {
            throw std::invalid_argument ("denominator cannot be zero");
        }

        this->simplify ();
    }

    explicit rational_t (std::int64_t numerator) : numerator (numerator), denominator (1) {}

    rational_t () : numerator (0), denominator (1) {}

    rational_t (const rational_t & other) = default;

    rational_t (rational_t && other) noexcept = default;

    rational_t & operator = (const rational_t & other) = default;

    rational_t & operator = (rational_t && other) noexcept = default;

    virtual ~rational_t () = default;


    [[nodiscard]] static constexpr auto equals (const rational_t & lhs, const rational_t & rhs) -> bool {
        return lhs.numerator == rhs.numerator and lhs.denominator == rhs.denominator;
    }

    [[nodiscard]] static constexpr auto less_than (const rational_t & lhs, const rational_t & rhs) -> bool {
        return lhs.numerator * rhs.denominator < rhs.numerator * lhs.denominator;
    }

    [[nodiscard]] static constexpr auto greater_than (const rational_t & lhs, const rational_t & rhs) -> bool {
        return lhs.numerator * rhs.denominator > rhs.numerator * lhs.denominator;
    }

    [[nodiscard]] static constexpr auto less_than_or_equals (const rational_t & lhs, const rational_t & rhs) -> bool {
        return lhs.numerator * rhs.denominator <= rhs.numerator * lhs.denominator;
    }

    [[nodiscard]] static constexpr auto greater_than_or_equals (const rational_t & lhs, const rational_t & rhs) ->
    bool {
        return lhs.numerator * rhs.denominator >= rhs.numerator * lhs.denominator;
    }

    [[nodiscard]] static constexpr auto not_equals (const rational_t & lhs, const rational_t & rhs) -> bool {
        return lhs.numerator != rhs.numerator or lhs.denominator != rhs.denominator;
    }

    [[nodiscard]] static constexpr auto equals (const rational_t & lhs, const int64_t & rhs) -> bool {
        return lhs.numerator == rhs and lhs.denominator == 1;
    }

    [[nodiscard]] static constexpr auto less_than (const rational_t & lhs, const int64_t & rhs) -> bool {
        return lhs.numerator < rhs;
    }

    [[nodiscard]] static constexpr auto greater_than (const rational_t & lhs, const int64_t & rhs) -> bool {
        return lhs.numerator > rhs;
    }

    [[nodiscard]] static constexpr auto less_than_or_equals (const rational_t & lhs, const int64_t & rhs) -> bool {
        return lhs.numerator <= rhs;
    }

    [[nodiscard]] static constexpr auto greater_than_or_equals (const rational_t & lhs, const int64_t & rhs) -> bool {
        return lhs.numerator >= rhs;
    }

    [[nodiscard]] static constexpr auto not_equals (const rational_t & lhs, const int64_t & rhs) -> bool {
        return (lhs.numerator != rhs) or (lhs.denominator != 1);
    }

    auto simplify () -> void {
        auto gcd = std::gcd (this->numerator, this->denominator);
        this->numerator /= gcd;
        this->denominator /= gcd;
    }

    static auto reduce (const rational_t & r) -> rational_t {
        auto gcd = std::gcd (r.numerator, r.denominator);
        return {r.numerator / gcd, r.denominator / gcd};
    }

    static rational_t add (const rational_t & lhs, const rational_t & rhs) {
        auto lcm     = std::lcm (lhs.denominator, rhs.denominator);
        auto new_num = (lhs.numerator + rhs.numerator) * lcm;
        auto out     = rational_t {new_num, lcm};
        return rational_t::reduce (out);
    }

    static rational_t sub (const rational_t & lhs, const rational_t & rhs) {
        auto lcm     = std::lcm (lhs.denominator, rhs.denominator);
        auto new_num = (lhs.numerator - rhs.numerator) * lcm;
        auto out     = rational_t {new_num, lcm};
        return rational_t::reduce (out);
    }

    static rational_t mul (const rational_t & lhs, const rational_t & rhs) {
        auto new_num = lhs.numerator * rhs.numerator;
        auto new_den = lhs.denominator * rhs.denominator;
        auto out     = rational_t {new_num, new_den};
        return rational_t::reduce (out);
    }

    static rational_t div (const rational_t & lhs, const rational_t & rhs) {
        auto new_num = lhs.numerator * rhs.denominator;
        auto new_den = lhs.denominator * rhs.numerator;
        auto out     = rational_t {new_num, new_den};
        return rational_t::reduce (out);
    }

    static rational_t neg (const rational_t & r) {
        return rational_t {-r.numerator, r.denominator};
    }

    // extend std::plus to rational_t
    friend rational_t operator + (const rational_t & lhs, const rational_t & rhs) {
        return rational_t::add (lhs, rhs);
    }

    // extend std::minus to rational_t
    friend rational_t operator - (const rational_t & lhs, const rational_t & rhs) {
        return rational_t::sub (lhs, rhs);
    }

    // extend std::multiplies to rational_t
    friend rational_t operator * (const rational_t & lhs, const rational_t & rhs) {
        return rational_t::mul (lhs, rhs);
    }

    // extend std::divides to rational_t
    friend rational_t operator / (const rational_t & lhs, const rational_t & rhs) {
        return rational_t::div (lhs, rhs);
    }

    // extend std::negate to rational_t
    friend rational_t operator - (const rational_t & r) {
        return rational_t::neg (r);
    }

    // extend std::equal_to to rational_t
    friend bool operator == (const rational_t & lhs, const rational_t & rhs) {
        return rational_t::equals (lhs, rhs);
    }

    // extend std::not_equal_to to rational_t
    friend bool operator != (const rational_t & lhs, const rational_t & rhs) {
        return not(lhs == rhs);
    }

    // extend std::less to rational_t
    friend bool operator < (const rational_t & lhs, const rational_t & rhs) {
        return rational_t::less_than (lhs, rhs);
    }

    // extend std::greater to rational_t
    friend bool operator > (const rational_t & lhs, const rational_t & rhs) {
        return rational_t::greater_than (lhs, rhs);
    }

    // extend std::less_equal to rational_t
    friend bool operator <= (const rational_t & lhs, const rational_t & rhs) {
        return rational_t::less_than_or_equals (lhs, rhs);
    }

    // extend std::greater_equal to rational_t
    friend bool operator >= (const rational_t & lhs, const rational_t & rhs) {
        return rational_t::greater_than_or_equals (lhs, rhs);
    }

    // extend std::equal_to to rational_t and int64_t
    friend bool operator == (const rational_t & lhs, const int64_t & rhs) {
        return rational_t::equals (lhs, rhs);
    }

    // extend std::not_equal_to to rational_t and int64_t
    friend bool operator != (const rational_t & lhs, const int64_t & rhs) {
        return not(lhs == rhs);
    }

    // extend std::less to rational_t and int64_t
    friend bool operator < (const rational_t & lhs, const int64_t & rhs) {
        return rational_t::less_than (lhs, rhs);
    }

    // extend std::greater to rational_t and int64_t
    friend bool operator > (const rational_t & lhs, const int64_t & rhs) {
        return rational_t::greater_than (lhs, rhs);
    }

    // extend std::less_equal to rational_t and int64_t
    friend bool operator <= (const rational_t & lhs, const int64_t & rhs) {
        return rational_t::less_than_or_equals (lhs, rhs);
    }

    // extend std::greater_equal to rational_t and int64_t
    friend bool operator >= (const rational_t & lhs, const int64_t & rhs) {
        return rational_t::greater_than_or_equals (lhs, rhs);
    }

    // extend std::equal_to to int64_t and rational_t
    friend bool operator == (const int64_t & lhs, const rational_t & rhs) {
        return rational_t::equals (rhs, lhs);
    }

    // extend std::not_equal_to to int64_t and rational_t
    friend bool operator != (const int64_t & lhs, const rational_t & rhs) {
        return not(rhs == lhs);
    }

};


using real_h = std::tuple< float, float, std::size_t >;


template < typename Fp > requires std::is_floating_point_v< Fp >
inline auto fp_eq (Fp lhs, Fp rhs) -> bool {
    // TODO(Error handling): check for NaN, Inf, etc... cfenv...
    std::less< Fp > () (std::abs (std::minus< Fp > () (lhs, rhs)) < std::numeric_limits< Fp >::epsilon ());
}

template < typename Fp > requires std::is_floating_point_v< Fp >
inline auto fp_lt (Fp lhs, Fp rhs) -> bool {
    // TODO(Error handling): check for NaN, Inf, etc... cfenv...
    return std::less< Fp > () (std::minus< Fp > () (lhs, rhs), std::numeric_limits< Fp >::epsilon ());
}

template < typename Fp > requires std::is_floating_point_v< Fp >
inline auto fp_gt (Fp lhs, Fp rhs) -> bool {
    // TODO(Error handling): check for NaN, Inf, etc... cfenv...
    return std::greater< Fp > (std::minus< Fp > () (lhs, rhs), std::numeric_limits< Fp >::epsilon ());
}

template < typename Fp > requires std::is_floating_point_v< Fp >
inline auto fp_le (Fp lhs, Fp rhs) -> bool {
    // TODO(Error handling): check for NaN, Inf, etc... cfenv...
    return std::less_equal< Fp > () (std::minus< Fp > () (lhs, rhs), std::numeric_limits< Fp >::epsilon ());
}

template < typename Fp > requires std::is_floating_point_v< Fp >
inline auto fp_ge (Fp lhs, Fp rhs) -> bool {
    // TODO(Error handling): check for NaN, Inf, etc... cfenv...
    return std::greater_equal< Fp > () (std::minus< Fp > () (lhs, rhs), std::numeric_limits< Fp >::epsilon ());
}

// TODO(Nate) Move to a separate file
template < typename Fp, Fp val >
struct FpStaticAnalysis {
    static constinit Fp fp_num    = val;
    static constinit Fp fp_nxt    = std::nextafter (val, std::numeric_limits< Fp >::max ());
    static constinit Fp fp_prv    = std::nextafter (val, std::numeric_limits< Fp >::lowest ());
    static constinit Fp fp_rad_hi = std::abs (fp_nxt) - std::abs (fp_num);
    static constinit Fp fp_rad_lo = std::abs (fp_num) - std::abs (fp_prv);
    static constinit Fp fp_width  = std::plus< Fp > () (fp_rad_hi, fp_rad_lo);

    static constexpr bool is_nan       = std::isnan (val);
    static constexpr bool centered     = fp_eq< Fp > (fp_rad_hi, fp_rad_lo);
    static constexpr bool is_zero      = fp_eq< Fp > (val, 0);
    static constexpr bool is_inf       = std::isinf (val);
    static constexpr bool is_pos_inf   = is_inf and fp_gt< Fp > (val, 0);
    static constexpr bool is_neg_inf   = is_inf and fp_lt< Fp > (val, 0);
    static constexpr bool is_finite    = (not is_nan and not is_inf);
    static constexpr bool is_subnormal = (is_finite and (std::abs (fp_num) < std::numeric_limits< Fp >::min ()));
    static constexpr bool is_normal    = (is_finite and (std::abs (fp_num) >= std::numeric_limits< Fp >::min ()));
    static constexpr bool is_denormal  =
                                  (is_subnormal and (std::abs (fp_num) > std::numeric_limits< Fp >::denorm_min ()));
    static constexpr bool is_snan      = (is_nan and (fp_eq< Fp > (fp_rad_hi, 0)));
    static constexpr bool is_qnan      = (is_nan and (not fp_eq< Fp > (fp_rad_hi, 0)));
    static constexpr bool is_signaling = (is_snan or is_qnan);
    static constexpr bool is_quiet     = (not is_signaling);
    static constexpr bool is_positive  = (is_finite and (fp_gt< Fp > (val, 0)));
    static constexpr bool is_negative  = (is_finite and (fp_lt< Fp > (val, 0)));
    static constexpr bool is_nonzero   = (is_finite and (not is_zero));
    static constexpr bool is_odd       = (is_finite and ((val % 0x2) != 0));
    static constexpr bool is_even      = (is_finite and ((val % 0x2) == 0));
    static constexpr bool is_integer   = (is_finite and ((val % 1) == 0));
};


// TODO(Nate) Move to a separate file
template < class Fp >
concept FloatingPointEquality = std::is_floating_point_v< Fp > and requires (Fp lhs, Fp rhs) {

    // use the delta-epsilon method to compare floating point numbers
    requires std::abs(lhs - rhs) <= std::numeric_limits< Fp >::epsilon ();

    // check that next highest value after lhs is greater than rhs
    requires std::abs(
                             std::nextafter (lhs, std::numeric_limits< Fp >::max ()) -
                             std::nextafter (rhs, std::numeric_limits< Fp >::max ())
                     ) <= std::numeric_limits< Fp >::epsilon ();
};


#endif