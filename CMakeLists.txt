cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# root project name
project(rxcpp-tutorials)

# TODO project version and options, wrap marco

# set cxx minimum standard to c++ 14
# set c++ standard to 17
set( CMAKE_CXX_STANDARD_REQUIRED ON )
if( CMAKE_CXX_STANDARD VERSION_LESS 17 )
    set( CMAKE_CXX_STANDARD 17 )
endif()


# check build type
if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release")
endif()

# load custom cmake interface
set(CUSTOM_INTERFACE_LC "${CMAKE_CURRENT_SOURCE_DIR}/cmake/api.cmake")
if(EXISTS ${CUSTOM_INTERFACE_LC})
    include(${CUSTOM_INTERFACE_LC})
else()
    message(FATAL_ERROR "Load ${CUSTOM_INTERFACE_LC} failed,build process interrupted.")
endif()

# load rxcpp
load_rxcpp(${CMAKE_CURRENT_SOURCE_DIR} v4.1.0)

# load projects
add_subdirectory(tutorials)