
include_directories("G:/My Documents/3rdLibraries/Include")
link_directories("G:/My Documents/3rdLibraries/Libs")
get_directory_property(OUT_VAR LINK_DIRECTORIES)
message(STATUS "Dir: ${OUT_VAR}")
message(STATUS "ExtraLibs ${EXTRA_LIBS}")

set(EXTRA_LIBS ${EXTRA_LIBS} glew glfw3)

message(STATUS "ExtraLibs ${EXTRA_LIBS}")

add_executable(window main.cpp)
target_link_libraries(window ${EXTRA_LIBS})


