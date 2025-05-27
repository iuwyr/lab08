cmake_minimum_required(VERSION 3.10)
project(demo)

add_executable(demo main.cpp)
install(TARGETS demo DESTINATION bin)