// Unit tests for the Vec class implementation

// Testing headers
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "test_utils.hpp"

// UUT headers
#include "vec.hpp"

TEST_CASE_TEMPLATE("Construct zero vector", Type, VALID_TYPES) {
    // Shared expected output data:
    constexpr TestArray kExpected{0.0L, 0.0L, 0.0L, 0.0L};

    SUBCASE("2D") {
        constexpr Vec<2, Type> v{};
        CHECK(v == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr Vec<3, Type> v{};
        CHECK(v == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr Vec<4, Type> v{};
        CHECK(v == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Construct vector from elements", Type, VALID_TYPES) {
    // Shared expected output data:
    constexpr TestArray kExpected{1.0L, 2.0L, 3.0L, 4.0L};

    SUBCASE("2D") {
        constexpr Vec<2, Type> v{static_cast<Type>(1),
                                 static_cast<Type>(2)};
        CHECK(v == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr Vec<3, Type> v{static_cast<Type>(1),
                                 static_cast<Type>(2),
                                 static_cast<Type>(3)};
        CHECK(v == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr Vec<4, Type> v{static_cast<Type>(1),
                                 static_cast<Type>(2),
                                 static_cast<Type>(3),
                                 static_cast<Type>(4)};
        CHECK(v == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Construct vector from vector", Type, VALID_TYPES) {
    // Shared expected output data:
    constexpr TestArray kInput{1.0L, 2.0L, 3.0L, 4.0L};
    constexpr TestArray kExpected{1.0L, 2.0L, 3.0L, 4.0L};

    SUBCASE("2D") {
        constexpr auto v_in = getVec<2, Type>(kInput);
        constexpr Vec<2, Type> v_copy{v_in};
        CHECK(v_copy == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v_in = getVec<3, Type>(kInput);
        constexpr Vec<3, Type> v_copy{v_in};
        CHECK(v_copy == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v_in = getVec<4, Type>(kInput);
        constexpr Vec<4, Type> v_copy{v_in};
        CHECK(v_copy == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Construct vector from single element fill", Type, VALID_TYPES) {
    // Shared input and expected output data:
    constexpr Type kFillValue{static_cast<Type>(123.0L)};
    constexpr TestArray kExpected{123.0L, 123.0L, 123.0L, 123.0L};

    SUBCASE("2D") {
        constexpr Vec<2, Type> v_fill{kFillValue};
        CHECK(v_fill == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr Vec<3, Type> v_fill{kFillValue};
        CHECK(v_fill == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr Vec<4, Type> v_fill{kFillValue};
        CHECK(v_fill == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Construct unit vector i", Type, VALID_TYPES) {
    // Shared expected output data:
    constexpr TestArray kExpected{1.0L, 0.0L, 0.0L, 0.0L};

    SUBCASE("2D") {
        constexpr auto v_i = Vec<2, Type>::i();
        CHECK(v_i == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v_i = Vec<3, Type>::i();
        CHECK(v_i == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v_i = Vec<4, Type>::i();
        CHECK(v_i == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Construct unit vector j", Type, VALID_TYPES) {
    // Shared expected output data:
    constexpr TestArray kExpected{0.0L, 1.0L, 0.0L, 0.0L};

    SUBCASE("2D") {
        constexpr auto v_j = Vec<2, Type>::j();
        CHECK(v_j == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v_j = Vec<3, Type>::j();
        CHECK(v_j == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v_j = Vec<4, Type>::j();
        CHECK(v_j == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Construct unit vector k", Type, VALID_TYPES) {
    // Shared expected output data:
    constexpr TestArray kExpected{0.0L, 0.0L, 1.0L, 0.0L};

    SUBCASE("2D") {
        // Cannot represent unit vector k with a 2D vector
    }

    SUBCASE("3D") {
        constexpr auto v_k = Vec<3, Type>::k();
        CHECK(v_k == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v_k = Vec<4, Type>::k();
        CHECK(v_k == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Access elements by index with at()", Type, VALID_TYPES) {
    // Shared input data:
    constexpr TestArray kInput{1.0L, 2.0L, 3.0L, 4.0L};
    constexpr Type kOffset{static_cast<Type>(7)}; // arbitrary

    SUBCASE("2D") {
        auto v = getVec<2, Type>(kInput);
        for (size_t i = 0; i < 2; i++) {
            // Read, write and read again
            CHECK(v.at(i) == kInput.at(i));
            v.at(i) = i + kOffset;
            CHECK(v.at(i) == i + kOffset);
        }
        // Out-of-bounds
        CHECK_THROWS(v.at(2) = 0);
    }

    SUBCASE("3D") {
        auto v = getVec<3, Type>(kInput);
        for (size_t i = 0; i < 3; i++) {
            // Read, write and read again
            CHECK(v.at(i) == kInput.at(i));
            v.at(i) = i + kOffset;
            CHECK(v.at(i) == i + kOffset);
        }
        // Out-of-bounds
        CHECK_THROWS(v.at(3) = 0);
    }

    SUBCASE("4D") {
        auto v = getVec<4, Type>(kInput);
        for (size_t i = 0; i < 4; i++) {
            // Read, write and read again
            CHECK(v.at(i) == kInput.at(i));
            v.at(i) = i + kOffset;
            CHECK(v.at(i) == i + kOffset);
        }
        // Out-of-bounds
        CHECK_THROWS(v.at(4) = 0);
    }
}

TEST_CASE_TEMPLATE("Begin/end iterator access", Type, VALID_TYPES) {
    // Shared input data:
    constexpr TestArray kInput{1.0L, 2.0L, 3.0L, 4.0L};
    constexpr Type kValue{static_cast<Type>(7)}; // arbitrary
    constexpr TestArray kExpected{7.0L, 7.0L, 7.0L, 7.0L};

    SUBCASE("2D") {
        auto v = getVec<2, Type>(kInput);
        for (Type& elem : v) { // uses begin() and end()
            elem = kValue;
        }
        CHECK(v == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        auto v = getVec<3, Type>(kInput);
        for (Type& elem : v) { // uses begin() and end()
            elem = kValue;
        }
        CHECK(v == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        auto v = getVec<4, Type>(kInput);
        for (Type& elem : v) { // uses begin() and end()
            elem = kValue;
        }
        CHECK(v == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Begin/end const iterator access", Type, VALID_TYPES) {
    // Shared input data:
    constexpr TestArray kInput{1.0L, 2.0L, 3.0L, 4.0L};

    SUBCASE("2D") {
        auto v = getVec<2, Type>(kInput);
        CHECK(std::accumulate(v.cbegin(), v.cend(), 0) == doctest::Approx(3.0L));
    }

    SUBCASE("3D") {
        auto v = getVec<3, Type>(kInput);
        CHECK(std::accumulate(v.cbegin(), v.cend(), 0) == doctest::Approx(6.0L));
    }

    SUBCASE("4D") {
        auto v = getVec<4, Type>(kInput);
        CHECK(std::accumulate(v.cbegin(), v.cend(), 0) == doctest::Approx(10.0L));
    }
}

TEST_CASE_TEMPLATE("Access elements by named x,y,z,w accessors", Type, VALID_TYPES) {
    // Shared input data:
    constexpr TestArray kInput{1.0L, 2.0L, 3.0L, 4.0L};

    SUBCASE("2D") {
        constexpr auto v = getVec<2, Type>(kInput);
        CHECK(v.x() == doctest::Approx(1.0L));
        CHECK(v.y() == doctest::Approx(2.0L));
        // Accessors for z and w are not available for 2D vectors
    }

    SUBCASE("3D") {
        constexpr auto v = getVec<3, Type>(kInput);
        CHECK(v.x() == doctest::Approx(1.0L));
        CHECK(v.y() == doctest::Approx(2.0L));
        CHECK(v.z() == doctest::Approx(3.0L));
        // Accessor for w is not available for 3D vectors
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<4, Type>(kInput);
        CHECK(v.x() == doctest::Approx(1.0L));
        CHECK(v.y() == doctest::Approx(2.0L));
        CHECK(v.z() == doctest::Approx(3.0L));
        CHECK(v.w() == doctest::Approx(4.0L));
    }
}

TEST_CASE_TEMPLATE("Size", Type, VALID_TYPES) {
    SUBCASE("2D") {
        constexpr Vec<2, Type> v{};
        CHECK(v.size() == 2);
    }

    SUBCASE("3D") {
        constexpr Vec<3, Type> v{};
        CHECK(v.size() == 3);
    }

    SUBCASE("4D") {
        constexpr Vec<4, Type> v{};
        CHECK(v.size() == 4);
    }
}

TEST_CASE_TEMPLATE("Manhattan distance (floating-point)", Type, VALID_FLOAT_TYPES) {
    // Shared input data:
    constexpr TestArray kInput{0.4L, -2.1L, 0.0L, -3.0L};

    SUBCASE("2D") {
        constexpr auto v = getVec<2, Type>(kInput);
        constexpr Type len = v.manhattan();
        CHECK(len == doctest::Approx(2.5L));
        CHECK(v.manhattan() == doctest::Approx(2.5L)); // non-constexpr use
    }

    SUBCASE("3D") {
        constexpr auto v = getVec<3, Type>(kInput);
        constexpr Type len = v.manhattan();
        CHECK(len == doctest::Approx(2.5L));
        CHECK(v.manhattan() == doctest::Approx(2.5L)); // non-constexpr use
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<4, Type>(kInput);
        constexpr Type len = v.manhattan();
        CHECK(len == doctest::Approx(5.5L));
        CHECK(v.manhattan() == doctest::Approx(5.5L)); // non-constexpr use
    }
}

TEST_CASE_TEMPLATE("Manhattan distance (fixed-point)", Type, VALID_INT_TYPES) {
    // Shared input data:
    constexpr TestArrayInt kInput{2, 0, -1, -5};

    SUBCASE("2D") {
        constexpr auto v = getVec<2, Type>(kInput);
        constexpr Type len = v.manhattan();
        CHECK(len == 2);
        CHECK(v.manhattan() == 2); // non-constexpr use
    }

    SUBCASE("3D") {
        constexpr auto v = getVec<3, Type>(kInput);
        constexpr Type len = v.manhattan();
        CHECK(len == 3);
        CHECK(v.manhattan() == 3); // non-constexpr use
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<4, Type>(kInput);
        constexpr Type len = v.manhattan();
        CHECK(len == 8);
        CHECK(v.manhattan() == 8); // non-constexpr use
    }
}

TEST_CASE_TEMPLATE("Euclidean norm (floating-point)", Type, VALID_FLOAT_TYPES) {
    // Shared input data:
    constexpr TestArray kInput{0.4L, -2.1L, 0.0L, -3.0L};

    SUBCASE("2D") {
        constexpr auto v = getVec<2, Type>(kInput);
        constexpr Type len = v.euclidean();
        CHECK(len == doctest::Approx(2.13775L));
        CHECK(v.euclidean() == doctest::Approx(2.13775L)); // non-constexpr use
    }

    SUBCASE("3D") {
        constexpr auto v = getVec<3, Type>(kInput);
        constexpr Type len = v.euclidean();
        CHECK(len == doctest::Approx(2.13775L));
        CHECK(v.euclidean() == doctest::Approx(2.13775L)); // non-constexpr use
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<4, Type>(kInput);
        constexpr Type len = v.euclidean();
        CHECK(len == doctest::Approx(3.68374L));
        CHECK(v.euclidean() == doctest::Approx(3.68374L)); // non-constexpr use
    }
}

TEST_CASE_TEMPLATE("Euclidean norm (fixed-point)", Type, VALID_INT_TYPES) {
    // Shared input data:
    constexpr TestArrayInt kInput{2, 0, -1, -5};

    SUBCASE("2D") {
        constexpr auto v = getVec<2, Type>(kInput);
        constexpr Type len = v.euclidean();
        CHECK(len == 2);
        CHECK(v.euclidean() == 2); // non-constexpr use
    }

    SUBCASE("3D") {
        constexpr auto v = getVec<3, Type>(kInput);
        constexpr Type len = v.euclidean();
        CHECK(len == 2);
        CHECK(v.euclidean() == 2); // non-constexpr use
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<4, Type>(kInput);
        constexpr Type len = v.euclidean();
        CHECK(len == 5);
        CHECK(v.euclidean() == 5); // non-constexpr use
    }
}

TEST_CASE_TEMPLATE("Euclidean norm squared (floating-point)", Type, VALID_FLOAT_TYPES) {
    // Shared input data:
    constexpr TestArray kInput{0.4L, -2.1L, 0.0L, -3.0L};

    SUBCASE("2D") {
        constexpr auto v = getVec<2, Type>(kInput);
        constexpr Type len2 = v.euclidean2();
        CHECK(len2 == doctest::Approx(4.57L));
        CHECK(v.euclidean2() == doctest::Approx(4.57L)); // non-constexpr use
    }

    SUBCASE("3D") {
        constexpr auto v = getVec<3, Type>(kInput);
        constexpr Type len2 = v.euclidean2();
        CHECK(len2 == doctest::Approx(4.57L));
        CHECK(v.euclidean2() == doctest::Approx(4.57L)); // non-constexpr use
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<4, Type>(kInput);
        constexpr Type len2 = v.euclidean2();
        CHECK(len2 == doctest::Approx(13.57L));
        CHECK(v.euclidean2() == doctest::Approx(13.57L)); // non-constexpr use
    }
}

TEST_CASE_TEMPLATE("Euclidean norm squared (fixed-point)", Type, VALID_INT_TYPES) {
    // Shared input data:
    constexpr TestArrayInt kInput{2, 0, -1, -5};

    SUBCASE("2D") {
        constexpr auto v = getVec<2, Type>(kInput);
        constexpr Type len2 = v.euclidean2();
        CHECK(len2 == 4);
        CHECK(v.euclidean2() == 4); // non-constexpr use
    }

    SUBCASE("3D") {
        constexpr auto v = getVec<3, Type>(kInput);
        constexpr Type len2 = v.euclidean2();
        CHECK(len2 == 5);
        CHECK(v.euclidean2() == 5); // non-constexpr use
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<4, Type>(kInput);
        constexpr Type len2 = v.euclidean2();
        CHECK(len2 == 30);
        CHECK(v.euclidean2() == 30); // non-constexpr use
    }
}

TEST_CASE_TEMPLATE("Normalize (floating-point)", Type) {
    // Shared input data:
    constexpr TestArray kInput{0.4L, -2.1L, 0.0L, -3.0L};

    SUBCASE("2D") {
        constexpr TestArray kExpected{0.18711L, -0.98234L};
        constexpr auto v = getVec<2, Type>();
        constexpr Vec<2, Type> v_normalized = v.normalize();
        CHECK(v_normalized == getVec<2, Type>(kExpected));
        CHECK(v.normalize() == getVec<2, Type>(kExpected)); // non-constexpr use
    }

    SUBCASE("3D") {
        constexpr TestArray kExpected{0.18711L, -0.98234L, 0.0L};
        constexpr auto v = getVec<3, Type>();
        constexpr Vec<3, Type> v_normalized = v.normalize();
        CHECK(v_normalized == getVec<3, Type>(kExpected));
        CHECK(v.normalize() == getVec<3, Type>(kExpected)); // non-constexpr use
    }

    SUBCASE("4D") {
        constexpr TestArray kExpected{0.10859L, -0.57007L, 0.0L, -0.81439L};
        constexpr auto v = getVec<4, Type>();
        constexpr Vec<4, Type> v_normalized = v.normalize();
        CHECK(v_normalized == getVec<4, Type>(kExpected));
        CHECK(v.normalize() == getVec<4, Type>(kExpected)); // non-constexpr use
    }
}

TEST_CASE_TEMPLATE("Normalize (fixed-point)", Type, VALID_INT_TYPES) {
    // Shared input data:
    constexpr TestArrayInt kInput{10, 20, 30, 40};
    constexpr Type kLength{50L};

    SUBCASE("2D") {
        constexpr TestArrayInt kExpected{22, 45};
        constexpr auto v = getVec<2, Type>(kInput);
        constexpr Vec<2, Type> v_normalized = v.normalize(kLength);
        CHECK(v_normalized == getVec<2, Type>(kExpected));
        CHECK(v.normalize(kLength) == getVec<2, Type>(kExpected)); // non-constexpr use
    }

    SUBCASE("3D") {
        constexpr TestArrayInt kExpected{13, 27, 40};
        constexpr auto v = getVec<3, Type>(kInput);
        constexpr Vec<3, Type> v_normalized = v.normalize(kLength);
        CHECK(v_normalized == getVec<3, Type>(kExpected));
        CHECK(v.normalize(kLength) == getVec<3, Type>(kExpected)); // non-constexpr use
    }

    SUBCASE("4D") {
        constexpr TestArrayInt kExpected{9, 18, 27, 37};
        constexpr auto v = getVec<4, Type>(kInput);
        constexpr Vec<4, Type> v_normalized = v.normalize(kLength);
        CHECK(v_normalized == getVec<4, Type>(kExpected));
        CHECK(v.normalize(kLength) == getVec<4, Type>(kExpected)); // non-constexpr use
    }
}

TEST_CASE_TEMPLATE("Fill", Type, VALID_TYPES) {
    // Shared input and expected output data
    constexpr Type kFillValue{static_cast<Type>(123.0L)};
    constexpr TestArray kExpected{123.0L, 123.0L, 123.0L, 123.0L};

    SUBCASE("2D") {
        Vec<2, Type> v{};
        WARN(v != getVec<2, Type>(kExpected));
        v.fill(kFillValue);
        CHECK(v == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        Vec<3, Type> v{};
        WARN(v != getVec<3, Type>(kExpected));
        v.fill(kFillValue);
        CHECK(v == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        Vec<4, Type> v{};
        WARN(v != getVec<4, Type>(kExpected));
        v.fill(kFillValue);
        CHECK(v == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Clear", Type, VALID_TYPES) {
    // Shared input and expected output data
    constexpr Type kFillValue{static_cast<Type>(123.0L)};
    constexpr TestArray kExpected{0.0L, 0.0L, 0.0L, 0.0L};

    SUBCASE("2D") {
       Vec<2, Type> v{kFillValue};
       WARN(v != getVec<2, Type>(kExpected));
       v.clear();
       CHECK(v == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        Vec<3, Type> v{kFillValue};
        WARN(v != getVec<3, Type>(kExpected));
        v.clear();
        CHECK(v == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        Vec<4, Type> v{kFillValue};
        WARN(v != getVec<4, Type>(kExpected));
        v.clear();
        CHECK(v == getVec<4, Type>(kExpected));
    }
}
