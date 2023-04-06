#ifndef NET_GRAPH_TCC
#define NET_GRAPH_TCC

#include <iostream>
#include <utility>
#include <algorithm>
#include <concepts>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <execution>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <iterator>
#include <memory>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <bitset>

#include "defines.h++"

// TODO(Nate) Move this to a separate file
template < typename T >
class SemigroupCategory {

private:

protected:
    SemigroupCategory () = default;

protected:
    SemigroupCategory (const SemigroupCategory &) = default;

protected:
    SemigroupCategory (SemigroupCategory &&) noexcept = default;

protected:
    SemigroupCategory & operator = (const SemigroupCategory &) = default;

protected:
    SemigroupCategory & operator = (SemigroupCategory &&) noexcept = default;

public:
    virtual ~SemigroupCategory () = default;

public:
    virtual T & operator *= (const T &) = 0;

public:
    friend T operator * (const T & lhs, const T & rhs) {
        T temp (lhs);
        return temp *= rhs;
    }

    friend T pow (const T & x, int n) {
        T temp {x};
        return temp.pow (n);
    }

    inline T & pow (int n);//;requires (n>0) {
    // ;;   return pow (n-1) *= *this;
    //;;}

    static void compositionLaw (T & lhs, const T & rhs) {
        lhs *= rhs;
    }
};

// TODO(Nate) Move this to a separate file
template < typename T >
class MonoidCategory : protected virtual SemigroupCategory< T > {
private:


protected:
    MonoidCategory () = default;

protected:
    MonoidCategory (const MonoidCategory &) = default;

protected:
    MonoidCategory (MonoidCategory &&) noexcept = default;

protected:
    MonoidCategory & operator = (const MonoidCategory &) = default;

protected:
    MonoidCategory & operator = (MonoidCategory &&) noexcept = default;

public:
    virtual ~MonoidCategory () = default;

public:
    virtual T & setToOne () = 0;
};

// TODO(Nate) Move this to a separate file
template < typename T >
class GroupCategory : MonoidCategory< T > {

protected:
    GroupCategory () = default;

protected:
    GroupCategory (const GroupCategory &) = default;

protected:
    GroupCategory (GroupCategory &&) noexcept = default;

protected:
    GroupCategory & operator = (const GroupCategory &) = default;

protected:
    GroupCategory & operator = (GroupCategory &&) noexcept = default;

public:
    virtual ~GroupCategory () = default;

public:
    virtual T & operator /= (const T &) = 0;
};


// TODO(Nate) Move this to a separate file
template < typename T >
class AbelianSemiGroupCategory : SemigroupCategory< T > {

protected:
    AbelianSemiGroupCategory () = default;

protected:
    AbelianSemiGroupCategory (const AbelianSemiGroupCategory &) = default;

protected:
    AbelianSemiGroupCategory (AbelianSemiGroupCategory &&) noexcept = default;

protected:
    AbelianSemiGroupCategory & operator = (const AbelianSemiGroupCategory &) = default;

protected:
    AbelianSemiGroupCategory & operator = (AbelianSemiGroupCategory &&) noexcept = default;

public:
    virtual ~AbelianSemiGroupCategory () = default;

public:
    virtual T & operator += (const T &) = 0;

};

// TODO(Nate) Move this to a separate file
template < typename T >
class AbelianMonoidCategory : public AbelianSemiGroupCategory< T >, public MonoidCategory< T > {

protected:
    AbelianMonoidCategory () = default;

protected:
    AbelianMonoidCategory (const AbelianMonoidCategory &) = default;

protected:
    AbelianMonoidCategory (AbelianMonoidCategory &&) noexcept = default;

protected:
    AbelianMonoidCategory & operator = (const AbelianMonoidCategory &) = default;

protected:
    AbelianMonoidCategory & operator = (AbelianMonoidCategory &&) noexcept = default;

public:
    ~AbelianMonoidCategory () override = default;

public:
    virtual T & setToZero () = 0;

};

// TODO(Nate) Move this to a separate file
template < typename T >
class AbelianGroupCategory : public AbelianMonoidCategory< T > {

public:
    ~AbelianGroupCategory () override = default;

public:
    virtual T & operator -= (const T &) = 0;
};


// TODO(Nate) Move this to a separate file
template < typename T >
class RingCategory : public SemigroupCategory< T >, public AbelianGroupCategory< T > {

protected:
    RingCategory () = default;

protected:
    RingCategory (const RingCategory &) = default;

protected:
    RingCategory (RingCategory &&) noexcept = default;

protected:
    RingCategory & operator = (const RingCategory &) = default;

protected:
    RingCategory & operator = (RingCategory &&) noexcept = default;

public:
    ~RingCategory () override = default;
};

