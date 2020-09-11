cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

project(ZigZagCore VERSION 0.1.0)

add_subdirectory(external/lua)
add_subdirectory(external/sol2)

SET(SOURCES
    source/ZigZag/BaseBehaviour.cpp
    source/ZigZag/BaseDataInput.cpp
    source/ZigZag/BaseDataSource.cpp
    source/ZigZag/BaseOperator.cpp
    source/ZigZag/BaseParameter.cpp
    source/ZigZag/LuaBehaviour.cpp
    source/ZigZag/Object.cpp
    source/ZigZag/ObjectFactory.cpp
    source/ZigZag/ObjectSelection.cpp
    source/ZigZag/PluginLoader.cpp
    source/ZigZag/RenderOrder.cpp
    source/ZigZag/UnixPluginLoader.cpp
    source/ZigZag/WindowsPluginLoader.cpp
)

SET(HEADERS
    include/ZigZag/IDataSource.hpp
    include/ZigZag/Platform.hpp
    source/ZigZag/BaseBehaviour.hpp
    source/ZigZag/BaseDataInput.hpp
    source/ZigZag/BaseDataSource.hpp
    source/ZigZag/BaseOperator.hpp
    source/ZigZag/BaseParameter.hpp
    source/ZigZag/LuaBehaviour.hpp
    source/ZigZag/Object.hpp
    source/ZigZag/ObjectFactory.hpp
    source/ZigZag/ObjectSelection.hpp
    source/ZigZag/PlatformPluginLoader.hpp
    source/ZigZag/PluginLoader.hpp
    source/ZigZag/RenderOrder.hpp
    source/ZigZag/TParameter.hpp
    source/ZigZag/UnixPluginLoader.hpp
    source/ZigZag/WindowsPluginLoader.hpp
    source/ZigZag/detail/InputOutput.hpp
    source/ZigZag/detail/ParentChild.hpp
)

add_library(ZigZagCore STATIC ${SOURCES} ${HEADERS})

target_include_directories(ZigZagCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source)
target_include_directories(ZigZagCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(ZigZagCore lua)
target_link_libraries(ZigZagCore sol2)
