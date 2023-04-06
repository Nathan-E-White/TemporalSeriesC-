#ifndef TEMPORAL_DATA_POINT_TCC
#define TEMPORAL_DATA_POINT_TCC

#include <cstddef>
#include <array>
#include <concepts>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include "defines.h++"


template < class I >
concept NotVoid = !std::is_void_v< I >;

template < class I >
concept Dereferenceable = requires (I i) {
    * i;

    { ( void ) * i } -> std::same_as< decltype (* i) >;
    { * i } -> std::same_as< decltype (* i) >;
};

template < class I >
concept Incrementable = requires (I i) {
    ++i;
};

template < class I >
concept Referencable = requires (I i) {
    requires NotVoid< I >(i);
    { i.data () } -> std::same_as< std::add_lvalue_reference_t< std::remove_reference_t< decltype (i.data ()) > > >;
};


// concept satisfied if we have a legacy iterator
template < typename It >
concept LegacyIterator = requires (It r) {

    typename It::iterator_category;
    typename It::difference_type;
    typename It::pointer;
    typename It::reference;

    requires std::copy_constructible< It >(r);
    requires std::is_copy_assignable< It >(r);
    requires std::is_destructible< It >(r);

    // L-values must be swappable
    requires std::is_swappable< It >(r);

    requires Dereferenceable< It >(r);
    requires Incrementable< It >(r);

    { * r } -> Referencable;
    { ++r } -> std::same_as< It & >;
    { * r++ } -> Referencable;
    requires std::copyable< It >(r);

};


template < class I >
concept LegacyInputIterator = LegacyIterator< I > && requires (I i, I j) {

    requires std::equality_comparable< I > (i);
    requires std::iterator_traits< I >::reference;
    requires std::iterator_traits< I >::value_type;

    // given values i and j of type I, the expression i == j shall be well-formed and have a contextually converted type (Clause 4) that is EqualityComparable
    { i == j } -> std::convertible_to< bool >;
    { j == i } -> std::convertible_to< bool >;
    { i != j } -> std::convertible_to< bool >;
    { j != i } -> std::convertible_to< bool >;


    // I must have lvalue
    requires std::is_lvalue_reference_v< decltype (i) >;

    typename std::incrementable_traits< I >::difference_type;
    typename std::indirectly_readable_traits< I >::value_type;
    typename std::common_reference_t<
            std::iter_reference_t< I > &&,
            typename std::indirectly_readable_traits< I >::value_type &
    >;
    * i++;
    typename std::common_reference_t<
            decltype (* i++) &&,
            typename std::indirectly_readable_traits< I >::value_type &
    >;

    requires std::signed_integral< typename std::incrementable_traits< I >::difference_type >;


};

template < class I >
concept LegacyOutputIterator = LegacyIterator< I > && requires (I o, I r) {

    // must be class type or pointer type
    requires std::is_class_v< I > || std::is_pointer_v< I >;

    requires Dereferenceable< I >(r);
    * r = o;
    requires Incrementable< I >(r);

    // ++r must have an lvalue of type I
    requires std::is_lvalue_reference_v< decltype (++r) >;

    // r++ is convertible to const I&
    requires std::convertible_to< decltype (r++), const I & >;

    // *r++ = o
    * r++ = o;

};

// legacy forward iterator concept
template < class I >
concept LegacyForwardIterator = LegacyInputIterator< I > && requires (I i, I j) {

    // I must be swappable
    requires std::is_swappable< I >(i);

    // I must be copyable
    requires std::copyable< I >(i);

    // I must be assignable
    requires std::assignable_from< I &, I >(i);

    // I must be equality comparable
    requires std::equality_comparable< I >(i);

    // I must be incrementable
    requires Incrementable< I >(i);

    // I must be dereferenceable
    requires Dereferenceable< I >(i);

};


template < typename Data, std::size_t Arity >
class TemporalDataPoint {

private:    /* Data Types */

    typedef TemporalDataPoint< Data, Arity > Self;
    typedef TemporalDataPoint< Data, Arity >       & Self_rref;
    typedef const TemporalDataPoint< Data, Arity > & Self_crref;
    typedef TemporalDataPoint< Data, Arity >       && Self_move;
    typedef std::reference_wrapper< Self >       Self_ref;
    typedef std::reference_wrapper< const Self > Self_cref;
    typedef std::array< Data, Arity >            DataArray;
    typedef DataArray & DataArray_rref;
    typedef DataArray && DataArray_move;
    typedef std::reference_wrapper< DataArray > DataArray_ref;
    typedef Data                                data_t;
    typedef Data       & data_rref;
    typedef const Data & data_crref;
    typedef Data       && data_move;
    typedef std::reference_wrapper< Data >       data_ref;
    typedef std::reference_wrapper< const Data > data_cref;


private:    /* Private Class Data */
    std::array< data_ref, Arity > m_data_ref;

public:     /* Public Class Data */

public:     /* Default constructor */
    NOD TemporalDataPoint ();

public:     /* Copy constructor */
    NOD TemporalDataPoint (Self_crref);

public:     /* Move constructor */
    NOD TemporalDataPoint (Self_move) noexcept;

public:     /* Virtual Destructor */
    NRS virtual ~TemporalDataPoint ();

public:     /* Copy assignment operator */
    NOD Self_rref operator = (Self_crref);

public:     /* Move assignment operator */
    NOD Self_rref operator = (Self_move) noexcept;

private:    /* Private Methods */

public:     /* Public Class Methods */

