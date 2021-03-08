// Unit tests for the Vec class implementation

// Testing headers
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "test_utils_vec.hpp"

// UUT headers
#include "vec.hpp"

TEST_CASE_TEMPLATE("Construct zero vector", Type, VALID_TYPES) {
    // Shared expected output data:
    constexpr TestArray kExpected{0.0L, 0.0L, 0.0L, 0.0L};

    SUBCASE("2D") {
        constexpr Vec<Type, 2> v{};
        CHECK(v == getVec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr Vec<Type, 3> v{};
        CHECK(v == getVec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr Vec<Type, 4> v{};
        CHECK(v == getVec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Construct vector from elements", Type, VALID_TYPES) {
    // Shared expected output data:
    constexpr TestArray kExpected{1.0L, 2.0L, 3.0L, 4.0L};

    SUBCASE("2D") {
        constexpr Vec<Type, 2> v{static_cast<Type>(1),
                                 static_cast<Type>(2)};
        CHECK(v == getVec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr Vec<Type, 3> v{static_cast<Type>(1),
                                 static_cast<Type>(2),
                                 static_cast<Type>(3)};
        CHECK(v == getVec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr Vec<Type, 4> v{static_cast<Type>(1),
                                 static_cast<Type>(2),
                                 static_cast<Type>(3),
                                 static_cast<Type>(4)};
        CHECK(v == getVec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Construct vector from other vector", Type, VALID_TYPES) {
    // Shared expected output data:
    constexpr TestArray kInput{1.0L, 2.0L, 3.0L, 4.0L};
    constexpr TestArray kExpected{1.0L, 2.0L, 3.0L, 4.0L};

    SUBCASE("2D") {
        constexpr auto v = getVec<Type, 2>(kInput);
        constexpr Vec<Type, 2> v_copy{v};
        CHECK(v_copy == getVec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v = getVec<Type, 3>(kInput);
        constexpr Vec<Type, 3> v_copy{v};
        CHECK(v_copy == getVec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<Type, 4>(kInput);
        constexpr Vec<Type, 4> v_copy{v};
        CHECK(v_copy == getVec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Construct vector from single element fill", Type, VALID_TYPES) {
    // Shared input and expected output data:
    constexpr Type kFillValue{static_cast<Type>(123.0L)};
    constexpr TestArray kExpected{123.0L, 123.0L, 123.0L, 123.0L};

    SUBCASE("2D") {
        constexpr Vec<Type, 2> v_fill{kFillValue};
        CHECK(v_fill == getVec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr Vec<Type, 3> v_fill{kFillValue};
        CHECK(v_fill == getVec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr Vec<Type, 4> v_fill{kFillValue};
        CHECK(v_fill == getVec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Construct unit vector i", Type, VALID_TYPES) {
    // Shared expected output data:
    constexpr TestArray kExpected{1.0L, 0.0L, 0.0L, 0.0L};

    SUBCASE("2D") {
        constexpr auto v_i = Vec<Type, 2>::i();
        CHECK(v_i == getVec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v_i = Vec<Type, 3>::i();
        CHECK(v_i == getVec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v_i = Vec<Type, 4>::i();
        CHECK(v_i == getVec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Construct unit vector j", Type, VALID_TYPES) {
    // Shared expected output data:
    constexpr TestArray kExpected{0.0L, 1.0L, 0.0L, 0.0L};

    SUBCASE("2D") {
        constexpr auto v_j = Vec<Type, 2>::j();
        CHECK(v_j == getVec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr auto v_j = Vec<Type, 3>::j();
        CHECK(v_j == getVec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v_j = Vec<Type, 4>::j();
        CHECK(v_j == getVec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Construct unit vector k", Type, VALID_TYPES) {
    // Shared expected output data:
    constexpr TestArray kExpected{0.0L, 0.0L, 1.0L, 0.0L};

    SUBCASE("2D") {
        // Cannot represent unit vector k with a 2D vector
    }

    SUBCASE("3D") {
        constexpr auto v_k = Vec<Type, 3>::k();
        CHECK(v_k == getVec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr auto v_k = Vec<Type, 4>::k();
        CHECK(v_k == getVec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Access elements by index with at()", Type, VALID_TYPES) {
    // Shared input data:
    constexpr TestArray kInput{1.0L, 2.0L, 3.0L, 4.0L};
    constexpr Type kOffset{static_cast<Type>(7)}; // arbitrary

    SUBCASE("2D") {
        auto v = getVec<Type, 2>(kInput);
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
        auto v = getVec<Type, 3>(kInput);
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
        auto v = getVec<Type, 4>(kInput);
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
        auto v = getVec<Type, 2>(kInput);
        for (Type& elem : v) { // uses begin() and end()
            elem = kValue;
        }
        CHECK(v == getVec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        auto v = getVec<Type, 3>(kInput);
        for (Type& elem : v) { // uses begin() and end()
            elem = kValue;
        }
        CHECK(v == getVec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        auto v = getVec<Type, 4>(kInput);
        for (Type& elem : v) { // uses begin() and end()
            elem = kValue;
        }
        CHECK(v == getVec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Begin/end const iterator access", Type, VALID_TYPES) {
    // Shared input data:
    constexpr TestArray kInput{1.0L, 2.0L, 3.0L, 4.0L};

    SUBCASE("2D") {
        auto v = getVec<Type, 2>(kInput);
        CHECK(std::accumulate(v.cbegin(), v.cend(), 0) == doctest::Approx(3.0L));
    }

    SUBCASE("3D") {
        auto v = getVec<Type, 3>(kInput);
        CHECK(std::accumulate(v.cbegin(), v.cend(), 0) == doctest::Approx(6.0L));
    }

    SUBCASE("4D") {
        auto v = getVec<Type, 4>(kInput);
        CHECK(std::accumulate(v.cbegin(), v.cend(), 0) == doctest::Approx(10.0L));
    }
}

TEST_CASE_TEMPLATE("Access elements by named x,y,z,w accessors", Type, VALID_TYPES) {
    // Shared input data:
    constexpr TestArray kInput{1.0L, 2.0L, 3.0L, 4.0L};

    SUBCASE("2D") {
        constexpr auto v = getVec<Type, 2>(kInput);
        CHECK(v.x() == doctest::Approx(1.0L));
        CHECK(v.y() == doctest::Approx(2.0L));
        // Accessors for z and w are not available for 2D vectors
    }

    SUBCASE("3D") {
        constexpr auto v = getVec<Type, 3>(kInput);
        CHECK(v.x() == doctest::Approx(1.0L));
        CHECK(v.y() == doctest::Approx(2.0L));
        CHECK(v.z() == doctest::Approx(3.0L));
        // Accessor for w is not available for 3D vectors
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<Type, 4>(kInput);
        CHECK(v.x() == doctest::Approx(1.0L));
        CHECK(v.y() == doctest::Approx(2.0L));
        CHECK(v.z() == doctest::Approx(3.0L));
        CHECK(v.w() == doctest::Approx(4.0L));
    }
}

TEST_CASE_TEMPLATE("Size", Type, VALID_TYPES) {
    SUBCASE("2D") {
        constexpr Vec<Type, 2> v{};
        CHECK(v.size() == 2);
    }

    SUBCASE("3D") {
        constexpr Vec<Type, 3> v{};
        CHECK(v.size() == 3);
    }

    SUBCASE("4D") {
        constexpr Vec<Type, 4> v{};
        CHECK(v.size() == 4);
    }
}

TEST_CASE_TEMPLATE("Manhattan norm", Type, VALID_TYPES) {
    // Shared input data:
    constexpr TestArray kInput{0.4L, -2.1L, 0.0L, -3.0L};

    SUBCASE("2D") {
        constexpr auto v = getVec<Type, 2>(kInput);
        constexpr Type len = v.manhattan();
        CHECK(len == doctest::Approx(2.5L));
        CHECK(v.manhattan() == doctest::Approx(2.5L)); // non-constexpr use
    }

    SUBCASE("3D") {
        constexpr auto v = getVec<Type, 3>(kInput);
        constexpr Type len = v.manhattan();
        CHECK(len == doctest::Approx(2.5L));
        CHECK(v.manhattan() == doctest::Approx(2.5L)); // non-constexpr use
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<Type, 4>(kInput);
        constexpr Type len = v.manhattan();
        CHECK(len == doctest::Approx(5.5L));
        CHECK(v.manhattan() == doctest::Approx(5.5L)); // non-constexpr use
    }
}

TEST_CASE_TEMPLATE("Euclidean norm", Type, VALID_TYPES) {
    // Shared input data:
    constexpr TestArray kInput{0.4L, -2.1L, 0.0L, -3.0L};

    SUBCASE("2D") {
        constexpr auto v = getVec<Type, 2>(kInput);
        constexpr Type len = v.euclidean();
        CHECK(len == doctest::Approx(2.13775L));
        CHECK(v.euclidean() == doctest::Approx(2.13775L)); // non-constexpr use
    }

    SUBCASE("3D") {
        constexpr auto v = getVec<Type, 3>(kInput);
        constexpr Type len = v.euclidean();
        CHECK(len == doctest::Approx(2.13775L));
        CHECK(v.euclidean() == doctest::Approx(2.13775L)); // non-constexpr use
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<Type, 4>(kInput);
        constexpr Type len = v.euclidean();
        CHECK(len == doctest::Approx(3.68374L));
        CHECK(v.euclidean() == doctest::Approx(3.68374L)); // non-constexpr use
    }
}

TEST_CASE_TEMPLATE("Euclidean norm squared", Type, VALID_TYPES) {
    // Shared input data:
    constexpr TestArray kInput{0.4L, -2.1L, 0.0L, -3.0L};

    SUBCASE("2D") {
        constexpr auto v = getVec<Type, 2>(kInput);
        constexpr Type len2 = v.euclidean2();
        CHECK(len2 == doctest::Approx(4.57L));
        CHECK(v.euclidean2() == doctest::Approx(4.57L)); // non-constexpr use
    }

    SUBCASE("3D") {
        constexpr auto v = getVec<Type, 3>(kInput);
        constexpr Type len2 = v.euclidean2();
        CHECK(len2 == doctest::Approx(4.57L));
        CHECK(v.euclidean2() == doctest::Approx(4.57L)); // non-constexpr use
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<Type, 4>(kInput);
        constexpr Type len2 = v.euclidean2();
        CHECK(len2 == doctest::Approx(13.57L));
        CHECK(v.euclidean2() == doctest::Approx(13.57L)); // non-constexpr use
    }
}

TEST_CASE_TEMPLATE("Normalize", Type, VALID_TYPES) {
    // Shared input data:
    constexpr TestArray kInput{0.45L, -2.1L, 0.0L, -3.0L};

    // TODO: Test non-default desired length

    SUBCASE("2D") {
        constexpr TestArray kExpected{0.209529088730873460806321L,
                                      -0.977802414077409483771867L};
        constexpr auto v = getVec<Type, 2>(kInput);
        constexpr Vec<Type, 2> v_normalized = v.normalize();
        CHECK(v_normalized == getVec<Type, 2>(kExpected));
        CHECK(v.normalize() == getVec<Type, 2>(kExpected)); // non-constexpr use
    }

    SUBCASE("3D") {
        constexpr TestArray kExpected{0.209529088730873460806321L,
                                      -0.977802414077409483771867L,
                                      0.000000000000000000000000L};
        constexpr auto v = getVec<Type, 3>(kInput);
        constexpr Vec<Type, 3> v_normalized = v.normalize();
        CHECK(v_normalized == getVec<Type, 3>(kExpected));
        CHECK(v.normalize() == getVec<Type, 3>(kExpected)); // non-constexpr use
    }

    SUBCASE("4D") {
        constexpr TestArray kExpected{0.121967344227261256164733L,
                                      -0.569180939727219195448972L,
                                      0.000000000000000000000000L,
                                      -0.813115628181741707791990L};

        constexpr auto v = getVec<Type, 4>(kInput);
        constexpr Vec<Type, 4> v_normalized = v.normalize();
        CHECK(v_normalized == getVec<Type, 4>(kExpected));
        CHECK(v.normalize() == getVec<Type, 4>(kExpected)); // non-constexpr use
    }
}

TEST_CASE_TEMPLATE("Normalize in-place", Type, VALID_TYPES) {
    // Shared input data:
    constexpr TestArray kInput{0.45L, -2.1L, 0.0L, -3.0L};

    // TODO: Test non-default desired length

    SUBCASE("2D") {
        constexpr TestArray kExpected{0.209529088730873460806321L,
                                      -0.977802414077409483771867L};
        auto v = getVec<Type, 2>(kInput);
        v.normalize_in_place();
        CHECK(v == getVec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr TestArray kExpected{0.209529088730873460806321L,
                                      -0.977802414077409483771867L,
                                      0.000000000000000000000000L};
        auto v = getVec<Type, 3>(kInput);
        v.normalize_in_place();
        CHECK(v == getVec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr TestArray kExpected{0.121967344227261256164733L,
                                      -0.569180939727219195448972L,
                                      0.000000000000000000000000L,
                                      -0.813115628181741707791990L};

        auto v = getVec<Type, 4>(kInput);
        v.normalize_in_place();
        CHECK(v == getVec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Fill", Type, VALID_TYPES) {
    // Shared input and expected output data
    constexpr Type kFillValue{static_cast<Type>(123.0L)};
    constexpr TestArray kExpected{123.0L, 123.0L, 123.0L, 123.0L};

    SUBCASE("2D") {
        Vec<Type, 2> v{};
        WARN(v != getVec<Type, 2>(kExpected));
        v.fill(kFillValue);
        CHECK(v == getVec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        Vec<Type, 3> v{};
        WARN(v != getVec<Type, 3>(kExpected));
        v.fill(kFillValue);
        CHECK(v == getVec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        Vec<Type, 4> v{};
        WARN(v != getVec<Type, 4>(kExpected));
        v.fill(kFillValue);
        CHECK(v == getVec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Clear", Type, VALID_TYPES) {
    // Shared input and expected output data
    constexpr Type kFillValue{static_cast<Type>(123.0L)};
    constexpr TestArray kExpected{0.0L, 0.0L, 0.0L, 0.0L};

    SUBCASE("2D") {
       Vec<Type, 2> v{kFillValue};
       WARN(v != getVec<Type, 2>(kExpected));
       v.clear();
       CHECK(v == getVec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        Vec<Type, 3> v{kFillValue};
        WARN(v != getVec<Type, 3>(kExpected));
        v.clear();
        CHECK(v == getVec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        Vec<Type, 4> v{kFillValue};
        WARN(v != getVec<Type, 4>(kExpected));
        v.clear();
        CHECK(v == getVec<Type, 4>(kExpected));
    }
}
