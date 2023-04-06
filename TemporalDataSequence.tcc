#ifndef TEMPORAL_DATA_SEQUENCE_TCC
#define TEMPORAL_DATA_SEQUENCE_TCC

#include <cstdint>
#include <vector>
#include <concepts>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <variant>
#include <optional>
#include <array>
#include <bitset>
#include <mutex>
#include <algorithm>
#include <functional>

#include "TemporalDataPoint.tcc"
#include "defines.h++"


enum class TemporalDataSequenceCodes {
    OK, FAILURE
};



/* This is a class for a single path in a temporal data sequence. */
/* Multiple paths will be stored in another class. */
template <
        typename DataType,
        std::size_t DataArity,
        typename IndexType
> requires std::is_integral_v< IndexType >
class TemporalDataSequence {

public:
    using TDP =
            TemporalDataPoint<
                    DataType,
                    DataArity
            >;

private:
    //std::optional< SequenceCache< IndexType, IndexContainerType > > cache;

    using IndexedDataPoint = std::pair<
            std::reference_wrapper< const IndexType >,
            const TDP
    >;

    using IndexedSlider = std::pair<
            const IndexType,
            const std::reference_wrapper< const IndexedDataPoint >
    >;

private:

    std::vector< IndexedDataPoint > data;
    std::vector< IndexedSlider >    _indices;


    NOD
    TemporalDataSequenceCodes
    insert_data (TemporalDataPoint< DataType, DataArity > data_point);

public:
    constexpr TemporalDataSequence () noexcept = default;

    constexpr TemporalDataSequence (const TemporalDataSequence & other) noexcept = default;

    constexpr TemporalDataSequence (TemporalDataSequence && other) noexcept = default;

    constexpr TemporalDataSequence & operator = (const TemporalDataSequence & other) noexcept = default;

    constexpr TemporalDataSequence & operator = (TemporalDataSequence && other) noexcept = default;

    constexpr virtual ~TemporalDataSequence () noexcept = default;


};


template < typename DataType, std::size_t DataArity, typename IndexType > requires std::is_integral_v< IndexType >
NOD TemporalDataSequenceCodes
TemporalDataSequence< DataType, DataArity, IndexType >::insert_data (TDP data_point) {

    using TDSC = TemporalDataSequenceCodes;
    auto rtc_code = TDSC::OK;

    template < typename A, typename B, typename C, typename D, typename E >
    using Buildup = std::tuple< A, B, C, D, E >;

    std::function<
            TDSC (
                    const TDP &,
                    std::vector< IndexedDataPoint > & dat_vec,
                    std::vector< IndexedSlider > & ind_vec
            )
    > step1;

    /* 1a. Get the current number of data points, and index points in separate variables. */
    auto get_data_size = [] (const std::vector< IndexedDataPoint > & dat_vec) -> std::pair< std::size_t, TDSC > {
        return std::make_pair (dat_vec.size (), TDSC::OK);
    };

    auto get_index_size = [] (const std::vector< IndexedSlider > & ind_vec) -> std::pair< std::size_t, TDSC > {
        return std::make_pair (ind_vec.size (), TDSC::OK);
    };


    /* 1b. Get the next index number; get the max value in the container and add one to it */
    /*     Note the _indices are actually a pair of the index and a reference to the data point. */
    /*     For this step we only need the index. */
    auto find_next_index = [] (const auto & container) {

        if (container.empty ()) {
            return IndexType {0};
        }

        return std::max_element (
                container.begin (),
                container.end (),
                [] (const auto & lhs, const auto & rhs) {
                    return lhs.first < rhs.first;
                }
        )->first + 1;
    };

    /* 2a. Form the slider point */
    auto form_slider_point = [&] (const auto & index, const auto & data_point) {
        return std::pair {
                index,
                std::cref (data_point)
        };
    };

    /* 2b. Add the slider point to the container */
    auto add_slider_point = [] (const auto & slider_point, auto & container) {
        container.push_back (slider_point);
    };

    /* 2c. Verify that the index container has one more element than before */
    /*     Throw a runtime error if it does not. */
    auto verify_index_container_size = [] (const auto & container, const auto & num_index_points) {
        if (container.size () != num_index_points + 1) {
            throw std::runtime_error ("Index container size is not one more than before.");
        }
    };

    /* 3a. Form the data point */
    auto form_data_point_pair = [] (const auto & index, const auto & data_point) {
        return std::pair {
                std::cref (index),
                data_point
        };
    };

    /* 4. Add the indexed data point to the data vector */
    auto add_data_point = [] (const auto & data_point_pair, auto & container) {
        container.push_back (data_point_pair);
    };

    /* 5. Verify that the data container has one more element than before */
    /*    Throw a runtime error if it does not. */
    auto verify_data_container_size = [] (const auto & container, const auto & num_elements) {
        if (container.size () != num_elements + 1) {
            throw std::runtime_error ("Data container did not grow by one element.");
        }
    };

    /* 6. Verify that the data container and the index container have the same number of elements */
    /*    Throw a runtime error if they do not. */
    auto verify_containers_same_size = [] (const auto & container1, const auto & container2) {
        if (container1.size () != container2.size ()) {
            throw std::runtime_error ("Data container and index container do not have the same number of elements.");
        }
    };

    /* 7. Check that the reference to the data point in the index container is the same as the data point in the data container */
    /*    Throw a runtime error if they are not. */
    auto check_index_reference = [] (const auto & index_container, const auto & data_container) {
        if (index_container.back ().second.get ().second != data_container.back ().second) {
            throw std::runtime_error (
                    "Index container reference to data point is not the same as the data point in the data container."
            );
        }
    };

    /* 8. Check that the index in the index container is the same as the index in the data container */
    /*    Throw a runtime error if they are not. */
    auto check_index_value = [] (const auto & index_container, const auto & data_container) {
        if (index_container.back ().first != data_container.back ().first) {
            throw std::runtime_error ("Index container index is not the same as the index in the data container.");
        }
    };

    /* 9. Sort the index container by index if adding the data point did not cause the index container to be sorted */
    /*    Note: if we are doing this on every insert, then we only need to check the last 2 elements. */
    /*    Throw a runtime error if the index container is not sorted. */
    // Get the last two elements in the index container
    auto check_and_sort_containers = [] (const auto & index_container) {
        if (index_container.size () > 1) {
            if (index_container.back ().first < index_container[index_container.size () - 2].first) {
                std::sort (
                        index_container.begin (),
                        index_container.end (),
                        [] (const auto & lhs, const auto & rhs) {
                            return lhs.first < rhs.first;
                        }
                );
            }
        }
    };

    // Call the lambdas
    auto [num_data_points, rtc_1]  = get_data_size (data);
    auto [num_index_points, rtc_2] = get_index_size (_indices);
    auto [next_index, rtc_3]       = find_next_index (_indices);
    auto [slider_point, rtc_4]     = form_slider_point (next_index, data_point);
    auto rtc_5                     = add_slider_point (slider_point, _indices);
    auto rtc_6                     = verify_index_container_size (_indices, num_index_points);
    auto [data_point_pair, rtc_7] = form_data_point_pair (next_index, data_point);
    auto rtc_8                    = add_data_point (data_point_pair, data);
    auto rtc_9                    = verify_data_container_size (data, num_data_points);
    auto rtc_10                   = verify_containers_same_size (data, _indices);
    auto rtc_11                   = check_index_reference (_indices, data);
    auto rtc_12                   = check_index_value (_indices, data);
    auto rtc_13                   = check_and_sort_containers (_indices);

    return rtc_code;
}


#endif