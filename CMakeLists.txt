CMAKE_MINIMUM_REQUIRED(VERSION 3.24)
PROJECT(temporal_series_cpp23)

SET(CMAKE_CXX_STANDARD 23)


INCLUDE_DIRECTORIES("/opt/homebrew/include/boost/")
INCLUDE_DIRECTORIES("/opt/homebrew/include/boost/graph/")


# We need Boost C++
FIND_PACKAGE(Boost 1.80.0 REQUIRED COMPONENTS system filesystem graph)

# Install Boost
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})


LINK_DIRECTORIES("/opt/homebrew/lib/")



ADD_EXECUTABLE(temporal_series_cpp23 main.cpp template/SameSizeVQ.tcc TemporalDataPoint.c++ TemporalDataPoint.tcc
        TemporalDataSequence.c++
        template/AdditionNoOverflowQ.tcc
        template/SameQ.tcc
        TemporalDataSequence.tcc defines.h++ SwappabletTypeQ.tcc SemiregularQ.tcc template/SameVQ.tcc template/AddableQ.tcc NetGraph.tcc template/WillOverflow.inl template/WillOverflow.ii template/WillOverflow.tcc template/AdditionWillOverflow.c++ template/AdditionWillOverflow.h++ template/DefaultConstructibleQ.tcc template/CopyConstructibleQ.tcc template/MoveConstructibleQ.tcc template/CopyAssignableQ.tcc template/MoveAssignableQ.tcc template/DestructibleQ.tcc template/EqualityComparableQ.tcc template/RingBuffer/RingBuffer.tcc template/LRUCache/LruCache.tcc src/uint64_digits.c++ src/uint64_digits.h++)
