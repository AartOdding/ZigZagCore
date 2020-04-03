cmake_minimum_required(VERSION 2.8)

set( CMAKE_CXX_STANDARD 17 )

project(ZigZagMin)


add_executable(ZigZag
    main.cpp
    ZigZagObject.cpp
    BaseOperator.cpp
    BaseDataSource.cpp
    BaseDataInput.cpp
)

#${CMAKE_CURRENT_SOURCE_DIR}
target_include_directories(ZigZag PRIVATE third_party/boost_1_72_0)
