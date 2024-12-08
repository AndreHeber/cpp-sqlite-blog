cmake_minimum_required(VERSION 3.10)
project(Blog CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(Boost REQUIRED COMPONENTS json)

add_executable(${PROJECT_NAME} src/main.cpp)
include_directories(include)

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::boost Boost::json)
