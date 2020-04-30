cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

project(ZigZagCore VERSION 0.1.0)


add_library(ZigZagCore STATIC
    ZigZag/BaseDataInput.cpp
    ZigZag/BaseDataSource.cpp
    ZigZag/BaseOperator.cpp
    ZigZag/BaseParameter.cpp
    ZigZag/Object.cpp
)

add_subdirectory(external/Variant)

target_link_libraries(ZigZagCore ZigZagVariant)

target_include_directories(ZigZagCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
