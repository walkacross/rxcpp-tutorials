cmake_minimum_required(VERSION 3.15)
project(unsubscribe)

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/third_party/RxCpp/Rx/v2/src")