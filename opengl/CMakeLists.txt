cmake_minimum_required(VERSION 2.6)

# solution
project(LearnOpenGL)

if (WIN32)
    message(STATUS "The platform is win32")
elseif(APPLE)
    message(STATUS "The platform is apple")
endif()

message(STATUS "cxx Flags: " ${CMAKE_CXXFLAGS})

# add project
add_subdirectory(window)