    // iterators
    NOD auto begin ();

    NOD auto end ();

    NOD auto cbegin () const;

    NOD auto cend () const;

    NOD auto & rbegin ();

    NOD auto & rend ();

    NOD auto & crbegin () const;

    NOD auto & crend () const;

    // capacity
    NOD bool empty () const;

    NOD std::size_t size () const;

    NOD std::size_t max_size () const;

    // element access
    NOD auto at (std::size_t index);

    NOD auto at (std::size_t index) const;

    NOD auto operator [] (std::size_t index);

    NOD auto operator [] (std::size_t index) const;


    /**
     * @brief Interface function for std::array<T,N>::front()
     * @tparam Data - the type of data stored in the array
     * @tparam Arity - the number of elements in the array
     * @return std::common_reference_t< std::reference_wrapper< Data>>
     * @since C++17
     * @complexity constant
     * @see https://en.cppreference.com/w/cpp/container/array/front
     * @note On error, will std::cerr and exit the program
     * @dependencies <cstddef>, <array>, <iostream>, <cstdlib>, "defines.h++"
     * @example TODO
     * @bug No known bugs
     * @warning No known warnings
     * @version 1.0.0
     *
     * @author Nathan E White, PhD
     * @date 2022-11-19
     */
    NOD constexpr auto
    front () -> std::common_reference_t< std::reference_wrapper< Data>>;

    /**
     * @brief Interface function for std::array<T,N>::front() const
     * @tparam Data - the type of data stored in the array
     * @tparam Arity - the number of elements in the array
     * @return std::common_reference_t< std::reference_wrapper< const Data>>
     * @since C++14
     * @complexity constant
     * @see https://en.cppreference.com/w/cpp/container/array/front
     * @note On error, will std::cerr and exit the program
     * @dependencies <cstddef>, <array>, <iostream>, <cstdlib>, "defines.h++"
     * @example TODO
     * @bug No known bugs
     * @warning No known warnings
     * @version 1.0.0
     *
     * @author Nathan E White, PhD
     * @date 2022-11-19
     */
    NOD constexpr auto
    front () const -> std::common_reference_t< std::reference_wrapper< const Data>>;


    /**
     * @brief Returns a reference to the last element in the container.
     * @tparam Data  - The type of data stored in the container.
     * @tparam Arity - the number of elements in the array
     * @return std::common_reference_t<std::reference_wrapper<Data>>
     * @since C++17
     * @complexity constant
     * @see https://en.cppreference.com/w/cpp/container/array/back
     * @note On error, will std::cerr the error message and exit the program.
     * @dependencies <array>, <iostream>, <cstdlib>, <exception>, ...
     * @example TODO
     * @bug No known bugs
     * @warning No known warnings
     * @version 1.0.0
     *
     * @author Nathan E White, PhD
     * @date 2022-11-19
     */
    NOD constexpr auto
    back () -> std::common_reference_t< std::reference_wrapper< Data>>;


    /**
     * @brief Returns a reference to the last element in the container.
     * @tparam Data  - The type of data stored in the container.
     * @tparam Arity - the number of elements in the array
     * @return std::common_reference_t<std::reference_wrapper<const Data>>
     * @since C++14
     * @complexity constant
     * @see https://en.cppreference.com/w/cpp/container/array/back
     * @note On error, will std::cerr the error message and exit the program.
     * @dependencies <array>, <iostream>, <cstdlib>, <exception>, ...
     * @example TODO
     * @bug No known bugs
     * @warning No known warnings
     * @version 1.0.0
     *
     * @author Nathan E White, PhD
     * @date 2022-11-19
     */
    NOD constexpr auto
    back () const -> std::common_reference_t< std::reference_wrapper< const Data>>;


    /**
     * @brief Returns a pointer to array's underlying element storage.
     * @tparam Data  - The type of data stored in the container.
     * @tparam Arity - the number of elements in the array
     * @return std::add_pointer_t<std::add_lvalue_reference_t<Data>>
     * @since C++17
     * @complexity constant
     * @see https://en.cppreference.com/w/cpp/container/array/data
     * @note Will not throw an exception.
     * @dependencies <array>, <type_traits>, <utility>
     * @example TODO
     * @bug No known bugs
     * @warning No known warnings
     * @version 1.0.0
     *
     * @author Nathan E White, PhD
     * @date 2022-11-18
     */
    NOD constexpr
    auto data () noexcept -> std::add_pointer_t< std::reference_wrapper< Data >>;


