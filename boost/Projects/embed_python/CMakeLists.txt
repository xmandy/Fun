cmake_minimum_required(VERSION 2.6)

project(embed_py)

set(INCLUDE_DIR /usr/include/python2.7)
include_directories(${INCLUDE_DIR})

#set(LINK_DIR /usr/)

set(EXTRA_LIBS python2.7)

set(SRC_LST main.cpp)

add_executable(embed_py ${SRC_LST})
target_link_libraries(embed_py ${EXTRA_LIBS})
