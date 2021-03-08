// Unit tests for the Vec class implementation (operators)

#include <string>
#include <sstream>

// Testing headers
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "test_utils_vec.hpp"

// UUT headers
#include "vec.hpp"

TEST_CASE_TEMPLATE("Access elements by [] (all types)", Type, VALID_TYPES) {
    // Shared input data:
    constexpr TestArray kInput{1.0L, 2.0L, 3.0L, 4.0L};
    constexpr Type kOffset{static_cast<Type>(7)}; // arbitrary

    SUBCASE("2D") {
        auto v = getVec<Type, 2>(kInput);
        for (size_t i = 0; i < 2; i++) {
            // Read, write and read again
            CHECK(v[i] == kInput[i]);
            v[i] = i + kOffset;
            CHECK(v[i] == i + kOffset);
        }
    }

    SUBCASE("3D") {
        auto v = getVec<Type, 3>(kInput);
        for (size_t i = 0; i < 3; i++) {
            // Read, write and read again
            CHECK(v[i] == kInput[i]);
            v[i] = i + kOffset;
            CHECK(v[i] == i + kOffset);
        }
    }

    SUBCASE("4D") {
        auto v = getVec<Type, 4>(kInput);
        for (size_t i = 0; i < 4; i++) {
            // Read, write and read again
            CHECK(v[i] == kInput[i]);
            v[i] = i + kOffset;
            CHECK(v[i] == i + kOffset);
        }
    }
}

