cmake_minimum_required(VERSION 2.6)

project(epy_link)

set(INCLUDE_DIR /usr/include/python2.7)
include_directories(${INCLUDE_DIR})

#message(${CMAKE_SOURCE_DIR})

link_directories(/usr/local/lib)

set(EXTRA_LIBS 
   python2.7
   ${CMAKE_SOURCE_DIR}/my.a
   ${CMAKE_SOURCE_DIR}/hello_ext.a
   boost_system
   boost_python
    )

set(SRC_LST main.cpp)

add_executable(epy_link ${SRC_LST})
target_link_libraries(epy_link ${EXTRA_LIBS})
