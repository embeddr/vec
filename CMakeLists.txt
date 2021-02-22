cmake_minimum_required(VERSION 3.17)
project(vec LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Vec header-only library
add_library(vec INTERFACE)
target_include_directories(vec INTERFACE .)

# Doctest header-only library
set(DOCTEST_INCLUDE_DIR tests/doctest/doctest)
add_library(doctest INTERFACE)
target_include_directories(doctest INTERFACE ${DOCTEST_INCLUDE_DIR})

# Vec test executable
add_executable(test_vec tests/test_vec.cpp)
target_link_libraries(test_vec LINK_PUBLIC vec doctest)

# Build options
target_compile_options(test_vec PRIVATE -O0) # add flags here
