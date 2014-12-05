cmake_minimum_required(VERSION 2.6)

project(tester)
include_directories(${CMAKE_SOURCE_DIR}/main)
add_executable(tester test_runner.cpp)
target_link_libraries(tester print)
