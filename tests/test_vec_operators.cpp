// Unit tests for the Vec class implementation (operators)

#include <string>
#include <sstream>

// Testing headers
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "test_utils.hpp"

// UUT headers
#include "vec.hpp"

TEST_CASE_TEMPLATE("Access elements by [] (all types)", Type, VALID_TYPES) {
    // Shared input data:
    constexpr TestArray kInput{1.0L, 2.0L, 3.0L, 4.0L};
    constexpr Type kOffset{static_cast<Type>(7)}; // arbitrary

    SUBCASE("2D") {
        auto v = getVec<2, Type>(kInput);
        for (size_t i = 0; i < 2; i++) {
            // Read, write and read again
            CHECK(v[i] == kInput[i]);
            v[i] = i + kOffset;
            CHECK(v[i] == i + kOffset);
        }
    }

    SUBCASE("3D") {
        auto v = getVec<3, Type>(kInput);
        for (size_t i = 0; i < 3; i++) {
            // Read, write and read again
            CHECK(v[i] == kInput[i]);
            v[i] = i + kOffset;
            CHECK(v[i] == i + kOffset);
        }
    }

    SUBCASE("4D") {
        auto v = getVec<4, Type>(kInput);
        for (size_t i = 0; i < 4; i++) {
            // Read, write and read again
            CHECK(v[i] == kInput[i]);
            v[i] = i + kOffset;
            CHECK(v[i] == i + kOffset);
        }
    }
}

