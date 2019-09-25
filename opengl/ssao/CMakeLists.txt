cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0015 NEW)
# see: https://cmake.org/cmake/help/v3.0/policy/CMP0015.html

# project
project(ssao)

if (WIN32)
    set(INC_DIR "${CMAKE_SOURCE_DIR}/3rdlibs/Base/Include")
    set(INK_DIR "${CMAKE_SOURCE_DIR}/3rdlibs/Base/Libs" ${CMAKE_SOURCE_DIR}/3rdlibs/SOIL/lib ${CMAKE_SOURCE_DIR}/3rdlibs/assimp-3.3.1/lib)
    set(EXTRA_LIBS ${EXTRA_LIBS} opengl32)
elseif (MAC_OS_X)
    set(INC_DIR /usr/local/include/)
    set(INK_DIR /usr/local/lib ${CMAKE_SOURCE_DIR}/3rdlibs/SOIL/lib)
endif()

list(APPEND INC_DIR ${CMAKE_SOURCE_DIR}/custom ${CMAKE_SOURCE_DIR}/common)
list(APPEND INC_DIR ${CMAKE_SOURCE_DIR}/3rdlibs/SOIL/src ${CMAKE_SOURCE_DIR}/3rdlibs/glm ${CMAKE_SOURCE_DIR}/3rdlibs/assimp-3.3.1/include)


include_directories(${INC_DIR})
link_directories(${INK_DIR})

# show link dir
get_directory_property(OUT_VAR LINK_DIRECTORIES)
message(STATUS "link_directories: " ${OUT_VAR})

set(EXTRA_LIBS ${EXTRA_LIBS} glew glfw3 SOIL assimp assimp-vc140-mt)

set(INC_LST 
		${CMAKE_SOURCE_DIR}/custom/Shader.h
		${CMAKE_SOURCE_DIR}/custom/Camera.h
		${CMAKE_SOURCE_DIR}/custom/Mesh.h
		${CMAKE_SOURCE_DIR}/common/BasicDataTypes.h
		${CMAKE_SOURCE_DIR}/custom/Line.h
		${CMAKE_SOURCE_DIR}/custom/Model.hpp
		)

set(SRC_LST 
		${CMAKE_SOURCE_DIR}/common/PlatformUtils.cpp
		${CMAKE_SOURCE_DIR}/common/BasicDataTypes.cpp
		${CMAKE_SOURCE_DIR}/custom/Line.cpp
		main.cpp
		${CMAKE_SOURCE_DIR}/custom/Shader.cpp
        ${CMAKE_SOURCE_DIR}/custom/Camera.cpp
        ${CMAKE_SOURCE_DIR}/custom/Mesh.cpp
		${CMAKE_SOURCE_DIR}/custom/Model.cpp
		)
add_executable(ssao ${SRC_LST} ${INC_LST})

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

target_link_libraries(ssao ${EXTRA_LIBS})

if (WIN32)
	add_custom_command(TARGET ssao POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	${CMAKE_SOURCE_DIR}/3rdlibs/assimp-3.3.1/lib/assimp-vc140-mt.dll
	${PROJECT_BINARY_DIR}/Debug)

endif()


