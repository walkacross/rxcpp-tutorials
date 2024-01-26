cmake_minimum_required(VERSION 3.15)
project(hot_cold_observable)

add_executable(hot_cold_observable main.cpp)
target_include_directories(hot_cold_observable PUBLIC "${CMAKE_SOURCE_DIR}/third_party/RxCpp/Rx/v2/src")