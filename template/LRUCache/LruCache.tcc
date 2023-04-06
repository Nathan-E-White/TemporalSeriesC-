#ifndef LRU_CACHE_TCC
#define LRU_CACHE_TCC

#include <cstdint>
#include <array>
#include <bitset>
#include <variant>
#include <mutex>
#include <vector>
#include <optional>

#include "../../defines.h++"

/* Implement a LRU cache for the data. */
template < std::size_t NCache, typename IndexType >
class LRUCache {

    /* An internal set of codes for the cache. */
    enum class CacheCode {
        /* The cache is empty. */
          Empty
        , /* The cache is full. */
          Full
        , /* The cache is partially full. */
          Partial
        , /* The cache is invalid. */
          Invalid
        , /* General success. */
          Success
        , /* General failure. */
          Failure
        , /* The cache is not yet initialized. */
          Uninitialized
        , /* Eviction was successful. */
          EvictionSuccess
        , /* Eviction was unsuccessful. */
          EvictionFailure
        , EvictionFailure_Empty
        , EvictionFailure_ElementNotFound
        , EvictionFailure_InvalidIndex
        , EvictionFailure_InvalidCacheCode
        , EvictionFailure_InvalidCacheSize
        , EvictionFailure_InvalidCacheIndex
        , EvictionFailure_InvalidCacheElement
        , /* Insertion was successful. */
          InsertionSuccess
        , /* Insertion was unsuccessful. */
          InsertionFailure
        , InsertionFailure_Full
        , InsertionFailure_InvalidCacheCode
        , InsertionFailure_InvalidCacheSize
        , InsertionFailure_InvalidCacheIndex
        , InsertionFailure_InvalidTargetElement
        , InsertionFailure_InvalidTargetIndex
        , InsertionFailure_InvalidSourceIndex
        , InsertionFailure_InvalidSourceElement
        , /* Lookup was successful. */
          LookupSuccess
        , /* Lookup was unsuccessful. */
          LookupFailure
        , LookupFailure_Empty
        , LookupFailure_ElementNotFound
        , LookupFailure_InvalidCacheCode
        , LookupFailure_InvalidCacheSize
        , LookupFailure_InvalidCacheIndex
        , LookupFailure_InvalidTargetElement
        , LookupFailure_InvalidTargetIndex
        , LookupFailure_InvalidSourceIndex
        , LookupFailure_InvalidSourceElement
        , /* Update was successful. */
          UpdateSuccess
        , /* Update was unsuccessful. */
          UpdateFailure
        , UpdateFailure_Empty
        , UpdateFailure_ElementNotFound
        , UpdateFailure_InvalidCacheCode
        , UpdateFailure_InvalidCacheSize
        , UpdateFailure_InvalidCacheIndex
        , UpdateFailure_InvalidTargetElement
        , UpdateFailure_InvalidTargetIndex
        , UpdateFailure_InvalidSourceIndex
        , UpdateFailure_InvalidSourceElement
        , /* General error. */
        Error
        , /* General warning. */
        Warning
        , /* Bad Trouble */
        BadTrouble
    };

    /* Store the type of the data. */
    using DataType = std::variant<
            std::monostate,
            std::int8_t,
            std::int16_t,
            std::int32_t,
            std::int64_t,
            std::uint8_t,
            std::uint16_t,
            std::uint32_t,
            std::uint64_t,
            float,
            double
    >;

    /* Occupancy of the cache. */
    /* This is a bitset of size NCache. */
    /* A bit is set if the corresponding element is occupied. */
    /* If the bit is not set, the corresponding element is empty. */
    std::bitset< NCache > occupancy = {0};

    /* The cache is a vector of pairs of indices and values. */
    std::vector< std::pair< IndexType, DataType > > cache;

    /* The cache size is the maximum number of elements in the cache. */
    static const
    constinit
    std::size_t cacheSize = NCache;

    /* The cache data is stored in an array of pairs of indices and values. */
    std::array< std::pair< IndexType, DataType >, cacheSize > cacheData;

    /* We keep a hit counter for each element in the cache. */
    std::array< std::size_t, cacheSize > cacheHits;

    /* A vector of operation codes */
    /* Can we make this threadsafe with a mutex? */
    std::mutex               opcode_mutex;
    std::vector< CacheCode > history_codes;


public:


private:

    /* Get the index of the least recently used element in the cache. */
    /* This is the element with the lowest hit count. */
    /* If there is a tie, the element with the lowest index is returned. */
    /* If the cache is empty, the return value is undefined. */
    [[nodiscard]]
    std::optional< std::size_t > getLRUIndex () const noexcept {

        /* The index of the least recently used element. */
        std::size_t lruIndex = 0;

        /* The hit count of the least recently used element. */
        std::size_t lruHitCount = 0;

        /* The index of the current element. */
        std::size_t currentIndex = 0;

        /* The hit count of the current element. */
        std::size_t currentHitCount = 0;

        /* The number of elements in the cache. */
        std::size_t numElements = 0;

        /* The number of elements in the cache. */
        numElements = cache.size ();

        /* If the cache is empty, return an empty optional. */
        if (numElements == 0) {
            return std::nullopt;
        }

        /* If the cache is not empty, get the hit count of the first element. */
        lruHitCount = cacheHits[0];

        /* Iterate over the elements in the cache. */
        for (
                currentIndex = 1; currentIndex < numElements; currentIndex++
                ) {

            /* Get the hit count of the current element. */
            currentHitCount = cacheHits[currentIndex];

            /* If the current element has a lower hit count, */
            /* update the LRU index and hit count. */
            if (currentHitCount < lruHitCount) {
                lruIndex    = currentIndex;
                lruHitCount = currentHitCount;
            }

        }

        /* Return the index of the least recently used element. */
        return lruIndex;

    };


};

#endif
