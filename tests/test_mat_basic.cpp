// Unit tests for the Vec class implementation

// Testing headers
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "test_utils_mat.hpp"

// UUT headers
#include "mat.hpp"

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

TEST_CASE_TEMPLATE("Construct matrix from individual elements", Type, VALID_TYPES) {
    // TODO
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
    constexpr TestArray2D kInput{{
                                         {1.0L, 2.0L, -3.5L, 0.0L},
                                         {5.0L, 6.6L, 7.0L, -9.0L},
                                         {-1.0L, -2.0L, 3.0L, -4.0L},
                                         {-5.0L, -6.0L, 7.0L, -8.0L},
                                 }};

    SUBCASE("2D") {
        auto m = getMat<Type, 2>(kInput);
        for (size_t i = 0; i < 2; i++) {
            for (size_t j = 0; j < 2; j++) {
                // Read, write, and read again
                CHECK(m.at(i, j) == doctest::Approx(kInput[i][j]));
                m.at(i, j) = (i + j);
                CHECK(m.at(i, j) == doctest::Approx(i + j));
            }
        }
    }

    SUBCASE("3D") {
        auto m = getMat<Type, 3>(kInput);
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                // Read, write, and read again
                CHECK(m.at(i, j) == doctest::Approx(kInput[i][j]));
                m.at(i, j) = (i + j);
                CHECK(m.at(i, j) == doctest::Approx(i + j));
            }
        }
    }

    SUBCASE("4D") {
        auto m = getMat<Type, 4>(kInput);
        for (size_t i = 0; i < 4; i++) {
            for (size_t j = 0; j < 4; j++) {
                // Read, write, and read again
                CHECK(m.at(i, j) == doctest::Approx(kInput[i][j]));
                m.at(i, j) = (i + j);
                CHECK(m.at(i, j) == doctest::Approx(i + j));
            }
        }
    }
}

TEST_CASE_TEMPLATE("Access rows by index with at()", Type, VALID_TYPES) {
    constexpr TestArray2D kInput{{
            {1.0L, 2.0L, -3.5L, 0.0L},
            {5.0L, 6.6L, 7.0L, -9.0L},
            {-1.0L, -2.0L, 3.0L, -4.0L},
            {-5.0L, -6.0L, 7.0L, -8.0L},
    }};

    SUBCASE("2D") {
        auto m = getMat<Type, 2>(kInput);
        for (size_t i = 0; i < 2; i++) {
            const auto kExpected = getVec<Type, 2>(kInput[i]);
            // Read, write, and read again
            CHECK(m.at(i) == kExpected);
            m.at(i).clear();
            CHECK(m.at(i) == getVec<Type, 2>({}));
        }
        // Out-of-bounds
        CHECK_THROWS(m.at(2).normalize_in_place());
    }

    SUBCASE("3D") {
        auto m = getMat<Type, 3>(kInput);
        for (size_t i = 0; i < 3; i++) {
            const auto kExpected = getVec<Type, 3>(kInput[i]);
            // Read, write, and read again
            CHECK(m.at(i) == kExpected);
            m.at(i).clear();
            CHECK(m.at(i) == getVec<Type, 3>({}));
        }
        // Out-of-bounds
        CHECK_THROWS(m.at(3).normalize_in_place());
    }

    SUBCASE("4D") {
        auto m = getMat<Type, 4>(kInput);
        for (size_t i = 0; i < 4; i++) {
            const auto kExpected = getVec<Type, 4>(kInput[i]);
            // Read, write, and read again
            CHECK(m.at(i) == kExpected);
            m.at(i).clear();
            CHECK(m.at(i) == getVec<Type, 4>({}));
        }
        // Out-of-bounds
        CHECK_THROWS(m.at(4).normalize_in_place());
    }
}

TEST_CASE_TEMPLATE("Begin/end iterator access", Type, VALID_TYPES) {
    constexpr TestArray2D kInput{{
            {1.0L, 2.0L, -3.5L, 0.0L},
            {5.0L, 6.6L, 7.0L, -9.0L},
            {-1.0L, -2.0L, 3.0L, -4.0L},
            {-5.0L, -6.0L, 7.0L, -8.0L},
    }};
    constexpr Type kValue{static_cast<Type>(7)}; // arbitrary
    constexpr TestArray kExpected{7.0L, 7.0L, 7.0L, 7.0L};

    SUBCASE("2D") {
        auto m = getMat<Type, 2>(kInput) ;
        for (auto& row : m) {
            row.fill(kValue);
        }
        std::all_of(m.cbegin(), m.cend(),
                    [kExpected](auto& row) { return (row == getVec<Type, 2>(kExpected)); });
    }

    SUBCASE("3D") {
        auto m = getMat<Type, 3>(kInput) ;
        for (auto& row : m) {
            row.fill(kValue);
        }
        std::all_of(m.cbegin(), m.cend(),
                    [kExpected](auto& row) { return (row == getVec<Type, 3>(kExpected)); });
    }

    SUBCASE("4D") {
        auto m = getMat<Type, 4>(kInput) ;
        for (auto& row : m) {
            row.fill(kValue);
        }
        std::all_of(m.cbegin(), m.cend(),
                    [kExpected](auto& row) { return (row == getVec<Type, 4>(kExpected)); });
    }
}

TEST_CASE_TEMPLATE("Determinant", Type, VALID_TYPES) {
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

TEST_CASE_TEMPLATE("Transpose", Type, VALID_TYPES) {
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

TEST_CASE_TEMPLATE("Inverse", Type, VALID_TYPES) {
    constexpr TestArray2D kInput{{
            {1.0L, 2.0L, -3.5L, 0.0L},
            {5.0L, 6.6L, 7.0L, -9.0L},
            {-1.0L, -2.0L, 3.0L, -4.0L},
            {-5.0L, -6.0L, 7.0L, -8.0L},
    }};

    SUBCASE("2D") {
        constexpr TestArray2D kExpected{{
                {-1.941176470588235294L,  0.58823529411764705882L},
                { 1.470588235294117647L, -0.29411764705882352941L},
        }};
        constexpr auto m = getMat<Type, 2>(kInput);
        constexpr auto m_inverse = m.inverse();
        CHECK(m_inverse == getMat<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr TestArray2D kExpected{{
                { 19.882352941176470588L,  0.58823529411764705882L,  21.823529411764705882L},
                {-12.941176470588235294L, -0.29411764705882352941L, -14.411764705882352941L},
                {-2.0L,                    0.0L,                    -2.0L},
        }};
        constexpr auto m = getMat<Type, 3>(kInput);
        constexpr auto m_inverse = m.inverse();
        CHECK(m_inverse == getMat<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr TestArray2D kExpected{{
            {-0.165242169797420501698L, -0.071225073188543319702L,
              1.281339066661894321420L, -0.560541325993835926045L},
            { 0.113960117101669311523L,  0.135327639058232307434L,
             -1.034544188063591718674L,  0.365028500091284513474L},
            {-0.267806275188922882075L,  0.056980058550834655762L,
             -0.225071231275796890253L,  0.048433049768209457398L},
            {-0.216524222493171691886L, -0.007122507318854331970L,
             -0.221866102982312440878L, -0.006054131221026182176L},
        }};
        constexpr auto m = getMat<Type, 4>(kInput);
        constexpr auto m_inverse = m.inverse();
        CHECK(m_inverse == getMat<Type, 4>(kExpected));
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
