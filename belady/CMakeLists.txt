add_executable(belady)

target_include_directories(belady PRIVATE ${PROJECT_SOURCE_DIR})

target_sources(belady PRIVATE
    main.cpp
)