// Utilities for vector unit tests

#pragma once

#include <array>

// Testing headers
#include "doctest.h"

// UUT headers
#include "vec.hpp"

#define VALID_TYPES  float, double, long double

using std::size_t;
using vec::Vec;
static constexpr size_t kMaxSize = 4;

// Test array type for specifying input/output data
using TestArray = std::array<long double, kMaxSize>;

// Helper to create vector of specified type and size from provided input array
template <typename Type, size_t M>
constexpr Vec<Type, M> getVec(TestArray elems) {
    Vec<Type, M> v;
    for (size_t i = 0; i < M; i++) {
        v[i] = static_cast<Type>(elems[i]);
    }
    return v;
}

// Vec test guidelines:
//  * Use TEST_CASE_TEMPLATE with VALID_TYPES
//  * Define constexpr TestArray values for test inputs and output expectations
//  * Where appropriate, define SUBCASE sections for 2D, 3D, and 4D vectors
//      * Utilize getVec helper to get appropriately-sized vectors from TestArray values
//      * If implementations are not specialized on size, default to testing 4D vectors
//  * Exercise operations in a fully constexpr form wherever possible
//      * If the constexpr and non-constexpr implementations differ, test both

TEST_CASE("Basic checks to enable other tests") {
    SUBCASE("Element access with []") {
        // Helper getVec() above requires operator[] to set values
        constexpr float kScale = 3.0F; // arbitrary
        Vec<float, kMaxSize> v{0.0F, 1.0F, 2.0F, 3.0F};
        for (size_t i = 0; i < kMaxSize; i++) {
            CHECK(v[i] == doctest::Approx(i));
            v[i] *= kScale;
            CHECK(v[i] == doctest::Approx(i * kScale));
        }
    }

    SUBCASE("Floating-point vector (in)equality") {
        constexpr Vec<float, kMaxSize> v1{5.1F, -6.024F, 0.0F, 8.99F};
        constexpr Vec<float, kMaxSize> v2{5.1F, -6.024F, 0.0F, 8.99F};
        constexpr float kDelta = 0.001F;
        CHECK(v1 == v2);
        CHECK_FALSE(v1 != v2);

        for (size_t i = 0; i < kMaxSize; i++) {
            Vec<float, kMaxSize> v2_mod = v2;
            v2_mod[i] += kDelta;
            CHECK(v1 != v2_mod);
            CHECK_FALSE(v1 == v2_mod);
        }
    }

    SUBCASE("Helper getVec()") {
        constexpr TestArray kFloatTestValues{1.5L, -2.1L, 3.3L, 4.0L};
        constexpr auto v = getVec<float, kMaxSize>(kFloatTestValues);
        for (size_t i = 0; i < kMaxSize; i++) {
            CHECK(v[i] == doctest::Approx(kFloatTestValues[i]));
        }
    }
}
