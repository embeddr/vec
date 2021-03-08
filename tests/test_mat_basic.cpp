// Unit tests for the Vec class implementation

// Testing headers
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "test_utils_mat.hpp"

// UUT headers
#include "mat.hpp"

// Note that Vec Matrices are column major. However, in the TestArray2D types below, the inner
// arrays (which each represent a column) are defined horizontally on a single line. Thus, the
// layout of the test data below is effectively the transpose of the actual matrix data.
//
// constexpr TestArray2D kTestValues{{
//     { ... },    <- Column 0
//     { ... },    <- Column 1
//     { ... },    <- Column 2
//     { ... },    <- Column 3
// }};

TEST_CASE_TEMPLATE("Construct zero matrix", Type, VALID_TYPES) {
    constexpr TestArray2D kExpected{{
        {0.0L, 0.0L, 0.0L, 0.0L},
        {0.0L, 0.0L, 0.0L, 0.0L},
        {0.0L, 0.0L, 0.0L, 0.0L},
        {0.0L, 0.0L, 0.0L, 0.0L},
    }};

    SUBCASE("2D") {
        constexpr Mat<Type, 2> m{};
        CHECK(m == getMat<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr Mat<Type, 3> m{};
        CHECK(m == getMat<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr Mat<Type, 4> m{};
        CHECK(m == getMat<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Construct matrix from column vectors", Type, VALID_TYPES) {
    constexpr TestArray2D kTestValues{{
        {1.0L, 2.0L, 3.0L, 4.0L},
        {5.0L, 6.0L, 7.0L, 8.0L},
        {-1.0L, -2.0L, -3.0L, -4.0L},
        {-5.0L, -6.0L, -7.0L, -8.0L}
    }};

    SUBCASE("2D") {
        constexpr auto v0 = getVec<Type, 2>(kTestValues[0]);
        constexpr auto v1 = getVec<Type, 2>(kTestValues[1]);
        constexpr Mat<Type, 2> m{v0, v1};
        CHECK(m == getMat<Type, 2>(kTestValues));
    }

    SUBCASE("3D") {
        constexpr auto v0 = getVec<Type, 3>(kTestValues[0]);
        constexpr auto v1 = getVec<Type, 3>(kTestValues[1]);
        constexpr auto v2 = getVec<Type, 3>(kTestValues[2]);
        constexpr Mat<Type, 3> m{v0, v1, v2};
        CHECK(m == getMat<Type, 3>(kTestValues));
    }

    SUBCASE("4D") {
        constexpr auto v0 = getVec<Type, 4>(kTestValues[0]);
        constexpr auto v1 = getVec<Type, 4>(kTestValues[1]);
        constexpr auto v2 = getVec<Type, 4>(kTestValues[2]);
        constexpr auto v3 = getVec<Type, 4>(kTestValues[3]);
        constexpr Mat<Type, 4> m{v0, v1, v2, v3};
        CHECK(m == getMat<Type, 4>(kTestValues));
    }
}

TEST_CASE_TEMPLATE("Construct matrix from other matrix", Type, VALID_TYPES) {
    constexpr TestArray2D kTestValues{{
        {1.0L, 2.0L, 3.0L, 4.0L},
        {5.0L, 6.0L, 7.0L, 8.0L},
        {-1.0L, -2.0L, -3.0L, -4.0L},
        {-5.0L, -6.0L, -7.0L, -8.0L}
    }};

    SUBCASE("2D") {
        constexpr auto m = getMat<Type, 2>(kTestValues);
        constexpr Mat<Type, 2> m_copy{m};
        CHECK(m_copy == getMat<Type, 2>(kTestValues));
    }

    SUBCASE("3D") {
        constexpr auto m = getMat<Type, 3>(kTestValues);
        constexpr Mat<Type, 3> m_copy{m};
        CHECK(m_copy == getMat<Type, 3>(kTestValues));
    }

    SUBCASE("4D") {
        constexpr auto m = getMat<Type, 4>(kTestValues);
        constexpr Mat<Type, 4> m_copy{m};
        CHECK(m_copy == getMat<Type, 4>(kTestValues));
    }
}

TEST_CASE_TEMPLATE("Construct matrix from single element fill", Type, VALID_TYPES) {
    // Shared input and expected output data:
    constexpr Type kFillValue{static_cast<Type>(123.0L)};
    constexpr TestArray2D kExpected{{
        {123.0L, 123.0L, 123.0L, 123.0L},
        {123.0L, 123.0L, 123.0L, 123.0L},
        {123.0L, 123.0L, 123.0L, 123.0L},
        {123.0L, 123.0L, 123.0L, 123.0L},
    }};

    SUBCASE("2D") {
        constexpr Mat<Type, 2> m_fill{kFillValue};
        CHECK(m_fill == getMat<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr Mat<Type, 3> m_fill{kFillValue};
        CHECK(m_fill == getMat<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr Mat<Type, 4> m_fill{kFillValue};
        CHECK(m_fill == getMat<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Construct identity matrix", Type, VALID_TYPES) {
    constexpr TestArray2D kExpected{{
        {1.0L, 0.0L, 0.0L, 0.0L},
        {0.0L, 1.0L, 0.0L, 0.0L},
        {0.0L, 0.0L, 1.0L, 0.0L},
        {0.0L, 0.0L, 0.0L, 1.0L},
    }};


    SUBCASE("2D") {
        constexpr auto m_identity = Mat<Type, 2>::identity();
        CHECK(m_identity == getMat<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto m_identity = Mat<Type, 3>::identity();
        CHECK(m_identity == getMat<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto m_identity = Mat<Type, 4>::identity();
        CHECK(m_identity == getMat<Type, 4>(kExpected));
    }
}

// TODO: Element access and column access (with and without bounds checks)

TEST_CASE_TEMPLATE("Calculate determinant", Type, VALID_TYPES) {
    constexpr TestArray2D kInput{{
        {1.0L, 2.0L, -3.5L, 0.0L},
        {5.0L, 6.6L, 7.0L, -9.0L},
        {-1.0L, -2.0L, 3.0L, -4.0L},
        {-5.0L, -6.0L, 7.0L, -8.0L},
    }};

    SUBCASE("2D") {
        constexpr Type kExpected{static_cast<Type>(-3.4L)};
        constexpr auto m = getMat<Type, 2>(kInput);
        CHECK(m.determinant() == doctest::Approx(kExpected));
    }

    SUBCASE("3D") {
        constexpr Type kExpected{static_cast<Type>(1.7L)};
        constexpr auto m = getMat<Type, 3>(kInput);
        CHECK(m.determinant() == doctest::Approx(kExpected));
    }

    SUBCASE("4D") {
        constexpr Type kExpected{static_cast<Type>(-280.8L)};
        constexpr auto m = getMat<Type, 4>(kInput);
        CHECK(m.determinant() == doctest::Approx(kExpected));
    }
}

TEST_CASE_TEMPLATE("Calculate transpose", Type, VALID_TYPES) {
    constexpr TestArray2D kInput{{
        {1.0L, 2.0L, -3.5L, 0.0L},
        {5.0L, 6.6L, 7.0L, -9.0L},
        {-1.0L, -2.0L, 3.0L, -4.0L},
        {-5.0L, -6.0L, 7.0L, -8.0L},
    }};
    constexpr TestArray2D kExpected{{
        {1.0L, 5.0L, -1.0L, -5.0L},
        {2.0L, 6.6L, -2.0L, -6.0L},
        {-3.5L, 7.0L, 3.0L, 7.0L},
        {0.0L, -9.0L, -4.0L, -8.0L},
    }};

    SUBCASE("2D") {
        constexpr auto m = getMat<Type, 2>(kInput);
        constexpr auto m_t = m.transpose();
        CHECK(m_t == getMat<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto m = getMat<Type, 3>(kInput);
        constexpr auto m_t = m.transpose();
        CHECK(m_t == getMat<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto m = getMat<Type, 4>(kInput);
        constexpr auto m_t = m.transpose();
        CHECK(m_t == getMat<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Fill", Type, VALID_TYPES) {
    constexpr Type kFillValue{static_cast<Type>(123.0L)};
    constexpr TestArray2D kExpected{{
        {123.0L, 123.0L, 123.0L, 123.0L},
        {123.0L, 123.0L, 123.0L, 123.0L},
        {123.0L, 123.0L, 123.0L, 123.0L},
        {123.0L, 123.0L, 123.0L, 123.0L},
    }};

    SUBCASE("2D") {
        Mat<Type, 2> m{};
        WARN(m != getMat<Type, 2>(kExpected));
        m.fill(kFillValue);
        CHECK(m == getMat<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        Mat<Type, 3> m{};
        WARN(m != getMat<Type, 3>(kExpected));
        m.fill(kFillValue);
        CHECK(m == getMat<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        Mat<Type, 4> m{};
        WARN(m != getMat<Type, 4>(kExpected));
        m.fill(kFillValue);
        CHECK(m == getMat<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Clear", Type, VALID_TYPES) {
    // Shared input and expected output data
    constexpr Type kFillValue{static_cast<Type>(123.0L)};
    constexpr TestArray2D kExpected{{
        {0.0L, 0.0L, 0.0L, 0.0L},
        {0.0L, 0.0L, 0.0L, 0.0L},
        {0.0L, 0.0L, 0.0L, 0.0L},
        {0.0L, 0.0L, 0.0L, 0.0L},
    }};

    SUBCASE("2D") {
        Mat<Type, 2> m{kFillValue};
        WARN(m != getMat<Type, 2>(kExpected));
        m.clear();
        CHECK(m == getMat<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        Mat<Type, 3> m{kFillValue};
        WARN(m != getMat<Type, 3>(kExpected));
        m.clear();
        CHECK(m == getMat<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        Mat<Type, 4> m{kFillValue};
        WARN(m != getMat<Type, 4>(kExpected));
        m.clear();
        CHECK(m == getMat<Type, 4>(kExpected));
    }
}