// TODO(Nate) Move this to a separate file
template < typename T >
class RingWithUnitCategory :
        public MonoidCategory< T >,
        public AbelianGroupCategory< T >,
        public RingCategory< T > {

public:
    T & operator ++ () {
        T one (( T & ) * this);
        one.setToOne ();
        return ( T & ) * this += one;
    }
    T operator ++ (int) {
        T orig (( T & ) * this);
        ++* this;
        return orig;
    }
    T & operator -- () {
        T one (( T & ) * this);
        one.setToOne ();
        return ( T & ) * this -= one;
    }
    T operator -- (int) {
        T orig (( T & ) * this);
        --* this;
        return orig;
    }
};

// TODO(Nate) Move this to a separate file
template < typename T >
class FieldCategory : GroupCategory< T >, AbelianGroupCategory< T > {

protected:
    FieldCategory () = default;

protected:
    FieldCategory (const FieldCategory &) = default;

protected:
    FieldCategory (FieldCategory &&) noexcept = default;

protected:
    FieldCategory & operator = (const FieldCategory &) = default;

protected:
    FieldCategory & operator = (FieldCategory &&) noexcept = default;

public:
    ~FieldCategory () override = default;

public:

    T & operator ++ () {
        T one (( T & ) * this);
        one.setToOne ();
        return ( T & ) * this += one;
    }

    T operator ++ (int) {
        T orig (( T & ) * this);
        ++* this;
        return orig;
    }

    T & operator -- () {
        T one (( T & ) * this);
        one.setToOne ();
        return ( T & ) * this -= one;
    }

    T operator -- (int) {
        T orig (( T & ) * this);
        --* this;
        return orig;
    }
};


// TODO(Nate) Move this to a separate file
template < typename V, typename S >
class ExternalScalarsCategory {

public:
    ExternalScalarsCategory () = default;

    ExternalScalarsCategory (const ExternalScalarsCategory &) = default;

    ExternalScalarsCategory (ExternalScalarsCategory &&) noexcept = default;

    ExternalScalarsCategory & operator = (const ExternalScalarsCategory &) = default;

    ExternalScalarsCategory & operator = (ExternalScalarsCategory &&) noexcept = default;

    virtual ~ExternalScalarsCategory () = default;


public:
    virtual V & operator *= (const S &) = 0;

    friend V operator * (const S & s, const V & v) {
        V temp (v);
        return temp *= s;
    }
    friend V operator * (const V & v, const S & s) {
        V temp (v);
        return temp *= s;
    }
};

// TODO(Nate) Move this to a separate file
template < typename V, typename S >
class FieldScalarsCategory : public ExternalScalarsCategory< V, S > {

protected:
    FieldScalarsCategory () = default;

    FieldScalarsCategory (const FieldScalarsCategory &) = default;

    FieldScalarsCategory (FieldScalarsCategory &&) noexcept = default;

    FieldScalarsCategory & operator = (const FieldScalarsCategory &) = default;

    FieldScalarsCategory & operator = (FieldScalarsCategory &&) noexcept = default;

    ~FieldScalarsCategory () override = default;

public:
    virtual V & operator /= (const S &) = 0;

    friend V operator / (const V & v, const S & s) {
        V temp (v);
        return temp /= s;
    }
};

// TODO(Nate) Move this to a separate file
template < typename V, typename S >
class LeftScalarsCategory : public FieldScalarsCategory< V, S > {

protected:
    LeftScalarsCategory () = default;

    LeftScalarsCategory (const LeftScalarsCategory &) = default;

    LeftScalarsCategory (LeftScalarsCategory &&) noexcept = default;

    LeftScalarsCategory & operator = (const LeftScalarsCategory &) = default;

    LeftScalarsCategory & operator = (LeftScalarsCategory &&) noexcept = default;

    ~LeftScalarsCategory () override = default;

public:
    friend V operator / (const S & s, const V & v) {
        V temp (inverse (v));
        temp.setToOne ();
        return temp *= s;
    }
};

// TODO(Nate) Move this to a separate file
template < typename V, typename S >
class LinearSpaceCategory : public FieldScalarsCategory< V, S >, public AbelianGroupCategory< V > {

protected:
    LinearSpaceCategory () = default;

