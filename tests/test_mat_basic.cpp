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
        constexpr Mat<2, Type> m{};
        CHECK(m == getMat<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr Mat<3, Type> m{};
        CHECK(m == getMat<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr Mat<4, Type> m{};
        CHECK(m == getMat<4, Type>(kExpected));
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
        constexpr auto v0 = getVec<2, Type>(kTestValues[0]);
        constexpr auto v1 = getVec<2, Type>(kTestValues[1]);
        constexpr Mat<2, Type> m{v0, v1};
        CHECK(m == getMat<2, Type>(kTestValues));
    }

    SUBCASE("3D") {
        constexpr auto v0 = getVec<3, Type>(kTestValues[0]);
        constexpr auto v1 = getVec<3, Type>(kTestValues[1]);
        constexpr auto v2 = getVec<3, Type>(kTestValues[2]);
        constexpr Mat<3, Type> m{v0, v1, v2};
        CHECK(m == getMat<3, Type>(kTestValues));
    }

    SUBCASE("4D") {
        constexpr auto v0 = getVec<4, Type>(kTestValues[0]);
        constexpr auto v1 = getVec<4, Type>(kTestValues[1]);
        constexpr auto v2 = getVec<4, Type>(kTestValues[2]);
        constexpr auto v3 = getVec<4, Type>(kTestValues[3]);
        constexpr Mat<4, Type> m{v0, v1, v2, v3};
        CHECK(m == getMat<4, Type>(kTestValues));
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
        constexpr auto m = getMat<2, Type>(kTestValues);
        constexpr Mat<2, Type> m_copy{m};
        CHECK(m_copy == getMat<2, Type>(kTestValues));
    }

    SUBCASE("3D") {
        constexpr auto m = getMat<3, Type>(kTestValues);
        constexpr Mat<3, Type> m_copy{m};
        CHECK(m_copy == getMat<3, Type>(kTestValues));
    }

    SUBCASE("4D") {
        constexpr auto m = getMat<4, Type>(kTestValues);
        constexpr Mat<4, Type> m_copy{m};
        CHECK(m_copy == getMat<4, Type>(kTestValues));
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
        constexpr Mat<2, Type> m_fill{kFillValue};
        CHECK(m_fill == getMat<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr Mat<3, Type> m_fill{kFillValue};
        CHECK(m_fill == getMat<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr Mat<4, Type> m_fill{kFillValue};
        CHECK(m_fill == getMat<4, Type>(kExpected));
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
        constexpr auto m_identity = Mat<2, Type>::identity();
        CHECK(m_identity == getMat<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto m_identity = Mat<3, Type>::identity();
        CHECK(m_identity == getMat<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto m_identity = Mat<4, Type>::identity();
        CHECK(m_identity == getMat<4, Type>(kExpected));
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
        constexpr auto m = getMat<2, Type>(kInput);
        CHECK(m.determinant() == doctest::Approx(kExpected));
    }

    SUBCASE("3D") {
        constexpr Type kExpected{static_cast<Type>(1.7L)};
        constexpr auto m = getMat<3, Type>(kInput);
        CHECK(m.determinant() == doctest::Approx(kExpected));
    }

    SUBCASE("4D") {
        constexpr Type kExpected{static_cast<Type>(-280.8L)};
        constexpr auto m = getMat<4, Type>(kInput);
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
        constexpr auto m = getMat<2, Type>(kInput);
        constexpr auto m_t = m.transpose();
        CHECK(m_t == getMat<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto m = getMat<3, Type>(kInput);
        constexpr auto m_t = m.transpose();
        CHECK(m_t == getMat<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto m = getMat<4, Type>(kInput);
        constexpr auto m_t = m.transpose();
        CHECK(m_t == getMat<4, Type>(kExpected));
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
        Mat<2, Type> m{};
        WARN(m != getMat<2, Type>(kExpected));
        m.fill(kFillValue);
        CHECK(m == getMat<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        Mat<3, Type> m{};
        WARN(m != getMat<3, Type>(kExpected));
        m.fill(kFillValue);
        CHECK(m == getMat<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        Mat<4, Type> m{};
        WARN(m != getMat<4, Type>(kExpected));
        m.fill(kFillValue);
        CHECK(m == getMat<4, Type>(kExpected));
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
        Mat<2, Type> m{kFillValue};
        WARN(m != getMat<2, Type>(kExpected));
        m.clear();
        CHECK(m == getMat<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        Mat<3, Type> m{kFillValue};
        WARN(m != getMat<3, Type>(kExpected));
        m.clear();
        CHECK(m == getMat<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        Mat<4, Type> m{kFillValue};
        WARN(m != getMat<4, Type>(kExpected));
        m.clear();
        CHECK(m == getMat<4, Type>(kExpected));
    }
}
