cmake_minimum_required(VERSION 3.0)

project(geoglobe)

add_executable(geoglobe main.cpp)

install(TARGETS geoglobe RUNTIME DESTINATION bin)
