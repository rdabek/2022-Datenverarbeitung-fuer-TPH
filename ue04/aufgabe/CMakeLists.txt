cmake_minimum_required(VERSION 3.13)
project(UE02 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17) 

set(TARGET_NAME aufgabe)

add_executable(${TARGET_NAME} main.cpp)

add_subdirectory(utils)

# Compile options
target_compile_options(
    ${TARGET_NAME}
        PRIVATE
            $<$<CXX_COMPILER_ID:GNU>:-Wall -Werror>
)