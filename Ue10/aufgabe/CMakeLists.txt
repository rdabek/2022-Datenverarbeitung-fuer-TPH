cmake_minimum_required(VERSION 3.13)
project(UE10 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_definitions("-fconcepts")   # Compiler complained with auto param in constructor...

set(TARGET_NAME aufgabe)

find_package(
    Boost
        COMPONENTS
            system
            filesystem
            iostreams

    REQUIRED
)

add_executable(${TARGET_NAME} main.cpp)

add_subdirectory(utils)

target_link_libraries(
    ${TARGET_NAME}
        Boost::system
        Boost::filesystem
        Boost::iostreams
        stdc++fs
)

# Compile options
target_compile_options(
    ${TARGET_NAME}
        PRIVATE
            $<$<CXX_COMPILER_ID:GNU>:-Wall -Werror>
)