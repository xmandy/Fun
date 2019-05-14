cmake_minimum_required(VERSION 2.6)


# project
project(window)

if (WIN32)
    set(INC_DIR "${CMAKE_SOURCE_DIR}/3rdlibs/Base/Include")
    set(INK_DIR "${CMAKE_SOURCE_DIR}/3rdlibs/Base/Libs" ${CMAKE_SOURCE_DIR}/3rdlibs/SOIL/lib)
    set(EXTRA_LIBS ${EXTRA_LIBS} glew glfw3 opengl32)
elseif (MAC_OS_X)
    set(INC_DIR /usr/local/include/)
    set(INK_DIR /usr/local/lib)
endif()

include_directories(${INC_DIR})
link_directories(${INK_DIR})

# show link dir
get_directory_property(OUT_VAR LINK_DIRECTORIES)
message(STATUS "link_directories: " ${OUT_VAR})

set(EXTRA_LIBS ${EXTRA_LIBS} glew glfw3)

set(SRC_LST  main.cpp)
add_executable(window ${SRC_LST})

if (MAC_OS_X)
    set(APPLE_FM "Cocoa" "CoreVideo" "IOKit" "OpenGL")

    foreach(frame ${APPLE_FM})
    #message(STATUS ${frame})
    	set(TMP "FOUND_LIB-NOTFOUND")
    	find_library(TMP ${frame})
    	if (NOT TMP)
    		message(FATAL_ERROR "FRAMEWORK "  ${frame}  " not found")
    	endif()	
        set(EXTRA_LIBS ${EXTRA_LIBS} ${TMP})
        #list(APPEND SYS_FW ${TMP})
    endforeach()
    #message(STATUS "the library: " ${SYS_FW})
endif()

# show extra libs
message(STATUS "ExtraLibs: " ${EXTRA_LIBS})

target_link_libraries(window ${EXTRA_LIBS})

