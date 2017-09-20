cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0015 NEW)
# see: https://cmake.org/cmake/help/v3.0/policy/CMP0015.html

# project
project(model)

if (WIN32)
    set(INC_DIR "../3rdlibs/Base/Include")
    set(INK_DIR "../3rdlibs/Base/Libs" ../3rdlibs/SOIL/lib ../3rdlibs/assimp-3.3.1/lib)
    set(EXTRA_LIBS ${EXTRA_LIBS} opengl32)
elseif (MAC_OS_X)
    set(INC_DIR /usr/local/include/)
    set(INK_DIR /usr/local/lib ../3rdlibs/SOIL/lib ../3rdlibs/assimp-3.3.1/lib)
endif()

list(APPEND INC_DIR ../custom ../common)
list(APPEND INC_DIR ../3rdlibs/SOIL/src ../3rdlibs/glm ../3rdlibs/assimp-3.3.1/include)


include_directories(${INC_DIR})
link_directories(${INK_DIR})

# show link dir
get_directory_property(OUT_VAR LINK_DIRECTORIES)
message(STATUS "link_directories: " ${OUT_VAR})

set(EXTRA_LIBS ${EXTRA_LIBS} glew glfw3 SOIL assimp assimp-vc140-mt.dll)

set(INC_LST 
		../custom/Mesh.h
		../custom/Model.hpp
		../custom/Shader.h
		../custom/Camera.h)

set(SRC_LST 
		../common/PlatformUtils.cpp
		main.cpp
		../custom/Mesh.cpp
		../custom/Shader.cpp
        ../custom/Camera.cpp
		../custom/Model.cpp
		)
add_executable(model ${SRC_LST} ${INC_LST})

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

target_link_libraries(model ${EXTRA_LIBS})