    LinearSpaceCategory (const LinearSpaceCategory &) = default;

    LinearSpaceCategory (LinearSpaceCategory &&) noexcept = default;

    LinearSpaceCategory & operator = (const LinearSpaceCategory &) = default;

    LinearSpaceCategory & operator = (LinearSpaceCategory &&) noexcept = default;

    ~LinearSpaceCategory () override = default;
};

// TODO(Nate) Move this to a separate file
template < typename V, typename S >
class LinearAlgebraCategory : public FieldScalarsCategory< V, S >, public RingCategory< V > {
protected:
    LinearAlgebraCategory () = default;

    LinearAlgebraCategory (const LinearAlgebraCategory &) = default;

    LinearAlgebraCategory (LinearAlgebraCategory &&) noexcept = default;

    LinearAlgebraCategory & operator = (const LinearAlgebraCategory &) = default;

    LinearAlgebraCategory & operator = (LinearAlgebraCategory &&) noexcept = default;

    ~LinearAlgebraCategory () override = default;
};

// TODO(Nate) Move this to a separate file
template < typename V, typename S >
class AlgebraWithUnitCategory : public RingWithUnitCategory< V >, public FieldScalarsCategory< V, S > {

protected:
    AlgebraWithUnitCategory () = default;

    AlgebraWithUnitCategory (const AlgebraWithUnitCategory &) = default;

    AlgebraWithUnitCategory (AlgebraWithUnitCategory &&) noexcept = default;

    AlgebraWithUnitCategory & operator = (const AlgebraWithUnitCategory &) = default;

    AlgebraWithUnitCategory & operator = (AlgebraWithUnitCategory &&) noexcept = default;

    ~AlgebraWithUnitCategory () override = default;
};


// TODO(Nate) Move this to a separate file
/**
 * @brief
 * @tparam V - Vector type
 * @tparam S - Scalar type
 */
template < typename V, typename S >
class DivisionAlgebraCategory : public FieldCategory< V >, public LeftScalarsCategory< V, S > {

protected:
    DivisionAlgebraCategory () = default;

    DivisionAlgebraCategory (const DivisionAlgebraCategory &) = default;

    DivisionAlgebraCategory (DivisionAlgebraCategory &&) noexcept = default;

    DivisionAlgebraCategory & operator = (const DivisionAlgebraCategory &) = default;

    DivisionAlgebraCategory & operator = (DivisionAlgebraCategory &&) noexcept = default;

    ~DivisionAlgebraCategory () override = default;
};


// TODO(Nate) Move this to a separate file
template < class T, int m, int l, int t, int q, int k, int i, int a >
class Physical : public LinearSpaceCategory< Physical< T, m, l, t, q, k, i, a >, T > {

private:
    T val;

public:

    constexpr Physical (const Physical &) = default;

    Physical (Physical &&) noexcept = default;

    Physical & operator = (const Physical &) = default;

    Physical & operator = (Physical &&) noexcept = default;

    ~Physical () override = default;

public:
    constexpr auto value () -> T & { return this->val; }
    constexpr auto value () const -> const T & { return this->val; }

private:
    typedef Physical< T, m, l, t, q, k, i, a > Phys;
    constexpr Physical () : val (1) {}

public:
    static Phys unit () { return Phys (); }

};

// TODO(Nate) Move this to a separate file
template < std::size_t N >
class AdditiveArray :
        public std::array< double, N >,
        public AbelianSemiGroupCategory< AdditiveArray< N>> {
public:
    AdditiveArray () : std::array< double, N > () {}

    AdditiveArray (const AdditiveArray< N > & other) : std::array< double, N > (other) {}

    AdditiveArray & operator += (const AdditiveArray< N > & other) {
        for (
                std::size_t i = 0; i < N; ++i
                ) {
            (* this)[i] += other[i];
        }
        return * this;
    }
};

/* See C++ science engineers, reference [96, Part IIA] */
/* Difficult to define useful exponentiation operator in C++, considering arity, associativity and precedence */
/* Definition of SemiGroupCategory<T>::operator*() follows [44, Section 12.1.1c] */

// TODO(Nate) Move this to a separate file
template < typename T, std::size_t N >
class SymmetricGroupCategory : public GroupCategory< T > {

};

// TODO(Nate) Move this to a separate file
template < typename T, std::size_t N >
class CyclicGroupCategory : public AbelianGroupCategory< T >, public SymmetricGroupCategory< T, N > {

};

