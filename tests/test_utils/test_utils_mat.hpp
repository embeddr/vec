// Utilities for matrix unit tests

#pragma once

#include <array>

// Testing headers
#include "doctest.h"
#include "test_utils_vec.hpp"

// UUT headers
#include "mat.hpp"

using vec::Mat;

// Two-dimensional test array type for specifying input/output data
using TestArray2D = std::array<std::array<long double, kMaxSize>, kMaxSize>;

// Helper to create matrix of specified type and size from provided 2D input array
template <typename Type, size_t M>
constexpr Mat<Type, M> getMat(TestArray2D elems) {
    Mat<Type, M> m;
    for (size_t i = 0; i < M; i++) {
        for (size_t j = 0; j < M; j++) {
            m(i, j) = static_cast<Type>(elems[i][j]);
        }
    }
    return m;
}

TEST_CASE("Basic checks to enable other tests") {
    SUBCASE("Element access with ()") {
        // Helper getMat() above requires operator() to set values
        constexpr float kScale = 3.0F; // arbitrary
        Mat<float, kMaxSize> m{{3.0F, 2.0F, 1.0F, 0.0F},
                               {4.0F, 3.0F, 2.0F, 1.0F},
                               {5.0F, 4.0F, 3.0F, 2.0F},
                               {6.0F, 5.0F, 4.0F, 3.0F}};
        for (size_t i = 0; i < kMaxSize; i++) {
            for (size_t j = 0; j < kMaxSize; j++) {
                CHECK(m(i, j) == doctest::Approx(3.0f + i - j));
                m(i, j) *= kScale;
                CHECK(m(i, j) == doctest::Approx((3.0f + i - j) * kScale));
            }
        }
    }

    SUBCASE("Floating-point matrix (in)equality") {
        Mat<float, kMaxSize> m1{{1.0F, 2.0F, 3.0F, 4.0F},
                                {5.0F, 6.0F, 7.0F, 8.0F},
                                {-1.0F, -2.0F, -3.0F, -4.0F},
                                {-5.0F, -6.0F, -7.0F, -8.0F}};
        Mat<float, kMaxSize> m2{{1.0F, 2.0F, 3.0F, 4.0F},
                                {5.0F, 6.0F, 7.0F, 8.0F},
                                {-1.0F, -2.0F, -3.0F, -4.0F},
                                {-5.0F, -6.0F, -7.0F, -8.0F}};
        constexpr float kDelta = 0.001F;
        CHECK(m1 == m2);
        CHECK_FALSE(m1 != m2);

        for (size_t i = 0; i < kMaxSize; i++) {
            for (size_t j = 0; j < kMaxSize; j++) {
                Mat<float, kMaxSize> m2_mod = m2;
                m2_mod(i, j) += kDelta;
                CHECK(m1 != m2_mod);
                CHECK_FALSE(m1 == m2_mod);
            }
        }
    }

    SUBCASE("Helper getMat()") {
        constexpr TestArray2D kTestValues{{
           {1.0L, 2.0L, 3.0L, 4.0L},
           {5.0L, 6.0L, 7.0L, 8.0L},
           {-1.0L, -2.0L, -3.0L, -4.0L},
           {-5.0L, -6.0L, -7.0L, -8.0L}
        }};
        constexpr auto m = getMat<float, kMaxSize>(kTestValues);
        for (size_t i = 0; i < kMaxSize; i++) {
            for (size_t j = 0; j < kMaxSize; j++) {
                CHECK(m(i, j) == doctest::Approx(kTestValues[i][j]));
            }
        }
    }
}
