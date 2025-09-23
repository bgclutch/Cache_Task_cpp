cmake_minimum_required(VERSION 3.30)

project(cache)

set(CMAKE_CXX_STANDARD          23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "
        -Wall
        -Wextra
        -Wpedantic
        -DDEBUG
        -Wmissing-declarations
        -Wcast-align
        -Wshadow
        -Wsign-conversion")

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

add_subdirectory(lfu)
add_subdirectory(belady)