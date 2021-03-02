cmake_minimum_required(VERSION 3.17)
project(vec LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

########################################
# LIBRARY
########################################

# Vec header-only library
add_library(vec INTERFACE)
target_include_directories(vec INTERFACE include/)

########################################
# UNIT TESTS
########################################

# Doctest header-only library
set(DOCTEST_INCLUDE_DIR tests/doctest/doctest)
add_library(doctest INTERFACE)
target_include_directories(doctest INTERFACE ${DOCTEST_INCLUDE_DIR})

# Test utils header-only library
add_library(test_utils INTERFACE)
target_include_directories(doctest INTERFACE tests/test_utils/)

# Vec test executable (basic)
add_executable(test_vec_basic tests/test_vec_basic.cpp)
target_link_libraries(test_vec_basic LINK_PUBLIC vec doctest test_utils)
target_compile_options(test_vec_basic PRIVATE -O0)

# Vec test executable (operators)
add_executable(test_vec_operators tests/test_vec_operators.cpp)
target_link_libraries(test_vec_operators LINK_PUBLIC vec doctest test_utils)
target_compile_options(test_vec_operators PRIVATE -O0)

# Vec test executable (friends)
add_executable(test_vec_friends tests/test_vec_friends.cpp)
target_link_libraries(test_vec_friends LINK_PUBLIC vec doctest test_utils)
target_compile_options(test_vec_friends PRIVATE -O0)
