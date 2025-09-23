add_executable(lfu)

target_include_directories(lfu PRIVATE ${PROJECT_SOURCE_DIR})

target_sources(lfu PRIVATE
    main.cpp
)