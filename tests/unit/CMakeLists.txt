cmake_minimum_required(VERSION 3.11)

project(unit_test)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(GTest REQUIRED)

add_executable(unit_tests
    test.cpp
)

target_include_directories(unit_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR} /inc
    ../../lfu/inc
    lfu_cache.hpp
)

target_link_libraries(unit_tests PRIVATE GTest::gtest GTest::gtest_main)

enable_testing()
add_test(NAME unit_test COMMAND unit_tests)

