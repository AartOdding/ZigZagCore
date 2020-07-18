cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

project(ZigZagCore VERSION 0.1.0)

SET(SOURCES
    ZigZag/BaseDataInput.cpp
    ZigZag/BaseDataSource.cpp
    ZigZag/BaseOperator.cpp
    ZigZag/BaseParameter.cpp
    ZigZag/Object.cpp
    ZigZag/ObjectFactory.cpp
    ZigZag/ObjectSelection.cpp
    ZigZag/RenderOrder.cpp
)

SET(HEADERS
    ZigZag/BaseDataInput.hpp
    ZigZag/BaseDataSource.hpp
    ZigZag/BaseOperator.hpp
    ZigZag/BaseParameter.hpp
    ZigZag/InputOutputRelationship.hpp
    ZigZag/Object.hpp
    ZigZag/ObjectFactory.hpp
    ZigZag/ObjectSelection.hpp
    ZigZag/ParentChildRelationship.hpp
    ZigZag/RenderOrder.hpp
    ZigZag/TParameter.hpp
)

add_library(ZigZagCore STATIC ${SOURCES} ${HEADERS})

target_include_directories(ZigZagCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