    /**
     * @brief Returns a pointer to array's underlying element storage.
     * @tparam Data  - The type of data stored in the container.
     * @tparam Arity - the number of elements in the array
     * @return std::add_pointer_t<std::add_lvalue_reference_t<const Data>>
     * @since C++17
     * @complexity constant
     * @see https://en.cppreference.com/w/cpp/container/array/data
     * @note Will not throw an exception.
     * @dependencies <array>, <type_traits>, <utility>
     * @example TODO
     * @bug No known bugs
     * @warning No known warnings
     * @version 1.0.0
     *
     * @author Nathan E White, PhD
     * @date 2022-11-18
     */
    NOD constexpr
    auto data () const noexcept -> std::add_pointer_t< std::reference_wrapper< Data >>;


    /**
     * @brief Interface function for std::array<T,N>::fill(...)
     * @details Fills the array with the given value.
     * @tparam Data - the type of data stored in the array
     * @tparam Arity - the number of elements in the array
     * @param value - the value to fill the array with
     * @return void
     * @since C++20
     * @complexity O(N) -- linear in the size of the array
     * @see https://en.cppreference.com/w/cpp/container/array/fill
     * @note On error, will std::cerr and exit the program
     * @dependencies <cstddef>, <array>, <iostream>, <cstdlib>, "defines.h++"
     * @example TODO
     * @bug No known bugs
     * @warning No known warnings
     * @version 1.0.0
     *
     * @author Nathan E White, PhD
     * @date 2022-11-19
     */
    NRS constexpr auto fill (const data_t & value) -> void;

    /// Niebloid fill, <algorithm> version
    template < class T, std::output_iterator< const T & > O, std::sentinel_for< O > S >
    NRS constexpr auto fill (O first, S last, const T & value) const -> O;

    /// Niebloid fill, <algorithm> version
    template < class T, std::ranges::output_range< const T & > R >
    NOD constexpr auto fill (R && r, const T & value) const -> std::ranges::borrowed_iterator_t< R >;

    /// Niebloid fill, <algorithm> version
    template < class T, std::output_iterator< const T & > O >
    NOD constexpr auto fill_n (O first, std::iter_difference_t< O > n, const T & value) const -> O;


    template < class InputIt, class Size, class OutputIt >
    requires LegacyInputIterator< InputIt > && LegacyOutputIterator< OutputIt >
    NOD constexpr auto copy_n (InputIt first, Size count, OutputIt result) const -> OutputIt;

    template < class ExecutionPolicy, class ForwardIt1, class Size, class ForwardIt2 >
    requires std::is_execution_policy_v< std::decay_t< ExecutionPolicy>> &&
             std::is_execution_policy_v< std::remove_cvref_t< ExecutionPolicy>> &&
             LegacyForwardIterator< ForwardIt1 > && LegacyForwardIterator< ForwardIt2 >
    NOD auto copy_n (ExecutionPolicy && policy, ForwardIt1 first, Size count, ForwardIt2 result) -> ForwardIt2;

    /// Niebloid fill, <algorithm> version
    template < class I, class O >
    using copy_n_result = std::ranges::in_out_result< I, O >;

    template < std::input_iterator I, std::weakly_incrementable O > requires std::indirectly_copyable< I, O >
    constexpr auto copy_n (I first, std::iter_difference_t< I > n, O result) -> copy_n_result< I, O >;




    /**
     * @brief Interface function for std::array<T,N>::swap(...)
     * @details Exchanges the contents of the container with those of other.
     * @tparam Data - the type of data stored in the array
     * @tparam Arity - the number of elements in the array
     * @param other  - the array to swap with
     * @return (none)
     * @since C++20
     * @complexity O(N) -- linear in the size of the array
     * @see https://en.cppreference.com/w/cpp/container/array/swap
     * @note On error, will std::cerr and exit the program
     * @node This function will not throw exceptions if the array is empty.
     * @dependencies TODO
     * @example TODO
     * @bug No known bugs
     * @warning No known warnings
     * @version 1.0.0
     *
     * @author Nathan E White, PhD
     * @date 2022-11-19
     */
    NRS auto constexpr swap (std::common_reference_t< std::reference_wrapper< Data >> other) noexcept
    (std::is_nothrow_swappable_v< std::reference_wrapper< Data >>) -> void;

    bool clear ();

    static bool clear (Self_ref);

public:     /* Getters */



public:     /* Setters */

};


#endif
