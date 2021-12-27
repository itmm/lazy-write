cmake_minimum_required(VERSION 3.16.3)
project(lazy-write)

set(CMAKE_CXX_STANDARD 17)

add_library(lazy-write lazy-write.cpp)
target_include_directories(lazy-write PUBLIC .)
