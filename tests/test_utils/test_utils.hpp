// Utilities for Vec unit tests

#pragma once

#include <algorithm>
#include <array>
#include <cmath>

#include "vec.hpp"
#include "mat.hpp"

using std::size_t;
using vec::Vec;
using vec::Mat;

// Types to template test cases over
#define VALID_TYPES  float, double, long double

// Maximum vector/matrix size permitted
static constexpr size_t kMaxSize = 4;

// Floating-point comparison epsilon for test assertions
static constexpr long double kTestEpsilon = 1e-6L;

// Test types for specifying input/output data for vectors and matrices
using TestArray = std::array<long double, kMaxSize>;
using TestGrid = std::array<TestArray, kMaxSize>;

// Vector/matrix approximate comparison helper class (akin to doctest::Approx)
// Enables approximate comparison with operator== and display of each side on failed assertions
// TODO: use a concept to restrict Type in a more explicit fashion
template <typename Type>
class Approx {
public:
    constexpr explicit Approx(Type data)
            : data_(data), epsilon_(kTestEpsilon) {}

    // Set new epsilon for comparisons
    void epsilon(long double eps_new) {
        epsilon_ = eps_new;
    }

    friend constexpr bool operator==(const Type& lhs, const Approx& rhs) {
        return approx_eq(lhs, rhs.data_, rhs.epsilon_);
    }

    friend constexpr bool operator==(const Approx& lhs, const Type& rhs) {
        return approx_eq(lhs.data_, rhs, lhs.epsilon_);
    }

    friend constexpr bool operator==(const Approx& lhs, const Approx& rhs) {
        return approx_eq(lhs.data_, rhs.data_, std::min(lhs.epsilon_, rhs.epsilon_));
    }

    friend std::ostream& operator<<(std::ostream& os, const Approx& rhs) {
       os << rhs.data_;
       return os;
    }

private:
    Type data_;
    long double epsilon_;
};

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

// Helper to create approximate wrapper of test vector for equality checks
template <typename Type, size_t M>
constexpr Approx<Vec<Type, M>> get_approx_vec(const TestArray& test_array) {
    return Approx(get_vec<Type, M>(test_array));
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

// Helper to create approximate wrapper of test matrix for equality checks
template <typename Type, size_t M>
constexpr Approx<Mat<Type, M>> get_approx_mat(const TestGrid& test_grid) {
    return Approx(get_mat<Type, M>(test_grid));
}
