cmake_minimum_required(VERSION 2.6)

project(BoostLearn)
    
# Use FindBoost.cmake
# https://cmake.org/cmake/help/v3.15/module/FindBoost.html
set(BOOST_ROOT D:/my-workspace/Codes/boost_1_71_0/BoostLib)
set(BOOST_INCLUDEDIR D:/my-workspace/Codes/boost_1_71_0/BoostLib/include/boost-1_71)
set(BOOST_LIBRARYDIR     D:/my-workspace/Codes/boost_1_71_0/BoostLib/lib)
set(Boost_ADDITIONAL_VERSIONS "1.71" "1.71.0")
set(Boost_USE_STATIC_LIBS       ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    ON)
set(Boost_NO_SYSTEM_PATHS ON)

# If you want to use static runtime library use following
# see https://gitlab.kitware.com/cmake/community/wikis/FAQ#how-can-i-build-my-msvc-application-with-a-static-runtime
if(MSVC)     
    # Use the static C library for all build types
    foreach(var 
        CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
      )
      if(${var} MATCHES "/MD")
        string(REGEX REPLACE "/MD" "/MT" ${var} "${${var}}")
      endif()
    endforeach()    
endif(MSVC)


set(EXTRA_LIBS boost_system)

add_subdirectory(demo1)



