// Unit tests for the Mat class implementation (operators)

// Testing headers
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "test_utils.hpp"

// UUT headers
#include "mat.hpp"

TEST_CASE_TEMPLATE("Access rows by index with []", Type, VALID_TYPES) {
    constexpr TestGrid kInput{{
            {1.0, 2.0, -3.5, 0.0},
            {5.0, 6.6, 7.0, -9.0},
            {-1.0, -2.0, 3.0, -4.0},
            {-5.0, -6.0, 7.0, -8.0},
    }};

    SUBCASE("2D") {
        auto m = get_mat<Type, 2>(kInput);
        for (size_t i = 0; i < 2; i++) {
            // Read, write, and read again
            CHECK(m[i] == get_approx_vec<Type, 2>(kInput[i]));
            m[i].clear();
            CHECK(m[i] == get_approx_vec<Type, 2>({}));
        }
    }

    SUBCASE("3D") {
        auto m = get_mat<Type, 3>(kInput);
        for (size_t i = 0; i < 3; i++) {
            // Read, write, and read again
            CHECK(m[i] == get_approx_vec<Type, 3>(kInput[i]));
            m[i].clear();
            CHECK(m[i] == get_approx_vec<Type, 3>({}));
        }
    }

    SUBCASE("4D") {
        auto m = get_mat<Type, 4>(kInput);
        for (size_t i = 0; i < 4; i++) {
            // Read, write, and read again
            CHECK(m[i] == get_approx_vec<Type, 4>(kInput[i]));
            m[i].clear();
            CHECK(m[i] == get_approx_vec<Type, 4>({}));
        }
    }
}

TEST_CASE_TEMPLATE("Access elements by indices with ()", Type, VALID_TYPES) {
    constexpr TestGrid kInput{{
            {1.0, 2.0, -3.5, 0.0},
            {5.0, 6.6, 7.0, -9.0},
            {-1.0, -2.0, 3.0, -4.0},
            {-5.0, -6.0, 7.0, -8.0},
    }};

    SUBCASE("2D") {
        auto m = get_mat<Type, 2>(kInput);
        for (size_t i = 0; i < 2; i++) {
            for (size_t j = 0; j < 2; j++) {
                // Read, write, and read again
                CHECK(m(i, j) == doctest::Approx(kInput[i][j]));
                m(i, j) = (i + j);
                CHECK(m(i, j) == doctest::Approx(i + j));
            }
        }
    }

    SUBCASE("3D") {
        auto m = get_mat<Type, 3>(kInput);
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                // Read, write, and read again
                CHECK(m(i, j) == doctest::Approx(kInput[i][j]));
                m(i, j) = (i + j);
                CHECK(m(i, j) == doctest::Approx(i + j));
            }
        }
    }

    SUBCASE("4D") {
        auto m = get_mat<Type, 4>(kInput);
        for (size_t i = 0; i < 4; i++) {
            for (size_t j = 0; j < 4; j++) {
                // Read, write, and read again
                CHECK(m(i, j) == doctest::Approx(kInput[i][j]));
                m(i, j) = (i + j);
                CHECK(m(i, j) == doctest::Approx(i + j));
            }
        }
    }
}

