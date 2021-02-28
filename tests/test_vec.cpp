// Unit tests for the Vec class implementation

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "include/vec.hpp"
#include <array>

// Note: signed char / int8_t are technically allowed template parameters, but are highly
//       impractical due to limited resolution and are thus omitted from these tests.
#define VALID_FLOAT_TYPES  float, double, long double
#define VALID_INT_TYPES    short, int, long, long long
#define VALID_TYPES        VALID_FLOAT_TYPES, VALID_INT_TYPES

using std::size_t;
static constexpr size_t kMaxSize = 4;

// Test array type for specifying input/output data
using TestArray = std::array<long double, kMaxSize>;
using TestArrayInt = std::array<long long, kMaxSize>;

// Test vec types
using vec::Vec;
using vec::Vec4f;

// Helper to create vector of specified type and length from provided input array
template <size_t M, typename VecType, typename ArrayType>
constexpr Vec<M, VecType> getVec(std::array<ArrayType, kMaxSize> elems) {
    Vec<M, VecType> v{};
    for (size_t i = 0; i < M; i++) {
        v[i] = static_cast<VecType>(elems[i]);
    }
    return v;
}

TEST_CASE("Basic checks to enable other tests") {
    SUBCASE("Element access with []") {
       // Helper getVec() below requires operator[] to set values
        constexpr int kScale = 3; // arbitrary
        Vec<kMaxSize, int> v{1, 2, 3, 4};
        for (size_t i = 0; i < kMaxSize; i++) {
            CHECK(v[i] == (i + 1));
            v[i] *= 3;
            CHECK(v[i] == ((i + 1) * 3));
        }
    }

    SUBCASE("Fixed-point vector (in)equality") {
        // Many tests utilize Vec comparison operators
        constexpr Vec<kMaxSize, int> v1{5, -6, 7, 0};
        constexpr Vec<kMaxSize, int> v2{5, -6, 7, 0};
        CHECK(v1 == v2);
        CHECK_FALSE(v1 != v2);

        for (size_t i = 0; i < kMaxSize; i++) {
            Vec<kMaxSize, int> v2_mod = v2;
            v2_mod[i] += 1;
            CHECK(v1 != v2_mod);
            CHECK_FALSE(v1 == v2_mod);
        }
    }

    SUBCASE("Floating-point vector (in)equality") {
        // Many tests utilize Vec comparison operators
        constexpr Vec<kMaxSize, float> v1{5.1F, -6.0F, 0.0F, 8.99F};
        constexpr Vec<kMaxSize, float> v2{5.1F, -6.0F, 0.0F, 8.99F};
        CHECK(v1 == v2);
        CHECK_FALSE(v1 != v2);

        for (size_t i = 0; i < kMaxSize; i++) {
            Vec<kMaxSize, float> v2_mod = v2;
            v2_mod[i] += 1;
            CHECK(v1 != v2_mod);
            CHECK_FALSE(v1 == v2_mod);
        }
    }

    SUBCASE("Helper getVec()") {
        // Many tests utilize the getVec() helper to get vectors from test value arrays
        constexpr TestArray kFloatTestValues{1.5L, -2.1L, 3.3L, 4.0L};
        constexpr auto v_float = getVec<4, float>(kFloatTestValues);
        for (int i = 0; i < kMaxSize; i++) {
            CHECK(v_float[i] == doctest::Approx(kFloatTestValues[i]));
        }

        constexpr TestArrayInt kIntTestValues{1, 2, 3, 4};
        constexpr auto v_int = getVec<4, int>(kIntTestValues);
        for (int i = 0; i < kMaxSize; i++) {
            CHECK(v_int[i] == kIntTestValues[i]);
        }
    }
}

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

