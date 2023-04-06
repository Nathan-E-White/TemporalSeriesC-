#ifndef RING_BUFFER_TCC
#define RING_BUFFER_TCC


#include <cstdint>
#include <concepts>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <utility>
#include <array>
#include <iterator>


template <
        std::size_t RingSize,
        class DataCategory,
        typename size_type = std::size_t,
        typename difference_type = std::ptrdiff_t,
        typename reference = DataCategory &,
        typename const_reference = const DataCategory &,
        typename pointer = DataCategory *,
        typename const_pointer = const DataCategory *,
        typename iter = typename std::array< DataCategory, RingSize >::iterator,
        typename const_iter = typename std::array< DataCategory, RingSize >::const_iterator,
        typename reverse_iter = typename std::array< DataCategory, RingSize >::reverse_iterator,
        typename const_reverse_iter = typename std::array< DataCategory, RingSize >::const_reverse_iterator,
        typename span_iter = typename std::array< DataCategory, RingSize >::span::iterator,
        typename const_span_iter = typename std::array< DataCategory, RingSize >::span::const_iterator,
        typename reverse_span_iter = typename std::array< DataCategory, RingSize >::span::reverse_iterator,
        typename const_reverse_span_iter = typename std::array< DataCategory, RingSize >::span::const_reverse_iterator,
        typename sentinel = typename std::array< DataCategory, RingSize >::sentinel,
        typename const_sentinel = typename std::array< DataCategory, RingSize >::const_sentinel,
        typename reverse_sentinel = typename std::array< DataCategory, RingSize >::reverse_sentinel,
        typename const_reverse_sentinel = typename std::array< DataCategory, RingSize >::const_reverse_sentinel
>
class RingBuffer {

private: /* Types */


private: /* Data */

    std::array< DataCategory, RingSize > _data;
    std::size_t                          _head;
    std::size_t                          _tail;
    std::size_t                          _size;


public: /* Constructors */

    constexpr RingBuffer () noexcept;

    constexpr RingBuffer (const RingBuffer & other) noexcept;

    constexpr RingBuffer (RingBuffer && other) noexcept;

    constexpr RingBuffer & operator = (const RingBuffer & other) noexcept;

    constexpr RingBuffer & operator = (RingBuffer && other) noexcept;


public: /* Destructor */

public: /* Element Access (EA) */

    // -- at: constexpr reference at (size_type pos); // (1)
    // -- at: constexpr const_reference at (size_type pos) const; // (2)
    // -- operator[]: constexpr reference operator[] (size_type pos); // (3)
    // -- operator[]: constexpr const_reference operator[] (size_type pos) const; // (4)
    // -- front: constexpr reference front (); // (5)
    // -- front: constexpr const_reference front () const; // (6)
    // -- back: constexpr reference back (); // (7)
    // -- back: constexpr const_reference back () const; // (8)
    // -- data: constexpr pointer data () noexcept; // (9)
    // -- data: constexpr const_pointer data () const noexcept; // (10)

    /* (EA1) */
    constexpr reference at (size_type pos);

    /* (EA2) */
    constexpr const_reference at (size_type pos) const;

    /* (EA3) */
    constexpr reference operator[] (size_type pos);

    /* (EA4) */
    constexpr const_reference operator[] (size_type pos) const;

    /* (EA5) */
    constexpr reference front ();

    /* (EA6) */
    constexpr const_reference front () const;

    /* (EA7) */
    constexpr reference back ();

    /* (EA8) */
    constexpr const_reference back () const;

    /* (EA9) */
    constexpr pointer data () noexcept;

    /* (EA10) */
    constexpr const_pointer data () const noexcept;


public: /* Iterator Operations */

    /* Advance */

    /* Distance */

    /* Next */

    /* ranges::advance */
    /* ranges::distance */
    /* ranges::next */
    /* ranges::prev */


public: /* Range Access */

    /* ranges::begin */
    /* ranges::cbegin */
    /* ranges::cend */
    /* ranges::crbegin */
    /* ranges::crend */
    /* ranges::end */
    /* ranges::rbegin */
    /* ranges::rend */
    /* ranges::size */
    /* ranges::ssize */
    /* ranges::empty */
    /* ranges::data */

    /* Stream Iterators */
    /* istream_iterator */
    /* istreambuf_iterator */
    /* ostream_iterator */
    /* ostreambuf_iterator */

    /* Iterator Adaptors */
    /* Reverse Iterator */
    /* Move Iterator */
    /* Counted Iterator */
    /* Indirect Iterator */
    /* Transform Iterator */
    /* Filter Iterator */
    /* Join Iterator */
    /* Split Iterator */
    /* Take Iterator */
    /* Drop Iterator */
    /* Take While Iterator */
    /* Drop While Iterator */
    /* Sample Iterator */
    /* Stride Iterator */
    /* Cycle Iterator */
    /* Zip Iterator */
    /* Enumerate Iterator */
    /* Reverse View */
    /* Move View */
    /* Counted View */





};


#endif
