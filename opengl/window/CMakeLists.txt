cmake_minimum_required(VERSION 2.6)


# project
project(window)


set(INC_DIR /usr/local/include/)
include_directories(${INC_DIR})


set(INK_DIR /usr/local/lib)
link_directories(${INK_DIR})


set(SRC_LST main.cpp)
add_executable(window ${SRC_LST})

set(APPLE_FM "Cocoa" "CoreVideo" "IOKit" "OpenGL")

foreach(frame ${APPLE_FM})
#message(STATUS ${frame})
	set(TMP "FOUND_LIB-NOTFOUND")
	find_library(TMP ${frame})
	if (NOT TMP)
		message(FATAL_ERROR "FRAMEWORK "  ${frame}  " not found")
	endif()	
	list(APPEND SYS_FW ${TMP})
endforeach()
message(STATUS "the library: " ${SYS_FW})

target_link_libraries(window glew glfw3 ${SYS_FW})




