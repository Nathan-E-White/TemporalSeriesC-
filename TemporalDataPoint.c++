#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <execution>
#include <concepts>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include "TemporalDataPoint.tcc"


template < typename Data, std::size_t Arity >
NOD TemporalDataPoint< Data, Arity >::TemporalDataPoint () = default;


template < typename Data, std::size_t Arity >
NOD TemporalDataPoint< Data, Arity >::TemporalDataPoint (const TemporalDataPoint< Data, Arity > & other) = default;

template < typename Data, std::size_t Arity >
NOD TemporalDataPoint< Data, Arity >::TemporalDataPoint (TemporalDataPoint< Data, Arity > && other) noexcept = default;

template < typename Data, std::size_t Arity >
NRS TemporalDataPoint< Data, Arity >::~TemporalDataPoint () = default;

template < typename Data, std::size_t Arity >
TemporalDataPoint< Data, Arity > &
NOD TemporalDataPoint< Data, Arity >::operator = (const TemporalDataPoint< Data, Arity > & other) = default;

template < typename Data, std::size_t Arity >
TemporalDataPoint< Data, Arity > &
NOD TemporalDataPoint< Data, Arity >::operator = (TemporalDataPoint< Data, Arity > && other) noexcept = default;


template < typename Data, std::size_t Arity >
NOD bool
TemporalDataPoint< Data, Arity >::clear () {

    // lambda function to clear the data
    auto clear_data = [] (auto & data) {
        data.clear ();
    };

    /* Is there data to clear? */
    if (TemporalDataPoint::m_data_ref.empty ()) {
        return false;
    }

    /* Clear the data */
    std::for_each (
            TemporalDataPoint::m_data_ref.begin (),
            TemporalDataPoint::m_data_ref.end (),
            clear_data
    );

    return true;

}


template < typename Data, std::size_t Arity >
NOD constexpr
std::common_reference_t< std::reference_wrapper< Data>>
TemporalDataPoint< Data, Arity >::front () {
    // TODO(???): Is wrapping with std::common_reference necessary?
    return std::common_reference< std::reference_wrapper< Data>> (this->m_data_ref.front ());
}


template < typename Data, std::size_t Arity >
NOD constexpr
std::common_reference_t< std::reference_wrapper< const Data>>
TemporalDataPoint< Data, Arity >::front ()
const {
    return this->m_data_ref.front ();
}


template < typename Data, std::size_t Arity >
NOD constexpr auto
TemporalDataPoint< Data, Arity >::back ()
-> std::common_reference_t< std::reference_wrapper< Data>> {
    try {
        return this->m_data_ref.back ();
    } catch (std::out_of_range & e) {
        std::cerr << "TemporalDataPoint::back() out_of_range exception: " << e.what () << std::endl;
        std::exit (EXIT_FAILURE);

    } catch (std::runtime_error & e) {
        std::cerr << "TemporalDataPoint::back() runtime_error exception: " << e.what () << std::endl;
        std::exit (EXIT_FAILURE);

    } catch (std::exception & e) {
        std::cerr << "TemporalDataPoint::back() exception: " << e.what () << std::endl;
        std::exit (EXIT_FAILURE);

    } catch (...) {
        std::cerr << "TemporalDataPoint::back() unknown exception" << std::endl;
        std::exit (EXIT_FAILURE);
    }
}


template < typename Data, std::size_t Arity >
NOD constexpr
std::common_reference_t< std::reference_wrapper< const Data>>
TemporalDataPoint< Data, Arity >::back ()
const {
    try {
        return this->m_data_ref.back ();
    } catch (std::out_of_range & e) {
        std::cerr << "TemporalDataPoint::back() out_of_range exception: " << e.what () << std::endl;
        std::exit (EXIT_FAILURE);

    } catch (std::runtime_error & e) {
        std::cerr << "TemporalDataPoint::back() runtime_error exception: " << e.what () << std::endl;
        std::exit (EXIT_FAILURE);

    } catch (std::exception & e) {
        std::cerr << "TemporalDataPoint::back() exception: " << e.what () << std::endl;
        std::exit (EXIT_FAILURE);

    } catch (...) {
        std::cerr << "TemporalDataPoint::back() unknown exception" << std::endl;
        std::exit (EXIT_FAILURE);
    }

}


template < typename Data, std::size_t Arity >
NOD constexpr auto
TemporalDataPoint< Data, Arity >::data () noexcept -> std::add_pointer_t< std::reference_wrapper< Data>> {
    return this->m_data_ref.data ();
}

template < typename Data, std::size_t Arity >
NOD constexpr auto
TemporalDataPoint< Data, Arity >::data () const noexcept -> std::add_pointer_t< std::reference_wrapper< Data>> {
    return this->m_data_ref.data ();
}


template < typename Data, std::size_t Arity >
NRS constexpr auto
TemporalDataPoint< Data, Arity >::fill (const data_t & value) -> void {
    std::fill (std::execution::par_unseq, this->m_data_ref.begin (), this->m_data_ref.end (), value);
}



