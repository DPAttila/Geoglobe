cmake_minimum_required(VERSION 3.0)

project(geoglobe)

include_directories(agl2.0/include)
include_directories(agl2.0/imgui-master)
include_directories(agl2.0/imgui-master/examples)
include_directories(agl2.0/glad)
include_directories(agl2.0/stb)
include_directories(include)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

find_package(OpenGL REQUIRED)

link_directories(agl2.0)
link_libraries(agl GL)

# link_directories(src)

add_executable(geoglobe ${SRC_FILES} agl2.0/)

install(TARGETS geoglobe RUNTIME DESTINATION bin)
