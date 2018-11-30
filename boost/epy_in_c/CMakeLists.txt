cmake_minimum_required(VERSION 2.6)

project(epy_in_c)

set(INCLUDE_DIR /usr/include/python2.7)
include_directories(${INCLUDE_DIR})

set(EXTRA_LIBS python2.7)

set(SRC_LST mymodule.c)

#add_library(epy_in_c SHARED ${SRC_LST})
add_library(epy_in_c STATIC ${SRC_LST})
set_target_properties(epy_in_c PROPERTIES PREFIX "")
set_target_properties(epy_in_c PROPERTIES OUTPUT_NAME "my")
target_link_libraries(epy_in_c ${EXTRA_LIBS})

