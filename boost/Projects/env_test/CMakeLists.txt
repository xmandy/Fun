cmake_minimum_required(VERSION 2.6)


# project
project(EnvTest)

find_package(Boost REQUIRED COMPONENTS
             date_time)

add_executable(${PROJECT_NAME} env_test.cpp)
target_link_libraries(${PROJECT_NAME} Boost::date_time)
