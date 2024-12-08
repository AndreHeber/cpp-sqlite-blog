cmake_minimum_required(VERSION 3.10)
project(BloggingSoftware)

set(CMAKE_CXX_STANDARD 17)

add_executable(blog src/main.cpp)
include_directories(include)
