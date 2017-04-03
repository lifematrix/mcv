cmake_minimum_required(VERSION 2.8)
project(mcv CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(include)

file(GLOB SRC_FILES "src/*.cpp")

add_library(mcv SHARED ${SRC_FILES})
