// Unit tests for the Vec class implementation (operators)

#include <string>
#include <sstream>

// Testing headers
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "test_utils.hpp"

// UUT headers
#include "vec.hpp"

TEST_CASE_TEMPLATE("Access elements by []", Type, VALID_TYPES) {
    constexpr TestArray kInput{1.0, 2.0, 3.0, 4.0};
    constexpr Type kOffset = 7;

    SUBCASE("2D") {
        auto v = get_vec<Type, 2>(kInput);
        for (size_t i = 0; i < 2; i++) {
            // Read, write and read again
            CHECK(v[i] == kInput[i]);
            v[i] = i + kOffset;
            CHECK(v[i] == i + kOffset);
        }
    }

    SUBCASE("3D") {
        auto v = get_vec<Type, 3>(kInput);
        for (size_t i = 0; i < 3; i++) {
            // Read, write and read again
            CHECK(v[i] == kInput[i]);
            v[i] = i + kOffset;
            CHECK(v[i] == i + kOffset);
        }
    }

    SUBCASE("4D") {
        auto v = get_vec<Type, 4>(kInput);
        for (size_t i = 0; i < 4; i++) {
            // Read, write and read again
            CHECK(v[i] == kInput[i]);
            v[i] = i + kOffset;
            CHECK(v[i] == i + kOffset);
        }
    }
}

