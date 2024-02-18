cmake_minimum_required(VERSION 3.10)

project(ds4432)
set(CMAKE_C_STANDARD 99)

include_directories(include)
add_library(ds4432 STATIC
            src/ds4432.c)

add_executable(test test/test.c)
target_link_libraries(test ds4432)
