cmake_minimum_required(VERSION 2.6)

project(print_app)
add_subdirectory(main)
add_subdirectory(test)

enable_testing()
add_test(test_case test)
