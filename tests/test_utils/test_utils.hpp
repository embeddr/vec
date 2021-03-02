// Utilities for unit tests

#pragma once

#include <array>

// UUT headers
#include "vec.hpp"

// Note: signed char / int8_t are technically allowed template parameters, but are highly
//       impractical due to limited resolution, and are thus omitted from these tests
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

// Helper to create vector of specified type and length from provided input array
template <size_t M, typename VecType, typename ArrayType>
constexpr Vec<M, VecType> getVec(std::array<ArrayType, kMaxSize> elems) {
    Vec<M, VecType> v;
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
