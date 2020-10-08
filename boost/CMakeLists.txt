cmake_minimum_required(VERSION 2.6)

# solution
project(LearnBoost)

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
    set(BOOST_ROOT "./BoostLib")
    set(Boost_USE_STATIC_LIBS ON)
    # set(Boost_COMPILER "-vc141")

endif()

# Only set RelWithDebInfo configuration
set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose build type" FORCE)
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Relase" "RelWithDebInfo")
set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} CACHE STRING "My multi config types" FORCE)


# set RunTime
# can also set by https://cmake.org/cmake/help/v3.15/prop_tgt/MSVC_RUNTIME_LIBRARY.html
# but it only affects specified target
if(WIN32)
set(MSVC_RUNTIME "mt" CACHE STRING "MSVC Runtime")
set_property(CACHE MSVC_RUNTIME PROPERTY STRINGS "mt" "md")

if(${MSVC_RUNTIME} STREQUAL "mt")
    foreach(flag_var
            CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
            CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
            message(STATUS "origin: " ${${flag_var}})
            if(${${flag_var}} MATCHES "/MDd")
                string(REGEX REPLACE "/MDd" "/MT" ${flag_var} "${${flag_var}}")
            endif()
            if(${${flag_var}} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
            endif()
            message(STATUS "new: " ${${flag_var}})
    endforeach()

endif()



endif()

message(STATUS "cxx Flags: " ${CMAKE_CXXFLAGS})

find_package(Boost)

message(STATUS "IncludePath: " ${Boost_INCLUDE_DIRS})
message(STATUS "LibraryPath " ${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

add_subdirectory(Projects/env_test)

