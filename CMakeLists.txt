cmake_minimum_required(VERSION 2.8)

set( CMAKE_CXX_STANDARD 17 )

project(ZigZagMin)


add_executable(ZigZag
    main.cpp
    ZigZag/Object.cpp
    ZigZag/BaseOperator.cpp
    ZigZag/BaseDataSource.cpp
    ZigZag/BaseDataInput.cpp
)

#${CMAKE_CURRENT_SOURCE_DIR}
target_include_directories(ZigZag PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
