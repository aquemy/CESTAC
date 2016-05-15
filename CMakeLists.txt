cmake_minimum_required (VERSION 2.8)
project(CESTAC)
enable_language(CXX)

set(CMAKE_CXX_FLAGS         "-std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG   "-Wunknown-pragmas -O0 -g -Wall -Wextra -ansi -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-Wunknown-pragmas -O2")

include_directories(${CMAKE_SOURCE_DIR}/include)

set (CESTAC_FILES
    src/utils.cpp
    src/pert.cpp
    include/double.hpp
    include/utils.hpp
    include/pert.hpp
)
add_definitions("-DDEBUG")
add_library(cestac STATIC ${CESTAC_FILES})

add_executable (example example.cpp)
target_link_libraries (example cestac)
