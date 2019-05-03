cmake_minimum_required(VERSION 3.13)
project(parse_diff C CXX)

set(CMAKE_C_STANDARD 99)

add_subdirectory(mlog)

add_library(mstring mstring.c)

add_executable(parse_diff main.c logic.c)
target_link_libraries(parse_diff mstring mlog)


add_subdirectory(test)