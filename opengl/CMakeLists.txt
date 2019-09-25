cmake_minimum_required(VERSION 2.6)

# solution
project(LearnOpenGL)

message(STATUS "cxx Flags: " ${CMAKE_CXX_FLAGS})
message(STATUS "c Flags: " ${CMAKE_C_FLAGS})
message(STATUS ${CMAKE_SYSTEM_NAME})

#if (WIN32)
#    message(STATUS "The platform is win32")
#elseif(APPLE)
#    message(STATUS "The platform is apple")
#endif()
if (${CMAKE_SYSTEM_NAME} MATCHES Darwin)
    set(MAC_OS_X TRUE)
    add_definitions(-DMAC_OS_X)
elseif(${CMAKE_SYSTEM_NAME} MATCHES Windows)
    set(WIN32 TRUE)
    add_definitions(-DWIN32)
endif()

if (MAC_OS_X)
    message(STATUS  "Platform is mac")
endif()

if (WIN32)
    message(STATUS "Platform is win32")
endif()

message(STATUS "cxx Flags: " ${CMAKE_CXXFLAGS})

set(ASSET_ROOT ${CMAKE_SOURCE_DIR}/Assets)
configure_file(${CMAKE_SOURCE_DIR}/common/PlatformUtils.h.in ${CMAKE_SOURCE_DIR}/common/PlatformUtils.h @ONLY)

# add project
add_subdirectory(window)

add_subdirectory(shader)

add_subdirectory(texture_learn)

add_subdirectory(camera_learn)

add_subdirectory(colors)

add_subdirectory(phong)

add_subdirectory(material)

add_subdirectory(light_learn)

add_subdirectory(model)

add_subdirectory(depth)

add_subdirectory(framebuffer)

add_subdirectory(geo_shader)

add_subdirectory(stencil)

add_subdirectory(cylinder)

add_subdirectory(landscape)

add_subdirectory(base)

add_subdirectory(ssao)






