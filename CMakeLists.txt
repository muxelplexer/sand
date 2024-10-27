cmake_minimum_required(VERSION 3.29)
project(sand
        VERSION 0.0.1)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    SDL
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG main  # Replace this with a particular git tag or git hash
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    SYSTEM
)

FetchContent_MakeAvailable(SDL)

add_executable(sand
    src/main.c
    src/world.c
)

target_include_directories(sand PRIVATE
    inc/
)

target_link_libraries(sand PRIVATE
    SDL3::SDL3
)
target_compile_definitions(sand PUBLIC SDL_MAIN_USE_CALLBACKS)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}")
set_target_properties(sand PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")

target_compile_options(sand PRIVATE
    -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -fms-extensions
)


set_property(TARGET sand PROPERTY C_STANDARD 23)
set_property(TARGET sand PROPERTY C_EXTENSIONS FALSE)
