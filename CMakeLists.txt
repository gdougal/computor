cmake_minimum_required(VERSION 3.21)
project(computerov)

set(CMAKE_CXX_STANDARD 20)


include_directories(srcs/include)
add_executable(computor srcs/computor.cpp)
