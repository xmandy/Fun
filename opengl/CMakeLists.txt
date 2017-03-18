cmake_minimum_required(VERSION 2.6)

# solution
project(LearnOpenGL)

message(STATUS ${CMAKE_SYSTEM_NAME})

#if (WIN32)
#    message(STATUS "The platform is win32")
#elseif(APPLE)
#    message(STATUS "The platform is apple")
#endif()
if (${CMAKE_SYSTEM_NAME} MATCHES Darwin)
    set(MAC_OS_X TRUE)
    add_definitions(-DMAC_OS_X)
endif()

if (MAC_OS_X)
    message(STATUS  "Platform is mac")
endif()

if (WIN32)
    message(STATUS "Platform is win32")
endif()

message(STATUS "cxx Flags: " ${CMAKE_CXXFLAGS})

# add project
add_subdirectory(window)