TEST_CASE_TEMPLATE("Vector += vector (floating-point)", Type, VALID_FLOAT_TYPES) {
    // Shared input and expected output data:
    constexpr TestArray kInput1{1.2L, 2.0L, 3.5L, -14.0L};
    constexpr TestArray kInput2{-5.0L, 6.0L, 7.0L, 8.0L};
    constexpr TestArray kExpected{-3.8L, 8.0L, 10.5L, -6.0L};

    SUBCASE("2D") {
        auto v1 = getVec<2, Type>(kInput1);
        constexpr auto v2 = getVec<2, Type>(kInput2);
        v1 += v2;
        CHECK(v1 == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        auto v1 = getVec<3, Type>(kInput1);
        constexpr auto v2 = getVec<3, Type>(kInput2);
        v1 += v2;
        CHECK(v1 == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        auto v1 = getVec<4, Type>(kInput1);
        constexpr auto v2 = getVec<4, Type>(kInput2);
        v1 += v2;
        CHECK(v1 == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector += vector (fixed-point)", Type, VALID_INT_TYPES) {
    // Shared input and expected output data:
    constexpr TestArrayInt kInput1{1, 2, 3, -14};
    constexpr TestArrayInt kInput2{-5, 6, 7, 8};
    constexpr TestArrayInt kExpected{-4, 8, 10, -6};

    SUBCASE("2D") {
        auto v1 = getVec<2, Type>(kInput1);
        constexpr auto v2 = getVec<2, Type>(kInput2);
        v1 += v2;
        CHECK(v1 == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        auto v1 = getVec<3, Type>(kInput1);
        constexpr auto v2 = getVec<3, Type>(kInput2);
        v1 += v2;
        CHECK(v1 == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        auto v1 = getVec<4, Type>(kInput1);
        constexpr auto v2 = getVec<4, Type>(kInput2);
        v1 += v2;
        CHECK(v1 == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector -= vector (floating-point)", Type, VALID_FLOAT_TYPES) {
    // Shared input and expected output data:
    constexpr TestArray kInput1{1.2L, 2.0L, -15.0L, 20.7L};
    constexpr TestArray kInput2{5.0L, 6.0L, 7.0L, 8.0L};
    constexpr TestArray kExpected{-3.8L, -4.0L, -22.0L, 12.7L};

    SUBCASE("2D") {
        auto v1 = getVec<2, Type>(kInput1);
        constexpr auto v2 = getVec<2, Type>(kInput2);
        v1 -= v2;
        CHECK(v1 == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        auto v1 = getVec<3, Type>(kInput1);
        constexpr auto v2 = getVec<3, Type>(kInput2);
        v1 -= v2;
        CHECK(v1 == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        auto v1 = getVec<4, Type>(kInput1);
        constexpr auto v2 = getVec<4, Type>(kInput2);
        v1 -= v2;
        CHECK(v1 == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector -= vector (fixed-point)", Type, VALID_INT_TYPES) {
    // Shared input and expected output data:
    constexpr TestArrayInt kInput1{1, 2, -15, 20};
    constexpr TestArrayInt kInput2{5, 6, 7, 8};
    constexpr TestArrayInt kExpected{-4, -4, -22, 12};

    SUBCASE("2D") {
        auto v1 = getVec<2, Type>(kInput1);
        constexpr auto v2 = getVec<2, Type>(kInput2);
        v1 -= v2;
        CHECK(v1 == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        auto v1 = getVec<3, Type>(kInput1);
        constexpr auto v2 = getVec<3, Type>(kInput2);
        v1 -= v2;
        CHECK(v1 == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        auto v1 = getVec<4, Type>(kInput1);
        constexpr auto v2 = getVec<4, Type>(kInput2);
        v1 -= v2;
        CHECK(v1 == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector *= scalar (floating-point)", Type, VALID_FLOAT_TYPES) {
    // Shared input and expected output data:
    constexpr TestArray kInput{0.0L, 2.6L, 3.0L, -4.0L};
    constexpr Type kScalar{static_cast<Type>(2.4L)};
    constexpr TestArray kExpected{0.0L, 6.24L, 7.2L, -9.6L};

    SUBCASE("2D") {
        auto v = getVec<2, Type>(kInput);
        v *= kScalar;
        CHECK(v == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        auto v = getVec<3, Type>(kInput);
        v *= kScalar;
        CHECK(v == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        auto v = getVec<4, Type>(kInput);
        v *= kScalar;
        CHECK(v == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector *= scalar (fixed-point)", Type, VALID_INT_TYPES) {
    // Shared input and expected output data:
    constexpr TestArrayInt kInput{0, 2, 30, -4};
    constexpr Type kScalar{static_cast<Type>(-3L)};
    constexpr TestArray kExpected{0.0L, -6L, -90L, 12L};

    SUBCASE("2D") {
        auto v = getVec<2, Type>(kInput);
        v *= kScalar;
        CHECK(v == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        auto v = getVec<3, Type>(kInput);
        v *= kScalar;
        CHECK(v == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        auto v = getVec<4, Type>(kInput);
        v *= kScalar;
        CHECK(v == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector /= scalar (floating-point)", Type, VALID_FLOAT_TYPES) {
    // Shared input and expected output data:
    constexpr TestArray kInput{0.0L, 2.8L, 28.0L, -5.6L};
    constexpr Type kScalar{static_cast<Type>(1.4L)};
    constexpr TestArray kExpected{0.0L, 2.0L, 20.0L, -4.0L};

    SUBCASE("2D") {
        auto v = getVec<2, Type>(kInput);
        v /= kScalar;
        CHECK(v == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        auto v = getVec<3, Type>(kInput);
        v /= kScalar;
        CHECK(v == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        auto v = getVec<4, Type>(kInput);
        v /= kScalar;
        CHECK(v == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector /= scalar (fixed-point)", Type, VALID_INT_TYPES) {
    // Shared input and expected output data:
    constexpr TestArrayInt kInput{10, 20, 30, 40};
    constexpr Type kScalar{static_cast<Type>(4)};
    constexpr TestArrayInt kExpected{2, 5, 7, 10};

    SUBCASE("2D") {
        auto v = getVec<2, Type>(kInput);
        v /= kScalar;
        CHECK(v == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        auto v = getVec<3, Type>(kInput);
        v /= kScalar;
        CHECK(v == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        auto v = getVec<4, Type>(kInput);
        v /= kScalar;
        CHECK(v == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Test -vector (all types)", Type, VALID_TYPES) {
    // Shared input and expected output data:
    constexpr TestArray kInput{1.0L, -22.1L, 0.0L, 3.9L};
    constexpr TestArray kExpected{-1.0L, 22.1L, 0.0L, -3.9L};

    SUBCASE("2D") {
        constexpr auto v = getVec<2, Type>(kInput);
        constexpr auto v_neg = -v;
        CHECK(v_neg == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v = getVec<3, Type>(kInput);
        constexpr auto v_neg = -v;
        CHECK(v_neg == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<4, Type>(kInput);
        constexpr auto v_neg = -v;
        CHECK(v_neg == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector ==/!= vector (floating-point)", Type, VALID_FLOAT_TYPES) {
    // Shared input and expected output data:
    constexpr TestArray kInput{1.0L, -22.01L, 0.0L, 3.999L};

    SUBCASE("2D") {
        // Check equality case
        constexpr auto v1 = getVec<2, Type>(kInput);
        constexpr auto v2 = getVec<2, Type>(kInput);
        CHECK(v1 == v2);
        CHECK_FALSE(v1 != v2);

        // Check inequality cases
        for (size_t i = 0; i < 2; i++) {
            Vec<2, Type> v2_modified = v2;
            v2_modified[i] += 0.001L;
            CHECK_FALSE(v1 == v2_modified);
            CHECK(v1 != v2_modified);
        }
    }

    SUBCASE("3D") {
        // Check equality case
        constexpr auto v1 = getVec<3, Type>(kInput);
        constexpr auto v2 = getVec<3, Type>(kInput);
        CHECK(v1 == v2);
        CHECK_FALSE(v1 != v2);

        // Check inequality cases
        for (size_t i = 0; i < 3; i++) {
            Vec<3, Type> v2_modified = v2;
            v2_modified[i] += 0.001L;
            CHECK_FALSE(v1 == v2_modified);
            CHECK(v1 != v2_modified);
        }
    }

    SUBCASE("4D") {
        // Check equality case
        constexpr auto v1 = getVec<4, Type>(kInput);
        constexpr auto v2 = getVec<4, Type>(kInput);
        CHECK(v1 == v2);
        CHECK_FALSE(v1 != v2);

        // Check inequality cases
        for (size_t i = 0; i < 4; i++) {
            Vec<4, Type> v2_modified = v2;
            v2_modified[i] += 0.001L;
            CHECK_FALSE(v1 == v2_modified);
            CHECK(v1 != v2_modified);
        }
    }
}

TEST_CASE_TEMPLATE("Vector ==/!= vector (fixed-point)", Type, VALID_INT_TYPES) {
    // Shared input and expected output data:
    constexpr TestArrayInt kInput{1, 2, 3, 4};

    SUBCASE("2D") {
        // Check equality case
        constexpr auto v1 = getVec<2, Type>(kInput);
        constexpr auto v2 = getVec<2, Type>(kInput);
        CHECK(v1 == v2);
        CHECK_FALSE(v1 != v2);

        // Check inequality cases
        for (size_t i = 0; i < 2; i++) {
            Vec<2, Type> v2_modified = v2;
            v2_modified[i] += 1;
            CHECK_FALSE(v1 == v2_modified);
            CHECK(v1 != v2_modified);
        }
    }

    SUBCASE("3D") {
        // Check equality case
        constexpr auto v1 = getVec<3, Type>(kInput);
        constexpr auto v2 = getVec<3, Type>(kInput);
        CHECK(v1 == v2);
        CHECK_FALSE(v1 != v2);

        // Check inequality cases
        for (size_t i = 0; i < 3; i++) {
            Vec<3, Type> v2_modified = v2;
            v2_modified[i] += 1;
            CHECK_FALSE(v1 == v2_modified);
            CHECK(v1 != v2_modified);
        }
    }

    SUBCASE("4D") {
        // Check equality case
        constexpr auto v1 = getVec<4, Type>(kInput);
        constexpr auto v2 = getVec<4, Type>(kInput);
        CHECK(v1 == v2);
        CHECK_FALSE(v1 != v2);

        // Check inequality cases
        for (size_t i = 0; i < 4; i++) {
            Vec<4, Type> v2_modified = v2;
            v2_modified[i] += 1;
            CHECK_FALSE(v1 == v2_modified);
            CHECK(v1 != v2_modified);
        }
    }
}

TEST_CASE_TEMPLATE("Vector - vector (floating-point)", Type, VALID_FLOAT_TYPES) {
    // Shared input and expected output data:
    constexpr TestArray kInput1{1.2L, 2.0L, -15.0L, 20.7L};
    constexpr TestArray kInput2{5.0L, 6.0L, 7.0L, 8.0L};
    constexpr TestArray kExpected{-3.8L, -4.0L, -22.0L, 12.7L};

    SUBCASE("2D") {
        constexpr auto v1 = getVec<2, Type>(kInput1);
        constexpr auto v2 = getVec<2, Type>(kInput2);
        constexpr Vec<2, Type> v_diff = v1 - v2;
        CHECK(v_diff == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v1 = getVec<3, Type>(kInput1);
        constexpr auto v2 = getVec<3, Type>(kInput2);
        constexpr Vec<3, Type> v_diff = v1 - v2;
        CHECK(v_diff == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v1 = getVec<4, Type>(kInput1);
        constexpr auto v2 = getVec<4, Type>(kInput2);
        constexpr Vec<4, Type> v_diff = v1 - v2;
        CHECK(v_diff == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector - vector (fixed-point)", Type, VALID_INT_TYPES) {
    // Shared input and expected output data:
    constexpr TestArrayInt kInput1{1, 2, -15, 20};
    constexpr TestArrayInt kInput2{5, 6, 7, 8};
    constexpr TestArrayInt kExpected{-4, -4, -22, 12};

    SUBCASE("2D") {
        constexpr auto v1 = getVec<2, Type>(kInput1);
        constexpr auto v2 = getVec<2, Type>(kInput2);
        constexpr Vec<2, Type> v_diff = v1 - v2;
        CHECK(v_diff == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v1 = getVec<3, Type>(kInput1);
        constexpr auto v2 = getVec<3, Type>(kInput2);
        constexpr Vec<3, Type> v_diff = v1 - v2;
        CHECK(v_diff == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v1 = getVec<4, Type>(kInput1);
        constexpr auto v2 = getVec<4, Type>(kInput2);
        constexpr Vec<4, Type> v_diff = v1 - v2;
        CHECK(v_diff == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector + vector (floating-point)", Type, VALID_FLOAT_TYPES) {
    // Shared input and expected output data:
    constexpr TestArray kInput1{1.2L, 0.0L, 3.0L, 4.1L};
    constexpr TestArray kInput2{5.0L, 123.1L, -7.2L, 8.1L};
    constexpr TestArray kExpected{6.2L, 123.1L, -4.2L, 12.2L};

    SUBCASE("2D") {
        constexpr auto v1 = getVec<2, Type>(kInput1);
        constexpr auto v2 = getVec<2, Type>(kInput2);
        constexpr auto v_sum = v1 + v2;
        CHECK(v_sum == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v1 = getVec<3, Type>(kInput1);
        constexpr auto v2 = getVec<3, Type>(kInput2);
        constexpr auto v_sum = v1 + v2;
        CHECK(v_sum == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v1 = getVec<4, Type>(kInput1);
        constexpr auto v2 = getVec<4, Type>(kInput2);
        constexpr auto v_sum = v1 + v2;
        CHECK(v_sum == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector + vector (fixed-point)", Type, VALID_INT_TYPES) {
    // Shared input and expected output data:
    constexpr TestArrayInt kInput1{1, 0, 3, -4};
    constexpr TestArrayInt kInput2{5, 123, -7, -8};
    constexpr TestArrayInt kExpected{6, 123, -4, -12};

    SUBCASE("2D") {
        constexpr auto v1 = getVec<2, Type>(kInput1);
        constexpr auto v2 = getVec<2, Type>(kInput2);
        constexpr auto v_sum = v1 + v2;
        CHECK(v_sum == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v1 = getVec<3, Type>(kInput1);
        constexpr auto v2 = getVec<3, Type>(kInput2);
        constexpr auto v_sum = v1 + v2;
        CHECK(v_sum == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v1 = getVec<4, Type>(kInput1);
        constexpr auto v2 = getVec<4, Type>(kInput2);
        constexpr auto v_sum = v1 + v2;
        CHECK(v_sum == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector * scalar (floating-point)", Type, VALID_FLOAT_TYPES) {
    // Shared input and expected output data:
    constexpr TestArray kInput{0.0L, 2.6L, 3.0L, -4.0L};
    constexpr Type kScalar{static_cast<Type>(2.4L)};
    constexpr TestArray kExpected{0.0L, 6.24L, 7.2L, -9.6L};

    SUBCASE("2D") {
        constexpr auto v = getVec<2, Type>(kInput);
        constexpr Vec<2, Type> v_product = v * kScalar;
        constexpr Vec<2, Type> v_product_reverse = kScalar * v;
        CHECK(v_product == getVec<2, Type>(kExpected));
        CHECK(v_product_reverse == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v = getVec<3, Type>(kInput);
        constexpr Vec<3, Type> v_product = v * kScalar;
        constexpr Vec<3, Type> v_product_reverse = kScalar * v;
        CHECK(v_product == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<4, Type>(kInput);
        constexpr Vec<4, Type> v_product = v * kScalar;
        constexpr Vec<4, Type> v_product_reverse = kScalar * v;
        CHECK(v_product == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector * scalar (fixed-point)", Type, VALID_INT_TYPES) {
    // Shared input and expected output data:
    constexpr TestArrayInt kInput{0, 2, 30, -4};
    constexpr Type kScalar{static_cast<Type>(-3L)};
    constexpr TestArray kExpected{0.0L, -6L, -90L, 12L};

    SUBCASE("2D") {
        constexpr auto v = getVec<2, Type>(kInput);
        constexpr Vec<2, Type> v_product = v * kScalar;
        constexpr Vec<2, Type> v_product_reverse = kScalar * v;
        CHECK(v_product == getVec<2, Type>(kExpected));
        CHECK(v_product_reverse == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v = getVec<3, Type>(kInput);
        constexpr Vec<3, Type> v_product = v * kScalar;
        constexpr Vec<3, Type> v_product_reverse = kScalar * v;
        CHECK(v_product == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<4, Type>(kInput);
        constexpr Vec<4, Type> v_product = v * kScalar;
        constexpr Vec<4, Type> v_product_reverse = kScalar * v;
        CHECK(v_product == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector / scalar (floating-point)", Type, VALID_FLOAT_TYPES) {
    // Shared input and expected output data:
    constexpr TestArray kInput{0.0L, 2.8L, 28.0L, -5.6L};
    constexpr Type kScalar{static_cast<Type>(1.4L)};
    constexpr TestArray kExpected{0.0L, 2.0L, 20.0L, -4.0L};

    SUBCASE("2D") {
        constexpr auto v = getVec<2, Type>(kInput);
        constexpr Vec<2, Type> v_quotient = v / kScalar;
        CHECK(v_quotient == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v = getVec<3, Type>(kInput);
        constexpr Vec<3, Type> v_quotient = v / kScalar;
        CHECK(v_quotient == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<4, Type>(kInput);
        constexpr Vec<4, Type> v_quotient = v / kScalar;
        CHECK(v_quotient == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector / scalar (fixed-point)", Type, VALID_INT_TYPES) {
    // Shared input and expected output data:
    constexpr TestArrayInt kInput{10, 20, 30, 40};
    constexpr Type kScalar{static_cast<Type>(4)};
    constexpr TestArrayInt kExpected{2, 5, 7, 10};

    SUBCASE("2D") {
        constexpr auto v = getVec<2, Type>(kInput);
        constexpr Vec<2, Type> v_quotient = v / kScalar;
        CHECK(v_quotient == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v = getVec<3, Type>(kInput);
        constexpr Vec<3, Type> v_quotient = v / kScalar;
        CHECK(v_quotient == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<4, Type>(kInput);
        constexpr Vec<4, Type> v_quotient = v / kScalar;
        CHECK(v_quotient == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Ostream operator (floating-point)", Type, VALID_FLOAT_TYPES) {
    // Shared input data:
    constexpr TestArray kInput{1.0L, 2.001L, -3.999L, 4.5L};

    // Configure output resolution
    std::stringstream out;
    out << std::fixed << std::setprecision(3);

    SUBCASE("2D") {
        const std::string kExpected{"[  1.000  2.001  ]"};
        constexpr auto v = getVec<2, Type>(kInput);
        out << v;
        CHECK(out.str() == kExpected);
    }

    SUBCASE("3D") {
        const std::string kExpected{"[  1.000  2.001  -3.999  ]"};
        constexpr auto v = getVec<3, Type>(kInput);
        out << v;
        CHECK(out.str() == kExpected);
    }

    SUBCASE("4D") {
        const std::string kExpected{"[  1.000  2.001  -3.999  4.500  ]"};
        constexpr auto v = getVec<4, Type>(kInput);
        out << v;
        CHECK(out.str() == kExpected);
    }
}

TEST_CASE_TEMPLATE("Ostream operator (fixed-point)", Type, VALID_INT_TYPES) {
    // Shared input data:
    constexpr TestArrayInt kInput{1, 2, -3, 4};

    // Configure output resolution
    std::stringstream out;
    out << std::fixed << std::setprecision(3);

    SUBCASE("2D") {
        const std::string kExpected{"[  1  2  ]"};
        constexpr auto v = getVec<2, Type>(kInput);
        out << v;
        CHECK(out.str() == kExpected);
    }

    SUBCASE("3D") {
        const std::string kExpected{"[  1  2  -3  ]"};
        constexpr auto v = getVec<3, Type>(kInput);
        out << v;
        CHECK(out.str() == kExpected);
    }

    SUBCASE("4D") {
        const std::string kExpected{"[  1  2  -3  4  ]"};
        constexpr auto v = getVec<4, Type>(kInput);
        out << v;
        CHECK(out.str() == kExpected);
    }
}