TEST_CASE_TEMPLATE("Vector += vector", Type, VALID_TYPES) {
    // Shared input and expected output data:
    constexpr TestArray kInput1{1.2L, 2.0L, 3.5L, -14.0L};
    constexpr TestArray kInput2{-5.0L, 6.0L, 7.0L, 8.0L};
    constexpr TestArray kExpected{-3.8L, 8.0L, 10.5L, -6.0L};

    SUBCASE("2D") {
        auto v1 = getVec<Type, 2>(kInput1);
        constexpr auto v2 = getVec<Type, 2>(kInput2);
        v1 += v2;
        CHECK(v1 == getVec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        auto v1 = getVec<Type, 3>(kInput1);
        constexpr auto v2 = getVec<Type, 3>(kInput2);
        v1 += v2;
        CHECK(v1 == getVec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        auto v1 = getVec<Type, 4>(kInput1);
        constexpr auto v2 = getVec<Type, 4>(kInput2);
        v1 += v2;
        CHECK(v1 == getVec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector -= vector", Type, VALID_TYPES) {
    // Shared input and expected output data:
    constexpr TestArray kInput1{1.2L, 2.0L, -15.0L, 20.7L};
    constexpr TestArray kInput2{5.0L, 6.0L, 7.0L, 8.0L};
    constexpr TestArray kExpected{-3.8L, -4.0L, -22.0L, 12.7L};

    SUBCASE("2D") {
        auto v1 = getVec<Type, 2>(kInput1);
        constexpr auto v2 = getVec<Type, 2>(kInput2);
        v1 -= v2;
        CHECK(v1 == getVec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        auto v1 = getVec<Type, 3>(kInput1);
        constexpr auto v2 = getVec<Type, 3>(kInput2);
        v1 -= v2;
        CHECK(v1 == getVec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        auto v1 = getVec<Type, 4>(kInput1);
        constexpr auto v2 = getVec<Type, 4>(kInput2);
        v1 -= v2;
        CHECK(v1 == getVec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector *= scalar", Type, VALID_TYPES) {
    // Shared input and expected output data:
    constexpr TestArray kInput{0.0L, 2.6L, 3.0L, -4.0L};
    constexpr Type kScalar{static_cast<Type>(2.4L)};
    constexpr TestArray kExpected{0.0L, 6.24L, 7.2L, -9.6L};

    SUBCASE("2D") {
        auto v = getVec<Type, 2>(kInput);
        v *= kScalar;
        CHECK(v == getVec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        auto v = getVec<Type, 3>(kInput);
        v *= kScalar;
        CHECK(v == getVec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        auto v = getVec<Type, 4>(kInput);
        v *= kScalar;
        CHECK(v == getVec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector /= scalar", Type, VALID_TYPES) {
    // Shared input and expected output data:
    constexpr TestArray kInput{0.0L, 2.8L, 28.0L, -5.6L};
    constexpr Type kScalar{static_cast<Type>(1.4L)};
    constexpr TestArray kExpected{0.0L, 2.0L, 20.0L, -4.0L};

    SUBCASE("2D") {
        auto v = getVec<Type, 2>(kInput);
        v /= kScalar;
        CHECK(v == getVec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        auto v = getVec<Type, 3>(kInput);
        v /= kScalar;
        CHECK(v == getVec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        auto v = getVec<Type, 4>(kInput);
        v /= kScalar;
        CHECK(v == getVec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Test -vector (all types)", Type, VALID_TYPES) {
    // Shared input and expected output data:
    constexpr TestArray kInput{1.0L, -22.1L, 0.0L, 3.9L};
    constexpr TestArray kExpected{-1.0L, 22.1L, 0.0L, -3.9L};

    SUBCASE("2D") {
        constexpr auto v = getVec<Type, 2>(kInput);
        constexpr auto v_neg = -v;
        CHECK(v_neg == getVec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v = getVec<Type, 3>(kInput);
        constexpr auto v_neg = -v;
        CHECK(v_neg == getVec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<Type, 4>(kInput);
        constexpr auto v_neg = -v;
        CHECK(v_neg == getVec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector ==/!= vector", Type, VALID_TYPES) {
    // Shared input and expected output data:
    constexpr TestArray kInput{1.0L, -22.01L, 0.0L, 3.999L};

    SUBCASE("2D") {
        // Check equality case
        constexpr auto v1 = getVec<Type, 2>(kInput);
        constexpr auto v2 = getVec<Type, 2>(kInput);
        CHECK(v1 == v2);
        CHECK_FALSE(v1 != v2);

        // Check inequality cases
        for (size_t i = 0; i < 2; i++) {
            Vec<Type, 2> v2_modified = v2;
            v2_modified[i] += 0.001L;
            CHECK_FALSE(v1 == v2_modified);
            CHECK(v1 != v2_modified);
        }
    }

    SUBCASE("3D") {
        // Check equality case
        constexpr auto v1 = getVec<Type, 3>(kInput);
        constexpr auto v2 = getVec<Type, 3>(kInput);
        CHECK(v1 == v2);
        CHECK_FALSE(v1 != v2);

        // Check inequality cases
        for (size_t i = 0; i < 3; i++) {
            Vec<Type, 3> v2_modified = v2;
            v2_modified[i] += 0.001L;
            CHECK_FALSE(v1 == v2_modified);
            CHECK(v1 != v2_modified);
        }
    }

    SUBCASE("4D") {
        // Check equality case
        constexpr auto v1 = getVec<Type, 4>(kInput);
        constexpr auto v2 = getVec<Type, 4>(kInput);
        CHECK(v1 == v2);
        CHECK_FALSE(v1 != v2);

        // Check inequality cases
        for (size_t i = 0; i < 4; i++) {
            Vec<Type, 4> v2_modified = v2;
            v2_modified[i] += 0.001L;
            CHECK_FALSE(v1 == v2_modified);
            CHECK(v1 != v2_modified);
        }
    }
}

TEST_CASE_TEMPLATE("Vector - vector", Type, VALID_TYPES) {
    // Shared input and expected output data:
    constexpr TestArray kInput1{1.2L, 2.0L, -15.0L, 20.7L};
    constexpr TestArray kInput2{5.0L, 6.0L, 7.0L, 8.0L};
    constexpr TestArray kExpected{-3.8L, -4.0L, -22.0L, 12.7L};

    SUBCASE("2D") {
        constexpr auto v1 = getVec<Type, 2>(kInput1);
        constexpr auto v2 = getVec<Type, 2>(kInput2);
        constexpr Vec<Type, 2> v_diff = v1 - v2;
        CHECK(v_diff == getVec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v1 = getVec<Type, 3>(kInput1);
        constexpr auto v2 = getVec<Type, 3>(kInput2);
        constexpr Vec<Type, 3> v_diff = v1 - v2;
        CHECK(v_diff == getVec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v1 = getVec<Type, 4>(kInput1);
        constexpr auto v2 = getVec<Type, 4>(kInput2);
        constexpr Vec<Type, 4> v_diff = v1 - v2;
        CHECK(v_diff == getVec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector + vector", Type, VALID_TYPES) {
    // Shared input and expected output data:
    constexpr TestArray kInput1{1.2L, 0.0L, 3.0L, 4.1L};
    constexpr TestArray kInput2{5.0L, 123.1L, -7.2L, 8.1L};
    constexpr TestArray kExpected{6.2L, 123.1L, -4.2L, 12.2L};

    SUBCASE("2D") {
        constexpr auto v1 = getVec<Type, 2>(kInput1);
        constexpr auto v2 = getVec<Type, 2>(kInput2);
        constexpr auto v_sum = v1 + v2;
        CHECK(v_sum == getVec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v1 = getVec<Type, 3>(kInput1);
        constexpr auto v2 = getVec<Type, 3>(kInput2);
        constexpr auto v_sum = v1 + v2;
        CHECK(v_sum == getVec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v1 = getVec<Type, 4>(kInput1);
        constexpr auto v2 = getVec<Type, 4>(kInput2);
        constexpr auto v_sum = v1 + v2;
        CHECK(v_sum == getVec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector * scalar", Type, VALID_TYPES) {
    // Shared input and expected output data:
    constexpr TestArray kInput{0.0L, 2.6L, 3.0L, -4.0L};
    constexpr Type kScalar{static_cast<Type>(2.4L)};
    constexpr TestArray kExpected{0.0L, 6.24L, 7.2L, -9.6L};

    SUBCASE("2D") {
        constexpr auto v = getVec<Type, 2>(kInput);
        constexpr Vec<Type, 2> v_product = v * kScalar;
        constexpr Vec<Type, 2> v_product_reverse = kScalar * v;
        CHECK(v_product == getVec<Type, 2>(kExpected));
        CHECK(v_product_reverse == getVec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v = getVec<Type, 3>(kInput);
        constexpr Vec<Type, 3> v_product = v * kScalar;
        constexpr Vec<Type, 3> v_product_reverse = kScalar * v;
        CHECK(v_product == getVec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<Type, 4>(kInput);
        constexpr Vec<Type, 4> v_product = v * kScalar;
        constexpr Vec<Type, 4> v_product_reverse = kScalar * v;
        CHECK(v_product == getVec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector / scalar", Type, VALID_TYPES) {
    // Shared input and expected output data:
    constexpr TestArray kInput{0.0L, 2.8L, 28.0L, -5.6L};
    constexpr Type kScalar{static_cast<Type>(1.4L)};
    constexpr TestArray kExpected{0.0L, 2.0L, 20.0L, -4.0L};

    SUBCASE("2D") {
        constexpr auto v = getVec<Type, 2>(kInput);
        constexpr Vec<Type, 2> v_quotient = v / kScalar;
        CHECK(v_quotient == getVec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v = getVec<Type, 3>(kInput);
        constexpr Vec<Type, 3> v_quotient = v / kScalar;
        CHECK(v_quotient == getVec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<Type, 4>(kInput);
        constexpr Vec<Type, 4> v_quotient = v / kScalar;
        CHECK(v_quotient == getVec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Ostream operator", Type, VALID_TYPES) {
    // Shared input data:
    constexpr TestArray kInput{1.0L, 2.001L, -3.999L, 4.5L};

    // Configure output resolution
    std::stringstream out;
    out << std::fixed << std::setprecision(3);

    SUBCASE("2D") {
        const std::string kExpected{"[  1.000  2.001  ]"};
        constexpr auto v = getVec<Type, 2>(kInput);
        out << v;
        CHECK(out.str() == kExpected);
    }

    SUBCASE("3D") {
        const std::string kExpected{"[  1.000  2.001  -3.999  ]"};
        constexpr auto v = getVec<Type, 3>(kInput);
        out << v;
        CHECK(out.str() == kExpected);
    }

    SUBCASE("4D") {
        const std::string kExpected{"[  1.000  2.001  -3.999  4.500  ]"};
        constexpr auto v = getVec<Type, 4>(kInput);
        out << v;
        CHECK(out.str() == kExpected);
    }
}
