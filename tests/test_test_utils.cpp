// Unit tests for test utilities that enable other tests

// Testing headers
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

// UUT headers
#include "test_utils.hpp"

TEST_CASE("Basic vector/helper tests to enable more comprehensive vector tests") {
    SUBCASE("Element access with []") {
        constexpr float kScale = 123.0F; // arbitrary
        Vec<float, kMaxSize> v{0.0F, 1.0F, 2.0F, 3.0F};
        for (size_t i = 0; i < kMaxSize; i++) {
            // Read, write, read again
            CHECK(v[i] == doctest::Approx(i));
            v[i] *= kScale;
            CHECK(v[i] == doctest::Approx(i * kScale));
        }
    }

    SUBCASE("Helper get_vec()") {
        constexpr TestArray kInit{1.5, -2.1, 3.3, 4.0};
        constexpr auto v = get_vec<float, kMaxSize>(kInit);
        for (size_t i = 0; i < kMaxSize; i++) {
            CHECK(v[i] == doctest::Approx(kInit[i]));
        }
    }

    SUBCASE("Floating-point vector (in)equality") {
        constexpr Vec<float, kMaxSize> v1{5.1F, -6.024F, 0.0F, 8.99F};
        constexpr Vec<float, kMaxSize> v2{5.1F, -6.024F, 0.0F, 8.99F};
        constexpr float kDelta = 0.001F;
        CHECK(v1 == Approx(v2));

        for (size_t i = 0; i < kMaxSize; i++) {
            Vec<float, kMaxSize> v2_mod = v2;
            v2_mod[i] += kDelta;
            CHECK(v1 != Approx(v2_mod));
        }
    }
}

TEST_CASE("Basic matrix/helper checks to enable more comprehensive matrix tests") {
    SUBCASE("Element access with ()") {
        constexpr float kScale = 123.0F; // arbitrary
        Mat<float, kMaxSize> m{{3.0F, 2.0F, 1.0F, 0.0F},
                               {4.0F, 3.0F, 2.0F, 1.0F},
                               {5.0F, 4.0F, 3.0F, 2.0F},
                               {6.0F, 5.0F, 4.0F, 3.0F}};
        for (size_t i = 0; i < kMaxSize; i++) {
            for (size_t j = 0; j < kMaxSize; j++) {
                CHECK(m(i, j) == doctest::Approx(3.0F + i - j));
                m(i, j) *= kScale;
                CHECK(m(i, j) == doctest::Approx((3.0F + i - j) * kScale));
            }
        }
    }

    SUBCASE("Helper get_mat()") {
        constexpr TestGrid kTestValues{{
                {1.0, 2.0, 3.0, 4.0},
                {5.0, 6.0, 7.0, 8.0},
                {-1.0, -2.0, -3.0, -4.0},
                {-5.0, -6.0, -7.0, -8.0}
        }};
        constexpr auto m = get_mat<float, kMaxSize>(kTestValues);
        for (size_t i = 0; i < kMaxSize; i++) {
            for (size_t j = 0; j < kMaxSize; j++) {
                CHECK(m(i, j) == doctest::Approx(kTestValues[i][j]));
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
        CHECK(m1 == Approx(m2));

        for (size_t i = 0; i < kMaxSize; i++) {
            for (size_t j = 0; j < kMaxSize; j++) {
                Mat<float, kMaxSize> m2_mod = m2;
                m2_mod(i, j) += kDelta;
                CHECK(m1 != Approx(m2_mod));
            }
        }
    }
}
