cmake_minimum_required(VERSION 2.6)


# project
project(window)


set(INC_DIR /usr/local/include/GL /usr/local/include/GLFW)
include_directories(${INC_DIR})


set(INK_DIR /usr/local/lib)
link_directories(${INK_DIR})


set(SRC_LST main.cpp)
add_executable(window ${SRC_LST})
target_link_libraries(window glew glfw3)