TEST_CASE_TEMPLATE("Access elements by []", Type, VALID_TYPES) {
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

TEST_CASE_TEMPLATE("Vector += vector (float)", Type, VALID_FLOAT_TYPES) {
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

TEST_CASE_TEMPLATE("Vector += vector (int)", Type, VALID_INT_TYPES) {
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

TEST_CASE_TEMPLATE("Vector -= vector (float)", Type, VALID_FLOAT_TYPES) {
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

TEST_CASE_TEMPLATE("Vector -= vector (int)", Type, VALID_INT_TYPES) {
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

TEST_CASE_TEMPLATE("Test vector *= scalar (float)", Type, VALID_FLOAT_TYPES) {
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

TEST_CASE_TEMPLATE("Test vector *= scalar (int)", Type, VALID_INT_TYPES) {
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

TEST_CASE_TEMPLATE("Test vector /= scalar (float)", Type, VALID_FLOAT_TYPES) {
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

TEST_CASE_TEMPLATE("Test vector /= scalar (int)", Type, VALID_INT_TYPES) {
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

TEST_CASE_TEMPLATE("Test -vector", Type, VALID_TYPES) {
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

TEST_CASE_TEMPLATE("Test vector ==/!= vector (float)", Type, VALID_FLOAT_TYPES) {
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

TEST_CASE_TEMPLATE("Test vector ==/!= vector (int)", Type, VALID_INT_TYPES) {
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

TEST_CASE_TEMPLATE("Vector - vector (float)", Type, VALID_FLOAT_TYPES) {
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

TEST_CASE_TEMPLATE("Vector - vector (int)", Type, VALID_INT_TYPES) {
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

TEST_CASE_TEMPLATE("Test vector + vector (float)", Type, VALID_FLOAT_TYPES) {
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

TEST_CASE_TEMPLATE("Test vector + vector (int)", Type, VALID_INT_TYPES) {
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

TEST_CASE_TEMPLATE("Test vector * scalar (float)", Type, VALID_FLOAT_TYPES) {
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

TEST_CASE_TEMPLATE("Test vector * scalar (int)", Type, VALID_INT_TYPES) {
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

TEST_CASE_TEMPLATE("Test vector / scalar (float)", Type, VALID_FLOAT_TYPES) {
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

TEST_CASE_TEMPLATE("Test vector / scalar (int)", Type, VALID_INT_TYPES) {
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

// TODO: Test ostream operator

TEST_CASE("Test dot product") {
    constexpr Vec4f v1{1.0f, 2.0f, 3.0f, 4.0f};
    constexpr Vec4f v2{-5.0f, 6.0f, 7.0f, 8.0f};

    SUBCASE("Arbitrary") {
        constexpr auto v1_dot_v2 = dot(v1, v2);
        CHECK(v1_dot_v2 == doctest::Approx(60.0f));
    }
    SUBCASE("Arbitrary reverse order") {
        constexpr auto v2_dot_v1 = dot(v2, v1);
        CHECK(v2_dot_v1 == doctest::Approx(60.0f));
    }
    SUBCASE("Arbitrary and zero") {
        constexpr Vec4f v_zero{};
        CHECK(dot(v1, v_zero) == doctest::Approx(0.0f));
    }
    SUBCASE("Arbitrary and orthogonal") {
        constexpr Vec4f v_orthogonal{2.0f, -1.0f, 0.0f, 0.0f};
        CHECK(dot(v1, v_orthogonal) == doctest::Approx(0.0f));
    }
}

// TODO: Test cross product for Vec3f (only defined for 3D vectors)

TEST_CASE("Project onto") {
    constexpr Vec4f v1{1.0f, 2.0f, 3.0f, 4.0f};
    constexpr Vec4f v2{-5.0f, 6.0f, 7.0f, 8.0f};
    constexpr auto v1_proj_v2 = project_onto(v1, v2);
    CHECK(v1_proj_v2[0] == doctest::Approx(-1.72414f));
    CHECK(v1_proj_v2[1] == doctest::Approx(2.06897f));
    CHECK(v1_proj_v2[2] == doctest::Approx(2.41379f));
    CHECK(v1_proj_v2[3] == doctest::Approx(2.75862f));
}

TEST_CASE("Project onto unit") {
    constexpr Vec4f v1{1.0f, 2.0f, 3.0f, 4.0f};
    constexpr Vec4f v2{0.0f, 1.0f, 0.0f, 0.0f};
    constexpr auto v1_proj_unit_v2 = project_onto_unit(v1, v2);
    CHECK(v1_proj_unit_v2[0] == doctest::Approx(0.0f));
    CHECK(v1_proj_unit_v2[1] == doctest::Approx(2.0f));
    CHECK(v1_proj_unit_v2[2] == doctest::Approx(0.0f));
    CHECK(v1_proj_unit_v2[3] == doctest::Approx(0.0f));
}

TEST_CASE("Reject from") {
    constexpr Vec4f v1{1.0f, 2.0f, 3.0f, 4.0f};
    constexpr Vec4f v2{-5.0f, 6.0f, 7.0f, 8.0f};
    constexpr auto v1_rej_v2 = reject_from(v1, v2);
    CHECK(v1_rej_v2[0] == doctest::Approx(2.72414f));
    CHECK(v1_rej_v2[1] == doctest::Approx(-0.06897f));
    CHECK(v1_rej_v2[2] == doctest::Approx(0.58621f));
    CHECK(v1_rej_v2[3] == doctest::Approx(1.24138f));
}

TEST_CASE("Reject from unit") {
    constexpr Vec4f v1{1.0f, 2.0f, 3.0f, 4.0f};
    constexpr Vec4f v2{0.0f, 1.0f, 0.0f, 0.0f};
    constexpr auto v1_rej_unit_v2 = reject_from_unit(v1, v2);
    CHECK(v1_rej_unit_v2[0] == doctest::Approx(1.0f));
    CHECK(v1_rej_unit_v2[1] == doctest::Approx(0.0f));
    CHECK(v1_rej_unit_v2[2] == doctest::Approx(3.0f));
    CHECK(v1_rej_unit_v2[3] == doctest::Approx(4.0f));
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

TEST_CASE_TEMPLATE("Manhattan distance (float)", Type, VALID_FLOAT_TYPES) {
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
        CHECK(v.manhattan() == doctest::Approx(2.5L));
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<4, Type>(kInput);
        constexpr Type len = v.manhattan();
        CHECK(len == doctest::Approx(5.5L));
        CHECK(v.manhattan() == doctest::Approx(5.5L));
    }
}

TEST_CASE_TEMPLATE("Manhattan distance (int)", Type, VALID_INT_TYPES) {
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
        CHECK(v.manhattan() == 3);
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<4, Type>(kInput);
        constexpr Type len = v.manhattan();
        CHECK(len == 8);
        CHECK(v.manhattan() == 8);
    }
}

TEST_CASE_TEMPLATE("Euclidean norm (float)", Type, VALID_FLOAT_TYPES) {
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
        CHECK(v.euclidean() == doctest::Approx(2.13775L));
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<4, Type>(kInput);
        constexpr Type len = v.euclidean();
        CHECK(len == doctest::Approx(3.68374L));
        CHECK(v.euclidean() == doctest::Approx(3.68374L));
    }
}

TEST_CASE_TEMPLATE("Euclidean norm (int)", Type, VALID_INT_TYPES) {
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
        CHECK(v.euclidean() == 2);
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<4, Type>(kInput);
        constexpr Type len = v.euclidean();
        CHECK(len == 5);
        CHECK(v.euclidean() == 5);
    }
}

TEST_CASE_TEMPLATE("Euclidean norm squared (float)", Type, VALID_FLOAT_TYPES) {
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
        CHECK(v.euclidean2() == doctest::Approx(4.57L));
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<4, Type>(kInput);
        constexpr Type len2 = v.euclidean2();
        CHECK(len2 == doctest::Approx(13.57L));
        CHECK(v.euclidean2() == doctest::Approx(13.57L));
    }
}

TEST_CASE_TEMPLATE("Euclidean norm squared (int)", Type, VALID_INT_TYPES) {
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
        CHECK(v.euclidean2() == 5);
    }

    SUBCASE("4D") {
        constexpr auto v = getVec<4, Type>(kInput);
        constexpr Type len2 = v.euclidean2();
        CHECK(len2 == 30);
        CHECK(v.euclidean2() == 30);
    }
}

TEST_CASE_TEMPLATE("Normalize (float)", Type) {
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
        CHECK(v.normalize() == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr TestArray kExpected{0.10859L, -0.57007L, 0.0L, -0.81439L};
        constexpr auto v = getVec<4, Type>();
        constexpr Vec<4, Type> v_normalized = v.normalize();
        CHECK(v_normalized == getVec<4, Type>(kExpected));
        CHECK(v.normalize() == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Normalize (int)", Type, VALID_INT_TYPES) {
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
        CHECK(v.normalize(kLength) == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr TestArrayInt kExpected{9, 18, 27, 37};
        constexpr auto v = getVec<4, Type>(kInput);
        constexpr Vec<4, Type> v_normalized = v.normalize(kLength);
        CHECK(v_normalized == getVec<4, Type>(kExpected));
        CHECK(v.normalize(kLength) == getVec<4, Type>(kExpected));
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