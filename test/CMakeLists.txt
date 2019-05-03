cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)

include_directories(..)

set(TESTS_SRC sample.cc test-mstring.cc)
add_executable(test test-main.cc ${TESTS_SRC})
target_link_libraries(test mstring)