// TODO(Nate) Move this to a separate file
template < typename T, std::size_t N >
class DihedralGroupCategory : public CyclicGroupCategory< T, 2 * N >, public SymmetricGroupCategory< T, N > {

};

// TODO(Nate) Move this to a separate file, finish it
template < typename T, std::size_t N >
class DicyclicGroupCategory : public DihedralGroupCategory< T, 2 * N >, public SymmetricGroupCategory< T, N > {

};


// TODO(Nate) Move this to a separate file, finish it
template < typename T, template < typename > class GL, template < typename > class GR >
class DirectProductCategory : public GroupCategory< T >, public GL< T >, public GR< T > {

private:
    std::unordered_map< GL< T >, GR< T>> map;
};


// TODO(Nate) Move this to a separate file, finish it
template < class Domain, class Range >
class Functional {
public:
    virtual Range operator () (const Domain & x) const = 0;

    virtual Functional< Domain, Range > * clone () const = 0;

    virtual ~Functional () = default;
};

// TODO(Nate) Move this to a separate file, finish it
template < class Domain >
class Isofunctional : public virtual Functional< Domain, Domain > {
public:
    virtual Isofunctional< Domain > * clone () const = 0;
};

// TODO(Nate) Move this to a separate file, finish it
template < class Domain, class Range >
class Function : public virtual Functional< Domain, Range > {
protected:
    Range (* pf) (Domain);

public:
    explicit Function (Range (* f) (Domain)) : pf (f) {}
    Function () : pf (nullptr) {}

public:
    Function< Domain, Range > & operator = (const Function< Domain, Range > & f) {
        this->pf = f.pf;
        return * this;
    }

public:
    Function< Domain, Range > & operator = (Range (* f) (Domain)) {
        this->pf = f;
        return * this;
    }

public:
    virtual Range operator () (const Domain & x) const {
        return this->pf (x);
    }

    virtual Function< Domain, Range > * clone () const {
        return new Function< Domain, Range > (* this);
    }

};

/* PAGE 517 */


// TODO(Nate) Move this to a separate file, finish it
template < typename Tp, template < typename... > class Con, typename ...Args >
concept IsContainer = requires (Con< Args... > c) {

    std::is_array_v< Con< Tp, Args...>> (c);


};

// TODO(Nate) Move this to a separate file, finish it
template < typename Tp, template < typename... > class Container, typename ...Args > requires IsContainer<
        Tp,
        Container,
        Args...
>
class FunctionApplication {
public:

    enum class FunctionApplicationCodes : std::uint8_t {
        OK, ERROR, UNDEFINED
    };
    using Code = FunctionApplicationCodes;

    struct ApplyOptions {
        std::bitset< 8 > flags;
    };

private:
    Code code = Code::UNDEFINED;

public:

    static std::pair< Code, Container< Tp, Args...>>
    apply (std::function< Tp (Args...) > f, Container< Tp, Args... > & c) {

        Container< Tp, Args... > results;

        std::transform (c.begin (), c.end (), results.begin (), [&f] (const Tp & arg) { return f (arg); });

        return std::make_pair< Code, Container< Tp, Args...>> (Code::OK, results);

    }

    auto operator () (std::function< Tp (Args...) > f, Container< Tp, Args... > & c) ->
    std::common_reference<
            std::pair<
                    Code,
                    Container< Tp, Args...>>
    > {
        return apply (f, c);
    }
};


/* Declare Classes Here */
template <
        template < class > class VertexAllocatorPolicy,
        template < class > class EdgeAllocatorPolicy,
        template < class > class MetadataAllocatorPolicy,
        template < class > class VertDescAllocatorPolicy,
        template < class > class EdgeDescAllocatorPolicy,
        template < class > class GraphEdgeIteratorAllocatorPolicy,
        template < class > class GraphVertexIteratorAllocatorPolicy
>
class NetGraph;

class NetGraphEdge;

class NetGraphVertex;

class NetGraphMetadata;

class VertexDescriptor;

class EdgeDescriptor;

class GraphEdgeIterator;

class GraphVertexIterator;


/* Implement Classes Here */

// TODO(Nate) Move this to a separate file, finish it
struct VectorInterface {

    template < typename Tp >
    constexpr auto begin () noexcept -> std::common_iterator<
            std::counted_iterator< typename std::vector< Tp >::iterator >,
            std::default_sentinel_t
    >;

    template < typename Tp >
    constexpr auto begin () const noexcept -> std::common_iterator<
            std::counted_iterator< typename std::vector< Tp >::iterator >,
            std::default_sentinel_t
    >;


