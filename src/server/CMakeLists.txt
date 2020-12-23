cmake_minimum_required(VERSION 3.1)

project(tp_lk_2d_mp_shooter LANGUAGES CXX)

##
### Test definitions ###
##

configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(test)

##
### Source definitions ###
##
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

find_package(Boost)
include_directories("${PROJECT_SOURCE_DIR}/include" (${Boost_INCLUDE_DIRS}))

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/*.cpp")

add_executable(tp_lk_2d_mp_shooter ${sources})
target_link_libraries(tp_lk_2d_mp_shooter ${Boost_LIBRARIES} Threads::Threads)