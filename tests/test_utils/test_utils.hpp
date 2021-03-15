// Utilities for Vec unit tests

#pragma once

#include <algorithm>
#include <array>

#include "vec.hpp"
#include "mat.hpp"

using std::size_t;
using vec::Vec;
using vec::Mat;

// Types to template test cases over
#define VALID_TYPES  float, double, long double

// Approximate (in)equality checks for vectors and matrices
#define CHECK_APPROX_EQ(a, b) CHECK(approx_eq((a), (b), kTestEpsilon))
#define CHECK_APPROX_NEQ(a, b) CHECK_FALSE(approx_eq((a), (b), kTestEpsilon))

// Maximum vector/matrix size permitted
static constexpr size_t kMaxSize = 4;

// Floating-point comparison epsilon for test assertions
static constexpr double kTestEpsilon = 1e-6;

// Test types for specifying input/output data for vectors and matrices
using TestArray = std::array<long double, kMaxSize>;
using TestGrid = std::array<TestArray, kMaxSize>;

// Helper to create vector of specified type and size from provided test array
template <typename Type, size_t M>
constexpr Vec<Type, M> get_vec(const TestArray& test_array) {

    Vec<Type, M> v;
    auto assign_elem = [](const auto& test_elem) {
        return static_cast<Type>(test_elem);
    };
    std::transform(test_array.cbegin(), test_array.cbegin() + M,
                   v.begin(), assign_elem);
    return v;
}

// Helper to create matrix of specified type and size from provided test grid
template <typename Type, size_t M>
constexpr Mat<Type, M> get_mat(const TestGrid& test_grid) {
    Mat<Type, M> m;
    auto assign_row = [](const auto& test_array) {
        return get_vec<Type, M>(test_array);
    };
    std::transform(test_grid.cbegin(), test_grid.cbegin() + M,
                   m.begin(), assign_row);
    return m;
}
