// Unit tests for the Vec class implementation

// Testing headers
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "test_utils.hpp"

// UUT headers
#include "mat.hpp"

TEST_CASE_TEMPLATE("Construct zero matrix", Type, VALID_TYPES) {
    constexpr TestGrid kExpected{{
            {0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0},
    }};

    SUBCASE("2D") {
        constexpr Mat<Type, 2> m{};
        CHECK(m == get_mat<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr Mat<Type, 3> m{};
        CHECK(m == get_mat<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr Mat<Type, 4> m{};
        CHECK(m == get_mat<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Construct matrix from column vectors", Type, VALID_TYPES) {
    constexpr TestGrid kTestValues{{
            {1.0, 2.0, 3.0, 4.0},
            {5.0, 6.0, 7.0, 8.0},
            {-1.0, -2.0, -3.0, -4.0},
            {-5.0, -6.0, -7.0, -8.0}
    }};

    SUBCASE("2D") {
        constexpr auto v0 = get_vec<Type, 2>(kTestValues[0]);
        constexpr auto v1 = get_vec<Type, 2>(kTestValues[1]);
        constexpr Mat<Type, 2> m{v0, v1};
        CHECK(m == get_mat<Type, 2>(kTestValues));
    }

    SUBCASE("3D") {
        constexpr auto v0 = get_vec<Type, 3>(kTestValues[0]);
        constexpr auto v1 = get_vec<Type, 3>(kTestValues[1]);
        constexpr auto v2 = get_vec<Type, 3>(kTestValues[2]);
        constexpr Mat<Type, 3> m{v0, v1, v2};
        CHECK(m == get_mat<Type, 3>(kTestValues));
    }

    SUBCASE("4D") {
        constexpr auto v0 = get_vec<Type, 4>(kTestValues[0]);
        constexpr auto v1 = get_vec<Type, 4>(kTestValues[1]);
        constexpr auto v2 = get_vec<Type, 4>(kTestValues[2]);
        constexpr auto v3 = get_vec<Type, 4>(kTestValues[3]);
        constexpr Mat<Type, 4> m{v0, v1, v2, v3};
        CHECK(m == get_mat<Type, 4>(kTestValues));
    }
}

TEST_CASE_TEMPLATE("Construct matrix from individual elements", Type, VALID_TYPES) {
    constexpr TestGrid kTestValues{{
            {1.0, 2.0, 3.0, 4.0},
            {5.0, 6.0, 7.0, 8.0},
            {-1.0, -2.0, -3.0, -4.0},
            {-5.0, -6.0, -7.0, -8.0}
    }};

    SUBCASE("2D") {
        constexpr auto v0 = get_vec<Type, 2>(kTestValues[0]);
        constexpr auto v1 = get_vec<Type, 2>(kTestValues[1]);
        constexpr Mat<Type, 2> m{v0[0], v0[1],
                                 v1[0], v1[1]};
        CHECK(m == get_mat<Type, 2>(kTestValues));
    }

    SUBCASE("3D") {
        constexpr auto v0 = get_vec<Type, 3>(kTestValues[0]);
        constexpr auto v1 = get_vec<Type, 3>(kTestValues[1]);
        constexpr auto v2 = get_vec<Type, 3>(kTestValues[2]);
        constexpr Mat<Type, 3> m{v0[0], v0[1], v0[2],
                                 v1[0], v1[1], v1[2],
                                 v2[0], v2[1], v2[2]};
        CHECK(m == get_mat<Type, 3>(kTestValues));
    }

    SUBCASE("4D") {
        constexpr auto v0 = get_vec<Type, 4>(kTestValues[0]);
        constexpr auto v1 = get_vec<Type, 4>(kTestValues[1]);
        constexpr auto v2 = get_vec<Type, 4>(kTestValues[2]);
        constexpr auto v3 = get_vec<Type, 4>(kTestValues[3]);
        constexpr Mat<Type, 4> m{v0[0], v0[1], v0[2], v0[3],
                                 v1[0], v1[1], v1[2], v1[3],
                                 v2[0], v2[1], v2[2], v2[3],
                                 v3[0], v3[1], v3[2], v3[3]};
        CHECK(m == get_mat<Type, 4>(kTestValues));
    }
}

TEST_CASE_TEMPLATE("Construct matrix from other matrix", Type, VALID_TYPES) {
    constexpr TestGrid kTestValues{{
            {1.0, 2.0, 3.0, 4.0},
            {5.0, 6.0, 7.0, 8.0},
            {-1.0, -2.0, -3.0, -4.0},
            {-5.0, -6.0, -7.0, -8.0}
    }};

    SUBCASE("2D") {
        constexpr auto m = get_mat<Type, 2>(kTestValues);
        constexpr Mat<Type, 2> m_copy{m};
        CHECK(m_copy == get_mat<Type, 2>(kTestValues));
    }

    SUBCASE("3D") {
        constexpr auto m = get_mat<Type, 3>(kTestValues);
        constexpr Mat<Type, 3> m_copy{m};
        CHECK(m_copy == get_mat<Type, 3>(kTestValues));
    }

    SUBCASE("4D") {
        constexpr auto m = get_mat<Type, 4>(kTestValues);
        constexpr Mat<Type, 4> m_copy{m};
        CHECK(m_copy == get_mat<Type, 4>(kTestValues));
    }
}

TEST_CASE_TEMPLATE("Construct matrix from single element fill", Type, VALID_TYPES) {
    // Shared input and expected output data:
    constexpr Type kFillValue = 123.0;
    constexpr TestGrid kExpected{{
            {123.0, 123.0, 123.0, 123.0},
            {123.0, 123.0, 123.0, 123.0},
            {123.0, 123.0, 123.0, 123.0},
            {123.0, 123.0, 123.0, 123.0},
    }};

    SUBCASE("2D") {
        constexpr Mat<Type, 2> m_fill{kFillValue};
        CHECK(m_fill == get_mat<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr Mat<Type, 3> m_fill{kFillValue};
        CHECK(m_fill == get_mat<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr Mat<Type, 4> m_fill{kFillValue};
        CHECK(m_fill == get_mat<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Construct identity matrix", Type, VALID_TYPES) {
    constexpr TestGrid kExpected{{
            {1.0, 0.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 0.0, 1.0, 0.0},
            {0.0, 0.0, 0.0, 1.0},
    }};


    SUBCASE("2D") {
        constexpr auto m_identity = Mat<Type, 2>::identity();
        CHECK(m_identity == get_mat<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto m_identity = Mat<Type, 3>::identity();
        CHECK(m_identity == get_mat<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto m_identity = Mat<Type, 4>::identity();
        CHECK(m_identity == get_mat<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Size", Type, VALID_TYPES) {
    SUBCASE("2D") {
        constexpr Mat<Type, 2> m{};
        CHECK(m.size() == 2);
    }

    SUBCASE("3D") {
        constexpr Mat<Type, 3> m{};
        CHECK(m.size() == 3);
    }

    SUBCASE("4D") {
        constexpr Mat<Type, 4> m{};
        CHECK(m.size() == 4);
    }
}

TEST_CASE_TEMPLATE("Access elements by indices with at()", Type, VALID_TYPES) {
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
                CHECK(m.at(i, j) == doctest::Approx(kInput[i][j]));
                m.at(i, j) = (i + j);
                CHECK(m.at(i, j) == doctest::Approx(i + j));
            }
        }
        // Out-of-bounds
        CHECK_THROWS(m.at(1, 2));
        CHECK_THROWS(m.at(2, 1));
    }

    SUBCASE("3D") {
        auto m = get_mat<Type, 3>(kInput);
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                // Read, write, and read again
                CHECK(m.at(i, j) == doctest::Approx(kInput[i][j]));
                m.at(i, j) = (i + j);
                CHECK(m.at(i, j) == doctest::Approx(i + j));
            }
        }
        // Out-of-bounds
        CHECK_THROWS(m.at(2, 3));
        CHECK_THROWS(m.at(3, 2));
    }

    SUBCASE("4D") {
        auto m = get_mat<Type, 4>(kInput);
        for (size_t i = 0; i < 4; i++) {
            for (size_t j = 0; j < 4; j++) {
                // Read, write, and read again
                CHECK(m.at(i, j) == doctest::Approx(kInput[i][j]));
                m.at(i, j) = (i + j);
                CHECK(m.at(i, j) == doctest::Approx(i + j));
            }
        }
        // Out-of-bounds
        CHECK_THROWS(m.at(3, 4));
        CHECK_THROWS(m.at(4, 3));
    }
}

TEST_CASE_TEMPLATE("Access rows by index with at()", Type, VALID_TYPES) {
    constexpr TestGrid kInput{{
            {1.0, 2.0, -3.5, 0.0},
            {5.0, 6.6, 7.0, -9.0},
            {-1.0, -2.0, 3.0, -4.0},
            {-5.0, -6.0, 7.0, -8.0},
    }};

    SUBCASE("2D") {
        auto m = get_mat<Type, 2>(kInput);
        for (size_t i = 0; i < 2; i++) {
            const auto kExpected = get_vec<Type, 2>(kInput[i]);
            // Read, write, and read again
            CHECK(m.at(i) == kExpected);
            m.at(i).clear();
            CHECK(m.at(i) == get_vec<Type, 2>({}));
        }
        // Out-of-bounds
        CHECK_THROWS(m.at(2).clear());
    }

    SUBCASE("3D") {
        auto m = get_mat<Type, 3>(kInput);
        for (size_t i = 0; i < 3; i++) {
            const auto kExpected = get_vec<Type, 3>(kInput[i]);
            // Read, write, and read again
            CHECK(m.at(i) == kExpected);
            m.at(i).clear();
            CHECK(m.at(i) == get_vec<Type, 3>({}));
        }
        // Out-of-bounds
        CHECK_THROWS(m.at(3).clear());
    }

    SUBCASE("4D") {
        auto m = get_mat<Type, 4>(kInput);
        for (size_t i = 0; i < 4; i++) {
            const auto kExpected = get_vec<Type, 4>(kInput[i]);
            // Read, write, and read again
            CHECK(m.at(i) == kExpected);
            m.at(i).clear();
            CHECK(m.at(i) == get_vec<Type, 4>({}));
        }
        // Out-of-bounds
        CHECK_THROWS(m.at(4).clear());
    }
}

TEST_CASE_TEMPLATE("Begin/end iterator access", Type, VALID_TYPES) {
    constexpr TestGrid kInput{{
            {1.0, 2.0, -3.5, 0.0},
            {5.0, 6.6, 7.0, -9.0},
            {-1.0, -2.0, 3.0, -4.0},
            {-5.0, -6.0, 7.0, -8.0},
    }};
    constexpr Type kValue = 7;
    constexpr TestArray kExpected{7.0, 7.0, 7.0, 7.0};

    SUBCASE("2D") {
        auto m = get_mat<Type, 2>(kInput) ;
        for (auto& row : m) {
            row.fill(kValue);
        }
        std::all_of(m.cbegin(), m.cend(),
                    [kExpected](auto& row) { return (row == get_vec<Type, 2>(kExpected)); });
    }

    SUBCASE("3D") {
        auto m = get_mat<Type, 3>(kInput) ;
        for (auto& row : m) {
            row.fill(kValue);
        }
        std::all_of(m.cbegin(), m.cend(),
                    [kExpected](auto& row) { return (row == get_vec<Type, 3>(kExpected)); });
    }

    SUBCASE("4D") {
        auto m = get_mat<Type, 4>(kInput) ;
        for (auto& row : m) {
            row.fill(kValue);
        }
        std::all_of(m.cbegin(), m.cend(),
                    [kExpected](auto& row) { return (row == get_vec<Type, 4>(kExpected)); });
    }
}

TEST_CASE_TEMPLATE("Determinant", Type, VALID_TYPES) {
    constexpr TestGrid kInput{{
            {1.0, 2.0, -3.5, 0.0},
            {5.0, 6.6, 7.0, -9.0},
            {-1.0, -2.0, 3.0, -4.0},
            {-5.0, -6.0, 7.0, -8.0},
    }};

    SUBCASE("2D") {
        constexpr Type kExpected = -3.4;
        constexpr auto m = get_mat<Type, 2>(kInput);
        CHECK(m.determinant() == doctest::Approx(kExpected));
    }

    SUBCASE("3D") {
        constexpr Type kExpected = 1.7;
        constexpr auto m = get_mat<Type, 3>(kInput);
        CHECK(m.determinant() == doctest::Approx(kExpected));
    }

    SUBCASE("4D") {
        constexpr Type kExpected = -280.8;
        constexpr auto m = get_mat<Type, 4>(kInput);
        CHECK(m.determinant() == doctest::Approx(kExpected));
    }
}

TEST_CASE_TEMPLATE("Transpose", Type, VALID_TYPES) {
    constexpr TestGrid kInput{{
            {1.0, 2.0, -3.5, 0.0},
            {5.0, 6.6, 7.0, -9.0},
            {-1.0, -2.0, 3.0, -4.0},
            {-5.0, -6.0, 7.0, -8.0},
    }};
    constexpr TestGrid kExpected{{
            {1.0, 5.0, -1.0, -5.0},
            {2.0, 6.6, -2.0, -6.0},
            {-3.5, 7.0, 3.0, 7.0},
            {0.0, -9.0, -4.0, -8.0},
    }};

    SUBCASE("2D") {
        constexpr auto m = get_mat<Type, 2>(kInput);
        constexpr auto m_t = m.transpose();
        CHECK(m_t == get_mat<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto m = get_mat<Type, 3>(kInput);
        constexpr auto m_t = m.transpose();
        CHECK(m_t == get_mat<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto m = get_mat<Type, 4>(kInput);
        constexpr auto m_t = m.transpose();
        CHECK(m_t == get_mat<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Inverse", Type, VALID_TYPES) {
    constexpr TestGrid kInput{{
            {1.0, 2.0, -3.5, 0.0},
            {5.0, 6.6, 7.0, -9.0},
            {-1.0, -2.0, 3.0, -4.0},
            {-5.0, -6.0, 7.0, -8.0},
    }};

    SUBCASE("2D") {
        constexpr TestGrid kExpected{{
                {-1.94117647,  0.58823529},
                { 1.47058823, -0.29411764},
        }};
        constexpr auto m = get_mat<Type, 2>(kInput);
        constexpr auto m_inverse = m.inverse();
        CHECK(m_inverse == get_approx_mat<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr TestGrid kExpected{{
                { 19.88235294,  0.58823529,  21.82352941},
                {-12.94117647, -0.29411764, -14.41176470},
                {-2.0,          0.0,         -2.0},
        }};
        constexpr auto m = get_mat<Type, 3>(kInput);
        constexpr auto m_inverse = m.inverse();
        CHECK(m_inverse == get_approx_mat<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr TestGrid kExpected{{
            {-0.1652421, -0.07122507,  1.28133906, -0.56054132},
            { 0.1139601,  0.13532763, -1.03454418,  0.36502850},
            {-0.2678062,  0.05698005, -0.22507123,  0.04843304},
            {-0.2165242, -0.00712250, -0.22186610, -0.00605414},
        }};
        constexpr auto m = get_mat<Type, 4>(kInput);
        constexpr auto m_inverse = m.inverse();
        CHECK(m_inverse == get_approx_mat<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Fill", Type, VALID_TYPES) {
    constexpr Type kFillValue = 123.0;
    constexpr TestGrid kExpected{{
            {123.0, 123.0, 123.0, 123.0},
            {123.0, 123.0, 123.0, 123.0},
            {123.0, 123.0, 123.0, 123.0},
            {123.0, 123.0, 123.0, 123.0},
    }};

    SUBCASE("2D") {
        Mat<Type, 2> m{};
        WARN(m != get_mat<Type, 2>(kExpected));
        m.fill(kFillValue);
        CHECK(m == get_mat<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        Mat<Type, 3> m{};
        WARN(m != get_mat<Type, 3>(kExpected));
        m.fill(kFillValue);
        CHECK(m == get_mat<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        Mat<Type, 4> m{};
        WARN(m != get_mat<Type, 4>(kExpected));
        m.fill(kFillValue);
        CHECK(m == get_mat<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Clear", Type, VALID_TYPES) {
    // Shared input and expected output data
    constexpr Type kFillValue = 123.0;
    constexpr TestGrid kExpected{{
            {0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0},
    }};

    SUBCASE("2D") {
        Mat<Type, 2> m{kFillValue};
        WARN(m != get_mat<Type, 2>(kExpected));
        m.clear();
        CHECK(m == get_mat<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        Mat<Type, 3> m{kFillValue};
        WARN(m != get_mat<Type, 3>(kExpected));
        m.clear();
        CHECK(m == get_mat<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        Mat<Type, 4> m{kFillValue};
        WARN(m != get_mat<Type, 4>(kExpected));
        m.clear();
        CHECK(m == get_mat<Type, 4>(kExpected));
    }
}
