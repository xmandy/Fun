cmake_minimum_required(VERSION 2.6)

project(bp_hw)
    
set(INK_DIR /usr/local/lib)
set(INC_DIR /usr/local/include/ /usr/include/python2.7/)
set(SRC_LST hw.cpp)

link_directories(/usr/local/lib)

set(EXTRA_LIBS boost_system boost_python)

include_directories(${INC_DIR})

add_library(bp_hw SHARED ${SRC_LST})
set_target_properties(bp_hw PROPERTIES PREFIX "")
set_target_properties(bp_hw PROPERTIES OUTPUT_NAME "hello_ext")
target_link_libraries(bp_hw ${EXTRA_LIBS})



