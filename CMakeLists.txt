cmake_minimum_required (VERSION 2.6)
project (Tinder)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
link_directories("${PROJECT_SOURCE_DIR}/lib")
include_directories ("${PROJECT_SOURCE_DIR}/include")

set(TEST_LINK_LIBS libgtest.a z pthread rt)

add_executable (test test/googleTest.cpp)
add_executable (main src/main.cpp)
target_link_libraries (test ${TEST_LINK_LIBS})
