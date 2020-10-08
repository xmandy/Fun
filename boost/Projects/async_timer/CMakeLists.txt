cmake_minimum_required(VERSION 2.6)

project(timer)
    
set(INK_DIR /usr/local/lib)
set(INC_DIR /usr/local/include/)
set(SRC_LST main.cpp)

link_directories(/usr/local/lib)

set(EXTRA_LIBS boost_system)

include_directories(${INC_DIR})

add_executable(timer ${SRC_LST})
target_link_libraries(timer ${EXTRA_LIBS})