    template < typename Tp >
    constexpr auto end () noexcept -> std::common_iterator<
            std::counted_iterator< typename std::vector< Tp >::iterator >,
            std::default_sentinel_t
    >;


    template < typename Tp >
    constexpr auto end () const noexcept -> std::common_iterator<
            std::counted_iterator< typename std::vector< Tp >::iterator >,
            std::default_sentinel_t
    >;

/* cbegin() and cend() -- given for each vector */
    template < typename Tp >
    constexpr auto cbegin () const noexcept -> std::common_iterator<
            std::counted_iterator< typename std::vector< Tp >::iterator >,
            std::default_sentinel_t
    >;


    template < typename Tp >
    constexpr auto cend () const noexcept -> std::common_iterator<
            std::counted_iterator< typename std::vector< Tp >::iterator >,
            std::default_sentinel_t
    >;

/* rbegin() and rend() -- given for each vector */
    template < typename Tp >
    constexpr auto rbegin () noexcept -> std::reverse_iterator<
            std::common_iterator<
                    std::counted_iterator< typename std::vector< Tp >::iterator >,
                    std::default_sentinel_t>>;

    template < typename Tp >
    constexpr auto
    rbegin () const noexcept -> std::reverse_iterator<
            std::common_iterator<
                    std::counted_iterator< typename std::vector< Tp >::iterator >,
                    std::default_sentinel_t>>;

    template < typename Tp >
    constexpr auto
    rend () noexcept -> std::reverse_iterator<
            std::common_iterator<
                    std::counted_iterator< typename std::vector< Tp >::iterator >,
                    std::default_sentinel_t>>;

    template < typename Tp >
    constexpr auto
    rend () const noexcept -> std::reverse_iterator<
            std::common_iterator<
                    std::counted_iterator< typename std::vector< Tp >::iterator >,
                    std::default_sentinel_t>>;


/* crbegin() and crend() -- given for each vector */
    template < typename Tp >
    constexpr auto
    crbegin () const noexcept -> std::reverse_iterator<
            std::common_iterator<
                    std::counted_iterator< typename std::vector< Tp >::iterator >,
                    std::default_sentinel_t>>;


    template < typename Tp >
    constexpr auto crend () const noexcept ->
    std::reverse_iterator<
            std::common_iterator<
                    std::counted_iterator< typename std::vector< Tp >::iterator >,
                    std::default_sentinel_t>>;

};

// TODO(Nate) Move this to a separate file, finish it
template < typename ...Tp >
using reference = std::common_reference_t< Tp... >;

// TODO(Nate) Move this to a separate file, finish it
enum class VertexOptionsList : uint8_t {
    DefaultAllOptions = 0, ThrowOnDuplicate = 1, NoThrowOnDuplicate = 2, ThrowOnNotFound = 3, NoThrowOnNotFound = 4,
    ThrowOnInvalid    = 5, NoThrowOnInvalid = 6, };

// TODO(Nate) Move this to a separate file, finish it
template <
        template < class > class VertexAllocatorPolicy,
        template < class > class EdgeAllocatorPolicy,
        template < class > class MetadataAllocatorPolicy,
        template < class > class VertDescAllocatorPolicy,
        template < class > class EdgeDescAllocatorPolicy,
        template < class > class GraphEdgeIteratorAllocatorPolicy,
        template < class > class GraphVertexIteratorAllocatorPolicy
>
class NetGraph {

private:


    template < std::size_t N >
    struct VertexOptionsSpec {
        std::bitset< N > option_data;

    };

private:
    std::vector< NetGraphVertex, VertexAllocatorPolicy< NetGraphVertex >>       vertices;
    std::vector< NetGraphEdge, EdgeAllocatorPolicy< NetGraphEdge>>              edges;
    std::vector< NetGraphMetadata, MetadataAllocatorPolicy< NetGraphMetadata >> metadata;
    std::vector< VertexDescriptor, VertDescAllocatorPolicy< VertexDescriptor >> vert_desc;
    std::vector< EdgeDescriptor, EdgeDescAllocatorPolicy< EdgeDescriptor >>     edge_desc;

    std::vector< GraphEdgeIterator, GraphEdgeIteratorAllocatorPolicy< GraphEdgeIterator >>       edge_iterators;
    std::vector< GraphVertexIterator, GraphVertexIteratorAllocatorPolicy< GraphVertexIterator >> vert_iterators;

