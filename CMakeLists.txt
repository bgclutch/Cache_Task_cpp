cmake_minimum_required(VERSION 3.30)

project(cache)

add_subdirectory(lfu)
add_subdirectory(belady)
add_subdirectory(tests)

option(ENABLE_ASAN OFF)

foreach(target lfu belady tests)
    target_compile_features(${target} PUBLIC cxx_std_23)
endforeach()

foreach(target lfu belady)
    target_compile_options(${target} PRIVATE
    $<$<CONFIG:Debug>:
        -Wall
        -Wextra
        -Wpedantic
        -DDEBUG
        -Wmissing-declarations
        -Wcast-align
        -Wshadow
        -Wsign-conversion>
    )
    if(ENABLE_ASAN)
        target_compile_options(${target} PRIVATE $<$<CONFIG:Debug>: -fsanitize=address>)
        target_link_options(${target} PRIVATE $<$<CONFIG:Debug>: -fsanitize=address>)
    endif()
endforeach()
