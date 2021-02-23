// Unit tests for the Vec class implementation

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "include/vec.hpp"

using std::size_t;
using vec::Vec4f;

// TODO: Use templates test cases to cover multiple types
// TODO: Determine a strategy for testing different vector sizes

TEST_CASE("Construct zero Vec4f") {
    constexpr Vec4f v{};
    CHECK(v[0] == 0.0f);
    CHECK(v[1] == 0.0f);
    CHECK(v[2] == 0.0f);
    CHECK(v[3] == 0.0f);
}

TEST_CASE("Construct constexpr Vec4f from elements") {
    constexpr Vec4f v{1.0f, 2.0f, 3.0f, 4.0f};
    CHECK(v[0] == 1.0f);
    CHECK(v[1] == 2.0f);
    CHECK(v[2] == 3.0f);
    CHECK(v[3] == 4.0f);
}

TEST_CASE("Construct constexpr Vec4f from other vector") {
    constexpr Vec4f v_init{1.0f, 2.0f, 3.0f, 4.0f};
    constexpr Vec4f v_copy{v_init};
    CHECK(v_copy[0] == 1.0f);
    CHECK(v_copy[1] == 2.0f);
    CHECK(v_copy[2] == 3.0f);
    CHECK(v_copy[3] == 4.0f);
}

TEST_CASE("Construct constexpr Vec4f from single element fill") {
    constexpr float kFillValue{123.0f};
    constexpr Vec4f v_fill{kFillValue};
    CHECK(v_fill[0] == kFillValue);
    CHECK(v_fill[1] == kFillValue);
    CHECK(v_fill[2] == kFillValue);
    CHECK(v_fill[3] == kFillValue);
}

TEST_CASE("Construct unit vector i") {
    constexpr auto v_i = Vec4f::i();
    CHECK(v_i[0] == 1.0f);
    CHECK(v_i[1] == 0.0f);
    CHECK(v_i[2] == 0.0f);
    CHECK(v_i[3] == 0.0f);
}

TEST_CASE("Construct unit vector j") {
    constexpr auto v_j = Vec4f::j();
    CHECK(v_j[0] == 0.0f);
    CHECK(v_j[1] == 1.0f);
    CHECK(v_j[2] == 0.0f);
    CHECK(v_j[3] == 0.0f);
}

TEST_CASE("Construct unit vector k") {
    constexpr auto v_k = Vec4f::k();
    CHECK(v_k[0] == 0.0f);
    CHECK(v_k[1] == 0.0f);
    CHECK(v_k[2] == 1.0f);
    CHECK(v_k[3] == 0.0f);
}

TEST_CASE("Access elements by named x,y,z,w accessors") {
    constexpr Vec4f v{1.0f, 2.0f, 3.0f, 4.0f};
    CHECK(v.x() == 1.0f);
    CHECK(v.y() == 2.0f);
    CHECK(v.z() == 3.0f);
    CHECK(v.w() == 4.0f);
}

TEST_CASE("Access elements by []") {
    Vec4f v{};
    for (size_t i = 0; i < 4; i++) {
        v[i] = i + 1.0f;
        CHECK(v[i] == i + 1.0f);
    }
}

TEST_CASE("Test vector += vector") {
    Vec4f v1{1.0f, 2.0f, 3.0f, 4.0f};
    constexpr Vec4f v2{5.0f, 6.0f, 7.0f, 8.0f};
    v1 += v2;
    CHECK(v1[0] == 6.0f);
    CHECK(v1[1] == 8.0f);
    CHECK(v1[2] == 10.0f);
    CHECK(v1[3] == 12.0f);
}

TEST_CASE("Test vector -= vector") {
    Vec4f v1{1.0f, 2.0f, 3.0f, 4.0f};
    constexpr Vec4f v2{4.0f, 3.0f, 2.0f, 1.0f};
    v1 -= v2;
    CHECK(v1[0] == -3.0f);
    CHECK(v1[1] == -1.0f);
    CHECK(v1[2] == 1.0f);
    CHECK(v1[3] == 3.0f);
}

TEST_CASE("Test vector *= scalar") {
    Vec4f v{1.0f, 2.0f, 3.0f, 4.0f};
    v *= 2.0f;
    CHECK(v[0] == doctest::Approx(2.0f));
    CHECK(v[1] == doctest::Approx(4.0f));
    CHECK(v[2] == doctest::Approx(6.0f));
    CHECK(v[3] == doctest::Approx(8.0f));
}

TEST_CASE("Test vector /= scalar") {
    Vec4f v{1.0f, 2.0f, 3.0f, 4.0f};
    v /= 2.0f;
    CHECK(v[0] == doctest::Approx(0.5f));
    CHECK(v[1] == doctest::Approx(1.0f));
    CHECK(v[2] == doctest::Approx(1.5f));
    CHECK(v[3] == doctest::Approx(2.0f));
}

TEST_CASE("Test -vector") {
    constexpr Vec4f v1{1.0f, 2.0f, 3.0f, 4.0f};
    constexpr Vec4f v2 = -v1;
    CHECK(v2[0] == -1.0f);
    CHECK(v2[1] == -2.0f);
    CHECK(v2[2] == -3.0f);
    CHECK(v2[3] == -4.0f);
}