TEST_CASE_TEMPLATE("Matrix += matrix", Type, VALID_TYPES) {
    constexpr TestGrid kInput1{{
            {1.0, 2.0, -3.5, 0.0},
            {5.0, 6.6, 7.0, -9.0},
            {-1.0, -2.0, 3.0, -4.0},
            {-5.0, -6.0, 7.0, -8.0},
    }};
    constexpr TestGrid kInput2{{
            {1.0, 1.0, -2.0, -2.0},
            {3.6, 3.6, 4.0, 4.0},
            {-1.0, -1.0, -4.0, -4.0},
            {-5.5, -5.5, 7.0, 7.0},
    }};
    constexpr TestGrid kExpected{{
            {2.0, 3.0, -5.5, -2.0},
            {8.6, 10.2, 11.0, -5.0},
            {-2.0, -3.0, -1.0, -8.0},
            {-10.5, -11.5, 14.0, -1.0},
    }};

    SUBCASE("2D") {
        auto m1 = get_mat<Type, 2>(kInput1);
        constexpr auto m2 = get_mat<Type, 2>(kInput2);
        m1 += m2;
        CHECK(m1 == get_approx_mat<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        auto m1 = get_mat<Type, 3>(kInput1);
        constexpr auto m2 = get_mat<Type, 3>(kInput2);
        m1 += m2;
        CHECK(m1 == get_approx_mat<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        auto m1 = get_mat<Type, 4>(kInput1);
        constexpr auto m2 = get_mat<Type, 4>(kInput2);
        m1 += m2;
        CHECK(m1 == get_approx_mat<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Matrix -= matrix", Type, VALID_TYPES) {
    constexpr TestGrid kInput1{{
            {1.0, 2.0, -3.5, 0.0},
            {5.0, 6.6, 7.0, -9.0},
            {-1.0, -2.0, 3.0, -4.0},
            {-5.0, -6.0, 7.0, -8.0},
    }};
    constexpr TestGrid kInput2{{
            {1.0, 1.0, -2.0, -2.0},
            {3.6, 3.6, 4.0, 4.0},
            {-1.0, -1.0, -4.0, -4.0},
            {-5.5, -5.5, 7.0, 7.0},
    }};
    constexpr TestGrid kExpected{{
            {0.0, 1.0, -1.5, 2.0},
            {1.4, 3.0, 3.0, -13.0},
            {0.0, -1.0, 7.0, 0.0},
            {0.5, -0.5, 0.0, -15.0},
    }};

    SUBCASE("2D") {
        auto m1 = get_mat<Type, 2>(kInput1);
        constexpr auto m2 = get_mat<Type, 2>(kInput2);
        m1 -= m2;
        CHECK(m1 == get_approx_mat<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        auto m1 = get_mat<Type, 3>(kInput1);
        constexpr auto m2 = get_mat<Type, 3>(kInput2);
        m1 -= m2;
        CHECK(m1 == get_approx_mat<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        auto m1 = get_mat<Type, 4>(kInput1);
        constexpr auto m2 = get_mat<Type, 4>(kInput2);
        m1 -= m2;
        CHECK(m1 == get_approx_mat<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Matrix *= scalar", Type, VALID_TYPES) {
    constexpr TestGrid kInput{{
            {1.0, 2.0, -3.5, 0.0},
            {5.0, 6.6, 7.0, -9.0},
            {-1.0, -2.0, 3.0, -4.0},
            {-5.0, -6.0, 7.0, -8.0},
    }};
    constexpr Type kScalar = static_cast<Type>(12.3);
    constexpr TestGrid kExpected{{
            {12.3, 24.6, -43.05, 0.0},
            {61.5, 81.18, 86.1, -110.7},
            {-12.3, -24.6, 36.9, -49.2},
            {-61.5, -73.8, 86.1, -98.4},
    }};

    SUBCASE("2D") {
        auto m = get_mat<Type, 2>(kInput);
        m *= kScalar;
        CHECK(m == get_approx_mat<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        auto m = get_mat<Type, 3>(kInput);
        m *= kScalar;
        CHECK(m == get_approx_mat<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        auto m = get_mat<Type, 4>(kInput);
        m *= kScalar;
        CHECK(m == get_approx_mat<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Matrix *= matrix", Type, VALID_TYPES) {
    constexpr TestGrid kInput1{{
            {1.0, 2.0, -3.5, 0.0},
            {5.0, 6.6, 7.0, -9.0},
            {-1.0, -2.0, 3.0, -4.0},
            {-5.0, -6.0, 7.0, -8.0},
    }};
    constexpr TestGrid kInput2{{
            {1.0, 1.0, -2.0, -2.0},
            {3.6, 3.6, 4.0, 4.0},
            {-1.0, -1.0, -4.0, -4.0},
            {-5.5, -5.5, 7.0, 7.0},
    }};


    SUBCASE("2D") {
        constexpr TestGrid kExpected{{
                {8.2, 8.2},
                {28.76, 28.76},
        }};

        auto m1 = get_mat<Type, 2>(kInput1);
        constexpr auto m2 = get_mat<Type, 2>(kInput2);
        m1 *= m2;
        CHECK(m1 == Approx(get_mat<Type, 2>(kExpected)));
    }

    SUBCASE("3D") {
        constexpr TestGrid kExpected{{
                {11.7, 11.7, 20.0},
                {21.76, 21.76, -11.6},
                {-11.2, -11.2, -18.0},
        }};

        auto m1 = get_mat<Type, 3>(kInput1);
        constexpr auto m2 = get_mat<Type, 3>(kInput2);
        m1 *= m2;
        CHECK(m1 == Approx(get_mat<Type, 3>(kExpected)));
    }

    SUBCASE("4D") {
        constexpr TestGrid kExpected{{
                {11.7, 11.7, 20.0, 20.0},
                {71.26, 71.26, -74.6, -74.6},
                {10.8, 10.8, -46.0, -46.0},
                {10.4, 10.4, -98.0, -98.0},
        }};

        auto m1 = get_mat<Type, 4>(kInput1);
        constexpr auto m2 = get_mat<Type, 4>(kInput2);
        m1 *= m2;
        CHECK(m1 == Approx(get_mat<Type, 4>(kExpected)));
    }
}

TEST_CASE_TEMPLATE("Matrix /= scalar", Type, VALID_TYPES) {
    constexpr TestGrid kInput{{
            {1.0, 2.0, -3.5, 0.0},
            {5.0, 6.6, 7.0, -9.0},
            {-1.0, -2.0, 3.0, -4.0},
            {-5.0, -6.0, 7.0, -8.0},
    }};
    constexpr Type kScalar = static_cast<Type>(2.5);
    constexpr TestGrid kExpected{{
            {0.4, 0.8, -1.4, 0.0},
            {2.0, 2.64, 2.8, -3.6},
            {-0.4, -0.8, 1.2, -1.6},
            {-2.0, -2.4, 2.8, -3.2},
    }};

    SUBCASE("2D") {
        auto m = get_mat<Type, 2>(kInput);
        m /= kScalar;
        CHECK(m == Approx(get_mat<Type, 2>(kExpected)));
    }

    SUBCASE("3D") {
        auto m = get_mat<Type, 3>(kInput);
        m /= kScalar;
        CHECK(m == Approx(get_mat<Type, 3>(kExpected)));
    }

    SUBCASE("4D") {
        auto m = get_mat<Type, 4>(kInput);
        m /= kScalar;
        CHECK(m == Approx(get_mat<Type, 4>(kExpected)));
    }
}

TEST_CASE_TEMPLATE("Negate (-matrix)", Type, VALID_TYPES) {
    constexpr TestGrid kInput{{
            {1.0, 2.0, -3.5, 0.0},
            {5.0, 6.6, 7.0, -9.0},
            {-1.0, -2.0, 3.0, -4.0},
            {-5.0, -6.0, 7.0, -8.0},
    }};
    constexpr TestGrid kExpected{{
            {-1.0, -2.0, 3.5, 0.0},
            {-5.0, -6.6, -7.0, 9.0},
            {1.0, 2.0, -3.0, 4.0},
            {5.0, 6.0, -7.0, 8.0},
    }};

    SUBCASE("2D") {
        constexpr auto m = get_mat<Type, 2>(kInput);
        constexpr auto m_neg = -m;
        CHECK(m_neg == get_approx_mat<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto m = get_mat<Type, 3>(kInput);
        constexpr auto m_neg = -m;
        CHECK(m_neg == get_approx_mat<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto m = get_mat<Type, 4>(kInput);
        constexpr auto m_neg = -m;
        CHECK(m_neg == get_approx_mat<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Matrix ==/!= matrix", Type, VALID_TYPES) {
    constexpr TestGrid kInput{{
            {1.0, 2.0, -3.5, 0.0},
            {5.0, 6.6, 7.0, -9.0},
            {-1.0, -2.0, 3.0, -4.0},
            {-5.0, -6.0, 7.0, -8.0},
    }};

    SUBCASE("2D") {
        // Check equality case
        constexpr auto m1 = get_mat<Type, 2>(kInput);
        constexpr auto m2 = get_mat<Type, 2>(kInput);
        CHECK(m1 == m2);
        CHECK_FALSE(m1 != m2);

        // Check inequality cases
        for (size_t i = 0; i < 2; i++) {
            for (size_t j = 0; j < 2; j++) {
                Mat<Type, 2> m2_modified = m2;
                m2_modified(i, j) += 0.001L;
                CHECK_FALSE(m1 == m2_modified);
                CHECK(m1 != m2_modified);
            }
        }
    }

    SUBCASE("3D") {
        // Check equality case
        constexpr auto m1 = get_mat<Type, 3>(kInput);
        constexpr auto m2 = get_mat<Type, 3>(kInput);
        CHECK(m1 == m2);
        CHECK_FALSE(m1 != m2);

        // Check inequality cases
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                Mat<Type, 3> m2_modified = m2;
                m2_modified(i, j) += 0.001L;
                CHECK_FALSE(m1 == m2_modified);
                CHECK(m1 != m2_modified);
            }
        }
    }

    SUBCASE("4D") {
        // Check equality case
        constexpr auto m1 = get_mat<Type, 4>(kInput);
        constexpr auto m2 = get_mat<Type, 4>(kInput);
        CHECK(m1 == m2);
        CHECK_FALSE(m1 != m2);

        // Check inequality cases
        for (size_t i = 0; i < 4; i++) {
            for (size_t j = 0; j < 4; j++) {
                Mat<Type, 4> m2_modified = m2;
                m2_modified(i, j) += 0.001L;
                CHECK_FALSE(m1 == m2_modified);
                CHECK(m1 != m2_modified);
            }
        }
    }
}

TEST_CASE_TEMPLATE("Matrix + matrix", Type, VALID_TYPES) {
    constexpr TestGrid kInput1{{
            {1.0, 2.0, -3.5, 0.0},
            {5.0, 6.6, 7.0, -9.0},
            {-1.0, -2.0, 3.0, -4.0},
            {-5.0, -6.0, 7.0, -8.0},
    }};
    constexpr TestGrid kInput2{{
            {1.0, 1.0, -2.0, -2.0},
            {3.6, 3.6, 4.0, 4.0},
            {-1.0, -1.0, -4.0, -4.0},
            {-5.5, -5.5, 7.0, 7.0},
    }};
    constexpr TestGrid kExpected{{
            {2.0, 3.0, -5.5, -2.0},
            {8.6, 10.2, 11.0, -5.0},
            {-2.0, -3.0, -1.0, -8.0},
            {-10.5, -11.5, 14.0, -1.0},
    }};

    SUBCASE("2D") {
        constexpr auto m1 = get_mat<Type, 2>(kInput1);
        constexpr auto m2 = get_mat<Type, 2>(kInput2);
        constexpr Mat<Type, 2> m_sum = m1 + m2;
        CHECK(m_sum == get_approx_mat<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto m1 = get_mat<Type, 3>(kInput1);
        constexpr auto m2 = get_mat<Type, 3>(kInput2);
        constexpr Mat<Type, 3> m_sum = m1 + m2;
        CHECK(m_sum == get_approx_mat<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto m1 = get_mat<Type, 4>(kInput1);
        constexpr auto m2 = get_mat<Type, 4>(kInput2);
        constexpr Mat<Type, 4> m_sum = m1 + m2;
        CHECK(m_sum == get_approx_mat<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Matrix - matrix", Type, VALID_TYPES) {
    constexpr TestGrid kInput1{{
            {1.0, 2.0, -3.5, 0.0},
            {5.0, 6.6, 7.0, -9.0},
            {-1.0, -2.0, 3.0, -4.0},
            {-5.0, -6.0, 7.0, -8.0},
    }};
    constexpr TestGrid kInput2{{
            {1.0, 1.0, -2.0, -2.0},
            {3.6, 3.6, 4.0, 4.0},
            {-1.0, -1.0, -4.0, -4.0},
            {-5.5, -5.5, 7.0, 7.0},
    }};
    constexpr TestGrid kExpected{{
            {0.0, 1.0, -1.5, 2.0},
            {1.4, 3.0, 3.0, -13.0},
            {0.0, -1.0, 7.0, 0.0},
            {0.5, -0.5, 0.0, -15.0},
    }};

    SUBCASE("2D") {
        constexpr auto m1 = get_mat<Type, 2>(kInput1);
        constexpr auto m2 = get_mat<Type, 2>(kInput2);
        constexpr Mat<Type, 2> m_diff = m1 - m2;
        CHECK(m_diff == get_approx_mat<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto m1 = get_mat<Type, 3>(kInput1);
        constexpr auto m2 = get_mat<Type, 3>(kInput2);
        constexpr Mat<Type, 3> m_diff = m1 - m2;
        CHECK(m_diff == get_approx_mat<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto m1 = get_mat<Type, 4>(kInput1);
        constexpr auto m2 = get_mat<Type, 4>(kInput2);
        constexpr Mat<Type, 4> m_diff = m1 - m2;
        CHECK(m_diff == get_approx_mat<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Matrix * scalar", Type, VALID_TYPES) {
    constexpr TestGrid kInput{{
            {1.0, 2.0, -3.5, 0.0},
            {5.0, 6.6, 7.0, -9.0},
            {-1.0, -2.0, 3.0, -4.0},
            {-5.0, -6.0, 7.0, -8.0},
    }};
    constexpr Type kScalar = static_cast<Type>(12.3);
    constexpr TestGrid kExpected{{
            {12.3, 24.6, -43.05, 0.0},
            {61.5, 81.18, 86.1, -110.7},
            {-12.3, -24.6, 36.9, -49.2},
            {-61.5, -73.8, 86.1, -98.4},
    }};

    SUBCASE("2D") {
        constexpr auto m = get_mat<Type, 2>(kInput);
        constexpr Mat<Type, 2> m_mul = m * kScalar;
        constexpr Mat<Type, 2> m_mul_reverse = kScalar * m;
        CHECK(m_mul == get_approx_mat<Type, 2>(kExpected));
        CHECK(m_mul_reverse == Approx(get_mat<Type, 2>(kExpected)));
    }

    SUBCASE("3D") {
        constexpr auto m = get_mat<Type, 3>(kInput);
        constexpr Mat<Type, 3> m_mul = m * kScalar;
        constexpr Mat<Type, 3> m_mul_reverse = kScalar * m;
        CHECK(m_mul == get_approx_mat<Type, 3>(kExpected));
        CHECK(m_mul_reverse == Approx(get_mat<Type, 3>(kExpected)));
    }

    SUBCASE("4D") {
        constexpr auto m = get_mat<Type, 4>(kInput);
        constexpr Mat<Type, 4> m_mul = m * kScalar;
        constexpr Mat<Type, 4> m_mul_reverse = kScalar * m;
        CHECK(m_mul == get_approx_mat<Type, 4>(kExpected));
        CHECK(m_mul_reverse == Approx(get_mat<Type, 4>(kExpected)));
    }
}

TEST_CASE_TEMPLATE("Vector * matrix", Type, VALID_TYPES) {
    constexpr TestArray kInput1{1.0, 2.0, 3.0, 4.0};
    constexpr TestGrid kInput2{{
            {1.0, 2.0, -3.5, 0.0},
            {5.0, 6.6, 7.0, -9.0},
            {-1.0, -2.0, 3.0, -4.0},
            {-5.0, -6.0, 7.0, -8.0},
    }};

    SUBCASE("2D") {
        constexpr TestArray kExpected{11.0, 15.2};
        constexpr auto v = get_vec<Type, 2>(kInput1);
        constexpr auto m = get_mat<Type, 2>(kInput2);
        constexpr Vec<Type, 2> v_out = v * m;
        CHECK(v_out == get_approx_vec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr TestArray kExpected{8.0, 9.2, 19.5};
        constexpr auto v = get_vec<Type, 3>(kInput1);
        constexpr auto m = get_mat<Type, 3>(kInput2);
        constexpr Vec<Type, 3> v_out = v * m;
        CHECK(v_out == get_approx_vec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr TestArray kExpected{-12.0, -14.8, 47.5, -62};
        constexpr auto v = get_vec<Type, 4>(kInput1);
        constexpr auto m = get_mat<Type, 4>(kInput2);
        constexpr Vec<Type, 4> v_out = v * m;
        CHECK(v_out == get_approx_vec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Matrix * matrix", Type, VALID_TYPES) {
    constexpr TestGrid kInput1{{
            {1.0, 2.0, -3.5, 0.0},
            {5.0, 6.6, 7.0, -9.0},
            {-1.0, -2.0, 3.0, -4.0},
            {-5.0, -6.0, 7.0, -8.0},
    }};
    constexpr TestGrid kInput2{{
            {1.0, 1.0, -2.0, -2.0},
            {3.6, 3.6, 4.0, 4.0},
            {-1.0, -1.0, -4.0, -4.0},
            {-5.5, -5.5, 7.0, 7.0},
    }};


    SUBCASE("2D") {
        constexpr TestGrid kExpected{{
                {8.2, 8.2},
                {28.76, 28.76},
        }};

        constexpr auto m1 = get_mat<Type, 2>(kInput1);
        constexpr auto m2 = get_mat<Type, 2>(kInput2);
        constexpr Mat<Type, 2> m_prod = m1 * m2;
        CHECK(m_prod == Approx(get_mat<Type, 2>(kExpected)));
    }

    SUBCASE("3D") {
        constexpr TestGrid kExpected{{
                {11.7, 11.7, 20.0},
                {21.76, 21.76, -11.6},
                {-11.2, -11.2, -18.0},
        }};

        constexpr auto m1 = get_mat<Type, 3>(kInput1);
        constexpr auto m2 = get_mat<Type, 3>(kInput2);
        constexpr Mat<Type, 3> m_prod = m1 * m2;
        CHECK(m_prod == Approx(get_mat<Type, 3>(kExpected)));
    }

    SUBCASE("4D") {
        constexpr TestGrid kExpected{{
                {11.7, 11.7, 20.0, 20.0},
                {71.26, 71.26, -74.6, -74.6},
                {10.8, 10.8, -46.0, -46.0},
                {10.4, 10.4, -98.0, -98.0},
        }};

        constexpr auto m1 = get_mat<Type, 4>(kInput1);
        constexpr auto m2 = get_mat<Type, 4>(kInput2);
        constexpr Mat<Type, 4> m_prod = m1 * m2;
        CHECK(m_prod == Approx(get_mat<Type, 4>(kExpected)));
    }
}

TEST_CASE_TEMPLATE("Matrix / scalar", Type, VALID_TYPES) {
    constexpr TestGrid kInput{{
            {1.0, 2.0, -3.5, 0.0},
            {5.0, 6.6, 7.0, -9.0},
            {-1.0, -2.0, 3.0, -4.0},
            {-5.0, -6.0, 7.0, -8.0},
    }};
    constexpr Type kScalar = static_cast<Type>(2.5);
    constexpr TestGrid kExpected{{
            {0.4, 0.8, -1.4, 0.0},
            {2.0, 2.64, 2.8, -3.6},
            {-0.4, -0.8, 1.2, -1.6},
            {-2.0, -2.4, 2.8, -3.2},
    }};

    SUBCASE("2D") {
        constexpr auto m = get_mat<Type, 2>(kInput);
        constexpr Mat<Type, 2> m_div = m / kScalar;
        CHECK(m_div == Approx(get_mat<Type, 2>(kExpected)));
    }

    SUBCASE("3D") {
        constexpr auto m = get_mat<Type, 3>(kInput);
        constexpr Mat<Type, 3> m_div = m / kScalar;
        CHECK(m_div == Approx(get_mat<Type, 3>(kExpected)));
    }

    SUBCASE("4D") {
        constexpr auto m = get_mat<Type, 4>(kInput);
        constexpr Mat<Type, 4> m_div = m / kScalar;
        CHECK(m_div == Approx(get_mat<Type, 4>(kExpected)));
    }
}

TEST_CASE_TEMPLATE("Ostream operator", Type, VALID_TYPES) {
    constexpr TestGrid kInput{{
            {1.0, 2.001, -3.5, 0.0},
            {5.0, 6.6, 7.0, -9.0},
            {-1.0, -2.0, 3.0, -4.0},
            {-5.0, -6.0, 7.0, -8.0},
    }};

    // Configure output resolution
    std::stringstream out;
    out << std::fixed << std::setprecision(3);

    SUBCASE("2D") {
        const std::string kExpected{"\n[[  1.000  2.001  ]"
                                    "\n [  5.000  6.600  ]]"};
        constexpr auto v = get_mat<Type, 2>(kInput);
        out << v;
        CHECK(out.str() == kExpected);
    }

    SUBCASE("3D") {
        const std::string kExpected{"\n[[  1.000  2.001  -3.500  ]"
                                    "\n [  5.000  6.600  7.000  ]"
                                    "\n [  -1.000  -2.000  3.000  ]]"};
    constexpr auto v = get_mat<Type, 3>(kInput);
        out << v;
        CHECK(out.str() == kExpected);
    }

    SUBCASE("4D") {
        const std::string kExpected{"\n[[  1.000  2.001  -3.500  0.000  ]"
                                    "\n [  5.000  6.600  7.000  -9.000  ]"
                                    "\n [  -1.000  -2.000  3.000  -4.000  ]"
                                    "\n [  -5.000  -6.000  7.000  -8.000  ]]"};
    constexpr auto v = get_mat<Type, 4>(kInput);
        out << v;
        CHECK(out.str() == kExpected);
    }
}
