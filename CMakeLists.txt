cmake_minimum_required(VERSION 2.8)
project(mcv CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(include)

file(GLOB SRC_FILES "src/*.cpp")

add_library(mcv SHARED ${SRC_FILES})
target_link_libraries(mcv c m)

file(GLOB TEST_FILES "test/test_gas.cpp")
add_executable(test ${TEST_FILES})
target_link_libraries(test mcv)
