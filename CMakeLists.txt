cmake_minimum_required(VERSION 3.13)
project(parse_diff C CXX)

set(CMAKE_C_STANDARD 99)

add_subdirectory(mlog)

add_library(mstring mstring.c)

add_executable(parse_diff main.c)
target_link_libraries(parse_diff mstring mlog)


set(TESTS_SRC tests/sample.cc tests/test-mstring.cc)
add_executable(tests tests/test-main.cc ${TESTS_SRC})
target_link_libraries(tests mstring)
