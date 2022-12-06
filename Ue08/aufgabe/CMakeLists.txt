cmake_minimum_required(VERSION 3.13)
project(UE08 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_definitions("-fconcepts")   # Compiler complained with auto param in constructor...

set(TARGET_NAME aufgabe)

add_executable(${TARGET_NAME} testbruch.cpp)

add_subdirectory(utils)

# Compile options
target_compile_options(
    ${TARGET_NAME}
        PRIVATE
            $<$<CXX_COMPILER_ID:GNU>:-Wall -Werror>
)