cmake_minimum_required(VERSION 3.29)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
project(sand
        VERSION 0.0.1)

add_executable(sand
    src/main.c
)

target_include_directories(sand PRIVATE
    inc/
)

# target_link_libraries(sand PRIVATE
# )

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}")
set_target_properties(sand PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")

target_compile_options(sand PRIVATE
    -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -fms-extensions
)


set_property(TARGET sand PROPERTY C_STANDARD 23)
set_property(TARGET sand PROPERTY C_EXTENSIONS FALSE)
