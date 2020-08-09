cmake_minimum_required(VERSION 2.6)

project(demo1)
set(SRC_LST main.cpp)

find_package(Boost 1.71 REQUIRED date_time system regex)
message(STATUS ${Boost_INCLUDE_DIRS})
message(STATUS ${Boost_LIBRARIES})
message(STATUS ${CMAKE_MSVC_RUNTIME_LIBRARY})
    
# include dir
set(INCLUDE_DIR ${Boost_INCLUDE_DIRS})
include_directories(${INCLUDE_DIR})


# libraries
set(EXTRA_LIBS ${Boost_LIBRARIES})
#set(LIB_DIR ${Boost_INCLUDE_DIRS})
#link_directories(${LIB_DIR})



add_executable(demo1 ${SRC_LST})
target_link_libraries(demo1 ${EXTRA_LIBS})


