cmake_minimum_required(VERSION 3.17)
project(vec)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Header-only library
add_library(vec INTERFACE)

# Include directories for library
target_include_directories(vec INTERFACE include/)

# Test executable
add_executable(vec_test main.cpp)
target_link_libraries(vec_test LINK_PUBLIC vec)

# Build options
target_compile_options(vec_test PRIVATE -O0) # add flags here