TEST_CASE_TEMPLATE("Vector += vector", Type, VALID_TYPES) {
    constexpr TestArray kInput1{1.2, 2.0, 3.5, -14.0};
    constexpr TestArray kInput2{-5.0, 6.0, 7.0, 8.0};
    constexpr TestArray kExpected{-3.8, 8.0, 10.5, -6.0};

    SUBCASE("2D") {
        auto v1 = get_vec<Type, 2>(kInput1);
        constexpr auto v2 = get_vec<Type, 2>(kInput2);
        v1 += v2;
        CHECK(v1 == get_approx_vec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        auto v1 = get_vec<Type, 3>(kInput1);
        constexpr auto v2 = get_vec<Type, 3>(kInput2);
        v1 += v2;
        CHECK(v1 == get_approx_vec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        auto v1 = get_vec<Type, 4>(kInput1);
        constexpr auto v2 = get_vec<Type, 4>(kInput2);
        v1 += v2;
        CHECK(v1 == get_approx_vec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector -= vector", Type, VALID_TYPES) {
    constexpr TestArray kInput1{1.2, 2.0, -15.0, 20.7};
    constexpr TestArray kInput2{5.0, 6.0, 7.0, 8.0};
    constexpr TestArray kExpected{-3.8, -4.0, -22.0, 12.7};

    SUBCASE("2D") {
        auto v1 = get_vec<Type, 2>(kInput1);
        constexpr auto v2 = get_vec<Type, 2>(kInput2);
        v1 -= v2;
        CHECK(v1 == get_approx_vec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        auto v1 = get_vec<Type, 3>(kInput1);
        constexpr auto v2 = get_vec<Type, 3>(kInput2);
        v1 -= v2;
        CHECK(v1 == get_approx_vec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        auto v1 = get_vec<Type, 4>(kInput1);
        constexpr auto v2 = get_vec<Type, 4>(kInput2);
        v1 -= v2;
        CHECK(v1 == get_approx_vec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector *= scalar", Type, VALID_TYPES) {
    constexpr TestArray kInput{0.0, 2.6, 3.0, -4.0};
    constexpr Type kScalar = 2.4;
    constexpr TestArray kExpected{0.0, 6.24, 7.2, -9.6};

    SUBCASE("2D") {
        auto v = get_vec<Type, 2>(kInput);
        v *= kScalar;
        CHECK(v == get_approx_vec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        auto v = get_vec<Type, 3>(kInput);
        v *= kScalar;
        CHECK(v == get_approx_vec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        auto v = get_vec<Type, 4>(kInput);
        v *= kScalar;
        CHECK(v == get_approx_vec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector /= scalar", Type, VALID_TYPES) {
    constexpr TestArray kInput{0.0, 2.8, 28.0, -5.6};
    constexpr Type kScalar = 1.4;
    constexpr TestArray kExpected{0.0, 2.0, 20.0, -4.0};

    SUBCASE("2D") {
        auto v = get_vec<Type, 2>(kInput);
        v /= kScalar;
        CHECK(v == get_approx_vec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        auto v = get_vec<Type, 3>(kInput);
        v /= kScalar;
        CHECK(v == get_approx_vec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        auto v = get_vec<Type, 4>(kInput);
        v /= kScalar;
        CHECK(v == get_approx_vec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Negate (-vector)", Type, VALID_TYPES) {
    constexpr TestArray kInput{1.0, -22.1, 0.0, 3.9};
    constexpr TestArray kExpected{-1.0, 22.1, 0.0, -3.9};

    SUBCASE("2D") {
        constexpr auto v = get_vec<Type, 2>(kInput);
        constexpr auto v_neg = -v;
        CHECK(v_neg == get_approx_vec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v = get_vec<Type, 3>(kInput);
        constexpr auto v_neg = -v;
        CHECK(v_neg == get_approx_vec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v = get_vec<Type, 4>(kInput);
        constexpr auto v_neg = -v;
        CHECK(v_neg == get_approx_vec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector ==/!= vector", Type, VALID_TYPES) {
    constexpr TestArray kInput{1.0, -22.01, 0.0, 3.999};

    SUBCASE("2D") {
        // Check equality case
        constexpr auto v1 = get_vec<Type, 2>(kInput);
        constexpr auto v2 = get_vec<Type, 2>(kInput);
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
        constexpr auto v1 = get_vec<Type, 3>(kInput);
        constexpr auto v2 = get_vec<Type, 3>(kInput);
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
        constexpr auto v1 = get_vec<Type, 4>(kInput);
        constexpr auto v2 = get_vec<Type, 4>(kInput);
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
    constexpr TestArray kInput1{1.2, 2.0, -15.0, 20.7};
    constexpr TestArray kInput2{5.0, 6.0, 7.0, 8.0};
    constexpr TestArray kExpected{-3.8, -4.0, -22.0, 12.7};

    SUBCASE("2D") {
        constexpr auto v1 = get_vec<Type, 2>(kInput1);
        constexpr auto v2 = get_vec<Type, 2>(kInput2);
        constexpr Vec<Type, 2> v_diff = v1 - v2;
        CHECK(v_diff == get_approx_vec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v1 = get_vec<Type, 3>(kInput1);
        constexpr auto v2 = get_vec<Type, 3>(kInput2);
        constexpr Vec<Type, 3> v_diff = v1 - v2;
        CHECK(v_diff == get_approx_vec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v1 = get_vec<Type, 4>(kInput1);
        constexpr auto v2 = get_vec<Type, 4>(kInput2);
        constexpr Vec<Type, 4> v_diff = v1 - v2;
        CHECK(v_diff == get_approx_vec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector + vector", Type, VALID_TYPES) {
    constexpr TestArray kInput1{1.2, 0.0, 3.0, 4.1};
    constexpr TestArray kInput2{5.0, 123.1, -7.2, 8.1};
    constexpr TestArray kExpected{6.2, 123.1, -4.2, 12.2};

    SUBCASE("2D") {
        constexpr auto v1 = get_vec<Type, 2>(kInput1);
        constexpr auto v2 = get_vec<Type, 2>(kInput2);
        constexpr auto v_sum = v1 + v2;
        CHECK(v_sum == get_approx_vec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v1 = get_vec<Type, 3>(kInput1);
        constexpr auto v2 = get_vec<Type, 3>(kInput2);
        constexpr auto v_sum = v1 + v2;
        CHECK(v_sum == get_approx_vec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v1 = get_vec<Type, 4>(kInput1);
        constexpr auto v2 = get_vec<Type, 4>(kInput2);
        constexpr auto v_sum = v1 + v2;
        CHECK(v_sum == get_approx_vec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector * scalar", Type, VALID_TYPES) {
    constexpr TestArray kInput{0.0, 2.6, 3.0, -4.0};
    constexpr Type kScalar = 2.4;
    constexpr TestArray kExpected{0.0, 6.24, 7.2, -9.6};

    SUBCASE("2D") {
        constexpr auto v = get_vec<Type, 2>(kInput);
        constexpr Vec<Type, 2> v_product = v * kScalar;
        constexpr Vec<Type, 2> v_product_reverse = kScalar * v;
        CHECK(v_product == get_approx_vec<Type, 2>(kExpected));
        CHECK(v_product_reverse == get_approx_vec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v = get_vec<Type, 3>(kInput);
        constexpr Vec<Type, 3> v_product = v * kScalar;
        constexpr Vec<Type, 3> v_product_reverse = kScalar * v;
        CHECK(v_product == get_approx_vec<Type, 3>(kExpected));
        CHECK(v_product_reverse == get_approx_vec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v = get_vec<Type, 4>(kInput);
        constexpr Vec<Type, 4> v_product = v * kScalar;
        constexpr Vec<Type, 4> v_product_reverse = kScalar * v;
        CHECK(v_product == get_approx_vec<Type, 4>(kExpected));
        CHECK(v_product_reverse == get_approx_vec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Vector / scalar", Type, VALID_TYPES) {
    constexpr TestArray kInput{0.0, 2.8, 28.0, -5.6};
    constexpr Type kScalar = 1.4;
    constexpr TestArray kExpected{0.0, 2.0, 20.0, -4.0};

    SUBCASE("2D") {
        constexpr auto v = get_vec<Type, 2>(kInput);
        constexpr Vec<Type, 2> v_quotient = v / kScalar;
        CHECK(v_quotient == get_approx_vec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v = get_vec<Type, 3>(kInput);
        constexpr Vec<Type, 3> v_quotient = v / kScalar;
        CHECK(v_quotient == get_approx_vec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v = get_vec<Type, 4>(kInput);
        constexpr Vec<Type, 4> v_quotient = v / kScalar;
        CHECK(v_quotient == get_approx_vec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Ostream operator", Type, VALID_TYPES) {
    constexpr TestArray kInput{1.0, 2.001, -3.999, 4.5};

    // Configure output resolution
    std::stringstream out;
    out << std::fixed << std::setprecision(3);

    SUBCASE("2D") {
        const std::string kExpected{"[  1.000  2.001  ]"};
        constexpr auto v = get_vec<Type, 2>(kInput);
        out << v;
        CHECK(out.str() == kExpected);
    }

    SUBCASE("3D") {
        const std::string kExpected{"[  1.000  2.001  -3.999  ]"};
        constexpr auto v = get_vec<Type, 3>(kInput);
        out << v;
        CHECK(out.str() == kExpected);
    }

    SUBCASE("4D") {
        const std::string kExpected{"[  1.000  2.001  -3.999  4.500  ]"};
        constexpr auto v = get_vec<Type, 4>(kInput);
        out << v;
        CHECK(out.str() == kExpected);
    }
}
