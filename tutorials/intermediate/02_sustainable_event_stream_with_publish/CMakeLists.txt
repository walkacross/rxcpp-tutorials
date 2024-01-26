cmake_minimum_required(VERSION 3.15)
project(sustainable_envet_streams_with_publish)

add_executable(sustainable_envet_streams_with_publish main.cpp)
target_include_directories(sustainable_envet_streams_with_publish PUBLIC "${CMAKE_SOURCE_DIR}/third_party/RxCpp/Rx/v2/src")