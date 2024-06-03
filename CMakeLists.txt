cmake_minimum_required(VERSION 3.28)
project(chip8)

set(CMAKE_CXX_STANDARD 26)
if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

list(APPEND CMAKE_PREFIX_PATH "/Library/Frameworks/SDL2.framework/Resources/CMake")
find_package(SDL2 REQUIRED)

include_directories("./include")

add_executable(chip8 src/main.cpp)

target_link_libraries(
        chip8
        PUBLIC
        SDL2::SDL2
        SDL2::SDL2main
)