    std::atomic< std::size_t > num_vertices = std::atomic (0x0UL);
    std::atomic< std::size_t > num_edges    = std::atomic (0x0UL);

    std::atomic< std::size_t > num_vert_desc = std::atomic (0x0UL);
    std::atomic< std::size_t > num_edge_desc = std::atomic (0x0UL);

    std::atomic< std::size_t > num_edge_iterators = std::atomic (0x0UL);
    std::atomic< std::size_t > num_vert_iterators = std::atomic (0x0UL);
    std::atomic< std::size_t > num_metadata_props = std::atomic (0x0UL);

public:
    static constexpr auto
    add_vertex (reference< NetGraph > g, reference< NetGraphVertex > vertex) noexcept -> VertexDescriptor;

    static constexpr auto
    add_edge (reference< NetGraph > g,
              reference< NetGraphVertex >,
              reference< NetGraphVertex >
    ) noexcept -> EdgeDescriptor;

    static constexpr auto
    remove_vertex (reference< NetGraph > g, reference< VertexDescriptor >) noexcept -> VertexDescriptor;

    static constexpr auto
    remove_edge (reference< NetGraph > g, reference< EdgeDescriptor >) noexcept -> EdgeDescriptor;

    static constexpr auto
    get_vertex (reference< NetGraph > g, reference< VertexDescriptor >) noexcept -> NetGraphVertex;

    static constexpr auto
    get_edge (reference< NetGraph > g, reference< EdgeDescriptor >) noexcept -> NetGraphEdge;

    static constexpr auto
    get_vertex_descriptor (reference< NetGraph > g, reference< NetGraphVertex >) noexcept -> VertexDescriptor;

    static constexpr auto
    get_edge_descriptor (reference< NetGraph > g, reference< NetGraphEdge >) noexcept -> EdgeDescriptor;

public:

    constexpr NetGraph () = default;

    constexpr NetGraph (const NetGraph & other) = default;

    constexpr NetGraph (NetGraph && other) noexcept = default;

    constexpr NetGraph & operator = (const NetGraph & other) = default;

    constexpr reference< NetGraph > operator [] (std::add_cv< std::add_lvalue_reference_t< NetGraph>>
                                                 other
    );


    constexpr NetGraph & operator = (NetGraph && other) noexcept = default;

    virtual ~NetGraph () = default;


    std::common_reference_t< GraphEdgeIterator >
    add_edge (const GraphVertexIterator & source, const GraphVertexIterator & target);
};

// TODO(Nate) Move this to a separate file, finish it
class NetGraphVertex {


public: /* Default Constructor */
    NetGraphVertex () = default;

public: /* Copy Constructor */
    NetGraphVertex (const NetGraphVertex &) = default;

public: /* Move Constructor */
    NetGraphVertex (NetGraphVertex &&) noexcept = default;

public: /* Copy Assignment Operator */
    NetGraphVertex & operator = (const NetGraphVertex &) = default;

public: /* Move Assignment Operator */
    NetGraphVertex & operator = (NetGraphVertex &&) noexcept = default;

public: /* Destructor */
    virtual ~NetGraphVertex () = default;
};

// TODO(Nate) Move this to a separate file, finish it
class NetGraphEdge {

public: /* Default Constructor */
    NetGraphEdge () = default;

public: /* Copy Constructor */
    NetGraphEdge (const NetGraphEdge &) = default;

public: /* Move Constructor */
    NetGraphEdge (NetGraphEdge &&) noexcept = default;

public: /* Copy Assignment Operator */
    NetGraphEdge & operator = (const NetGraphEdge &) = default;

public: /* Move Assignment Operator */
    NetGraphEdge & operator = (NetGraphEdge &&) noexcept = default;

public: /* Destructor */
    virtual ~NetGraphEdge () = default;


};

// TODO(Nate) Move this to a separate file, finish it
class NetGraphMetadata {

public: /* Default Constructor */
    NetGraphMetadata () = default;

public: /* Copy Constructor */
    NetGraphMetadata (const NetGraphMetadata &) = default;

public: /* Move Constructor */
    NetGraphMetadata (NetGraphMetadata &&) noexcept = default;

public: /* Virtual Destructor */
    virtual ~NetGraphMetadata () = default;

public: /* Copy Operator */
    NetGraphMetadata & operator = (const NetGraphMetadata &) = default;

public: /* Move Operator */
    NetGraphMetadata & operator = (NetGraphMetadata &&) noexcept = default;


};

/* Implement Functions Here */




#endif