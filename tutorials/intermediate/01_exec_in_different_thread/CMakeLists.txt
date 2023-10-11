cmake_minimum_required(VERSION 3.15)
project(exec_in_different_thread)

find_package(Threads REQUIRED)

add_executable(observe_on observe_on.cpp)
target_link_libraries(observe_on PRIVATE Threads::Threads)
target_include_directories(observe_on PUBLIC "${CMAKE_SOURCE_DIR}/third_party/RxCpp/Rx/v2/src")

add_executable(publish publish.cpp)
target_link_libraries(publish PRIVATE Threads::Threads)
target_include_directories(publish PUBLIC "${CMAKE_SOURCE_DIR}/third_party/RxCpp/Rx/v2/src")