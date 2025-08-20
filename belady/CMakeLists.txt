cmake_minimum_required(VERSION 3.11)
project(cache)
add_executable(cache)

target_include_directories(cache PUBLIC ${PROJECT_SOURCE_DIR}/inc)

target_sources(cache PRIVATE
    main.cpp
)

target_compile_options(cache PRIVATE
    $<$<CONFIG:DEBUG>:
        -Wall
        -Wextra
        -Wpedantic
        -g
        -O0
        -DDEBUG
        -Wmissing-declarations
        -Wcast-align
        -Wunused
        -Wshadow
        -Wsign-conversion
        -fsanitize=address>
)

target_link_libraries(cache PRIVATE m)

set_property(TARGET cache PROPERTY CXX_STANDARD 23)

target_link_options(cache PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address>
)