TEST_CASE("Test vector == vector") {
    // Check equality case
    constexpr Vec4f v1{1.0f, 2.0f, 3.0f, 4.0f};
    constexpr Vec4f v2{1.0f, 2.0f, 3.0f, 4.0f};
    CHECK(v1 == v2);

    // Check inequality cases
    for (size_t i = 0; i < 4; i++) {
        Vec4f v2_modified = v2;
        v2_modified[i] += 0.5f;
        CHECK_FALSE(v1 == v2_modified);
    }
}

// TODO: Test integer vector == vector

TEST_CASE("Test vector != vector") {
    // Check equality case
    constexpr Vec4f v1{1.0f, 2.0f, 3.0f, 4.0f};
    constexpr Vec4f v2{1.0f, 2.0f, 3.0f, 4.0f};
    CHECK_FALSE(v1 != v2);

    // Check inequality cases
    for (size_t i = 0; i < 4; i++) {
        Vec4f v2_modified = v2;
        v2_modified[i] += 0.5f;
        CHECK(v1 != v2_modified);
    }
}

TEST_CASE("Test vector - vector") {
    constexpr Vec4f v1{1.0f, 2.0f, 3.0f, 4.0f};
    constexpr Vec4f v2{4.0f, 3.0f, 2.0f, 1.0f};
    constexpr auto v_diff = v1 - v2;
    CHECK(v_diff[0] == -3.0f);
    CHECK(v_diff[1] == -1.0f);
    CHECK(v_diff[2] == 1.0f);
    CHECK(v_diff[3] == 3.0f);
}

TEST_CASE("Test vector + vector") {
    constexpr Vec4f v1{1.0f, 2.0f, 3.0f, 4.0f};
    constexpr Vec4f v2{5.0f, 6.0f, 7.0f, 8.0f};
    constexpr auto v_sum = v1 + v2;
    CHECK(v_sum[0] == 6.0f);
    CHECK(v_sum[1] == 8.0f);
    CHECK(v_sum[2] == 10.0f);
    CHECK(v_sum[3] == 12.0f);
}

TEST_CASE("Test vector * scalar") {
    constexpr Vec4f v{1.0f, 2.0f, 3.0f, 4.0f};
    constexpr Vec4f v_mult = v * 2.0f;
    CHECK(v_mult[0] == doctest::Approx(2.0f));
    CHECK(v_mult[1] == doctest::Approx(4.0f));
    CHECK(v_mult[2] == doctest::Approx(6.0f));
    CHECK(v_mult[3] == doctest::Approx(8.0f));
}

TEST_CASE("Test scalar * vector") {
    constexpr Vec4f v{1.0f, 2.0f, 3.0f, 4.0f};
    constexpr Vec4f v_mult = 2.0f * v;
    CHECK(v_mult[0] == doctest::Approx(2.0f));
    CHECK(v_mult[1] == doctest::Approx(4.0f));
    CHECK(v_mult[2] == doctest::Approx(6.0f));
    CHECK(v_mult[3] == doctest::Approx(8.0f));
}

TEST_CASE("Test vector / scalar") {
    constexpr Vec4f v{1.0f, 2.0f, 3.0f, 4.0f};
    constexpr Vec4f v_div = v / 2.0f;
    CHECK(v_div[0] == doctest::Approx(0.5f));
    CHECK(v_div[1] == doctest::Approx(1.0f));
    CHECK(v_div[2] == doctest::Approx(1.5f));
    CHECK(v_div[3] == doctest::Approx(2.0f));
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

// TODO: Test projection and rejection (including onto/from unit vectors)

TEST_CASE("Size (2D)") { // TODO: Other sizes
    constexpr Vec4f v{};
    CHECK(v.size() == 4);
}

// TODO: Test manhattan, euclidean, and euclidean-squared distance accessors

TEST_CASE("Normalize") {
    constexpr Vec4f v{1.0f, 2.0f, 3.0f, 4.0f};
    // FIXME: can't make this constexpr because std::sqrt() isn't constexpr! :(
    auto v_normalized = v.normalize();
    CHECK(v_normalized[0] == doctest::Approx(0.182574f));
    CHECK(v_normalized[1] == doctest::Approx(0.365148f));
    CHECK(v_normalized[2] == doctest::Approx(0.547723f));
    CHECK(v_normalized[3] == doctest::Approx(0.730297f));
}

TEST_CASE("Fill") {
    Vec4f v{};
    constexpr float kFillValue = 123.0f;
    v.fill(kFillValue);
    CHECK(v[0] == kFillValue);
    CHECK(v[1] == kFillValue);
    CHECK(v[2] == kFillValue);
    CHECK(v[3] == kFillValue);
}

TEST_CASE("Clear") {
    constexpr float kFillValue = 123.0f;
    Vec4f v{kFillValue};
    WARN(v[0] == kFillValue);
    WARN(v[1] == kFillValue);
    WARN(v[2] == kFillValue);
    WARN(v[3] == kFillValue);
    v.clear();
    CHECK(v[0] == 0.0f);
    CHECK(v[1] == 0.0f);
    CHECK(v[2] == 0.0f);
    CHECK(v[3] == 0.0f);
}