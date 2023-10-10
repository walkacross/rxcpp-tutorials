cmake_minimum_required(VERSION 3.15)
project(rxcpp_demo)

add_executable(rxcpp_demo main.cpp)
#message(Status ${rxcpp_SOURCE_DIR})
target_include_directories(rxcpp_demo PUBLIC "${CMAKE_SOURCE_DIR}/third_party/RxCpp/Rx/v2/src")