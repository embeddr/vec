cmake_minimum_required(VERSION 3.12)
project(vec LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

########################################
# LIBRARY
########################################

# Vec header-only library
set(VEC_INCLUDE_DIR include/)
add_library(vec INTERFACE)
target_include_directories(vec INTERFACE ${VEC_INCLUDE_DIR})

########################################
# UNIT TESTS
########################################

enable_testing()

# Doctest header-only library
set(DOCTEST_INCLUDE_DIR tests/doctest/doctest/)
add_library(doctest INTERFACE)
target_include_directories(doctest INTERFACE ${DOCTEST_INCLUDE_DIR})

# Test utils header-only library
set(TEST_UTILS_INCLUDE_DIR tests/test_utils/)
add_library(test_utils INTERFACE)
target_include_directories(doctest INTERFACE ${TEST_UTILS_INCLUDE_DIR})

# Test utils test executable
add_executable(test_test_utils tests/test_test_utils.cpp)
target_link_libraries(test_test_utils LINK_PUBLIC vec doctest test_utils)
target_compile_options(test_test_utils PRIVATE -O0)
add_test(test_test_utils test_test_utils)

# Vector test executables
add_executable(test_vec_basic tests/test_vec_basic.cpp)
target_link_libraries(test_vec_basic LINK_PUBLIC vec doctest test_utils)
target_compile_options(test_vec_basic PRIVATE -O0)
add_test(test_vec_basic test_vec_basic)

add_executable(test_vec_operators tests/test_vec_operators.cpp)
target_link_libraries(test_vec_operators LINK_PUBLIC vec doctest test_utils)
target_compile_options(test_vec_operators PRIVATE -O0)
add_test(test_vec_operators test_vec_operators)

add_executable(test_vec_friends tests/test_vec_friends.cpp)
target_link_libraries(test_vec_friends LINK_PUBLIC vec doctest test_utils)
target_compile_options(test_vec_friends PRIVATE -O0)
add_test(test_vec_friends test_vec_friends)

# Matrix test executables
add_executable(test_mat_basic tests/test_mat_basic.cpp)
target_link_libraries(test_mat_basic LINK_PUBLIC vec doctest test_utils)
target_compile_options(test_mat_basic PRIVATE -O0)
add_test(test_mat_basic test_mat_basic)

add_executable(test_mat_operators tests/test_mat_operators.cpp)
target_link_libraries(test_mat_operators LINK_PUBLIC vec doctest test_utils)
target_compile_options(test_mat_operators PRIVATE -O0)
add_test(test_mat_operators test_mat_operators)

add_executable(test_mat_friends tests/test_mat_friends.cpp)
target_link_libraries(test_mat_friends LINK_PUBLIC vec doctest test_utils)
target_compile_options(test_mat_friends PRIVATE -O0)
add_test(test_mat_friends test_mat_friends)

# Transform test executables
add_executable(test_transform tests/test_transform.cpp)
target_link_libraries(test_transform LINK_PUBLIC vec doctest test_utils)
target_compile_options(test_transform PRIVATE -O0)
add_test(test_transform test_transform)

########################################
# EXAMPLES
########################################

# Target hit detection executable
add_executable(target_hit_detection examples/target_hit_detection.cpp)
target_link_libraries(target_hit_detection LINK_PUBLIC vec)
target_compile_options(target_hit_detection PRIVATE -O0)
