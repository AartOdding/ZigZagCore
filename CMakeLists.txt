cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

project(ZigZagCore VERSION 0.1.0)


add_library(ZigZagCore
    ZigZag/BaseDataInput.cpp
    ZigZag/BaseDataSource.cpp
    ZigZag/BaseOperator.cpp
    ZigZag/BaseParameter.cpp
    ZigZag/Object.cpp
    ZigZag/Variant.cpp
)


add_subdirectory(external/glm)

target_include_directories(ZigZagCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/glm)

target_include_directories(ZigZagCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
