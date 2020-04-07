cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)

project(ZigZagCoreLib)


add_library(ZigZagCoreLib
    ZigZag/Object.cpp
    ZigZag/BaseOperator.cpp
    ZigZag/BaseDataSource.cpp
    ZigZag/BaseDataInput.cpp
    ZigZag/parameter/BaseParameter.cpp 
)


target_include_directories(ZigZagCoreLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
