cmake_minimum_required(VERSION 3.15)
project(create_event_stream)

add_executable(${PROJECT_NAME} main.cpp)
#message(Status ${rxcpp_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/third_party/RxCpp/Rx/v2/src")

add_executable(create_stream_by_factory_functions create_stream_by_factory_functions.cpp)
#message(Status ${rxcpp_SOURCE_DIR})
target_include_directories(create_stream_by_factory_functions PUBLIC "${CMAKE_SOURCE_DIR}/third_party/RxCpp/Rx/v2/src")