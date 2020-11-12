cmake_minimum_required(VERSION 3.1)

project(tp_lk_2d_mp_shooter LANGUAGES CXX)

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/*.cpp")

add_executable(tp_lk_2d_mp_shooter ${sources})


