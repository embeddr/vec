// Unit tests for the Vec class implementation (friends)

// Testing headers
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "test_utils.hpp"

// UUT headers
#include "vec.hpp"

TEST_CASE_TEMPLATE("Dot product (floating-point)", Type, VALID_FLOAT_TYPES) {
    // Shared input data:
    constexpr TestArray kInput1{1.0L, 2.1L, -3.0L, 4.5L};
    constexpr TestArray kInput2{-5.0L, 6.9L, 7.0L, 8.2L};

    SUBCASE("2D") {
        constexpr auto v1 = getVec<2, Type>(kInput1);
        constexpr auto v2 = getVec<2, Type>(kInput2);
        constexpr Type v1_dot_v2 = dot(v1, v2);
        constexpr Type v2_dot_v1 = dot(v2, v1);
        CHECK(v1_dot_v2 == doctest::Approx(9.49L));
        CHECK(v1_dot_v2 == v2_dot_v1);
    }

    SUBCASE("3D") {
        constexpr auto v1 = getVec<3, Type>(kInput1);
        constexpr auto v2 = getVec<3, Type>(kInput2);
        constexpr Type v1_dot_v2 = dot(v1, v2);
        constexpr Type v2_dot_v1 = dot(v2, v1);
        CHECK(v1_dot_v2 == doctest::Approx(-11.51L));
        CHECK(v1_dot_v2 == v2_dot_v1);
    }

    SUBCASE("4D") {
        constexpr auto v1 = getVec<4, Type>(kInput1);
        constexpr auto v2 = getVec<4, Type>(kInput2);
        constexpr Type v1_dot_v2 = dot(v1, v2);
        constexpr Type v2_dot_v1 = dot(v2, v1);
        CHECK(v1_dot_v2 == doctest::Approx(25.39L));
        CHECK(v1_dot_v2 == v2_dot_v1);
    }
}

TEST_CASE_TEMPLATE("Dot product (fixed-point)", Type, VALID_INT_TYPES) {
    // Shared input data:
    constexpr TestArrayInt kInput1{1, 2, -3, 4};
    constexpr TestArrayInt kInput2{-5, 6, 7, 8};

    SUBCASE("2D") {
        constexpr auto v1 = getVec<2, Type>(kInput1);
        constexpr auto v2 = getVec<2, Type>(kInput2);
        constexpr Type v1_dot_v2 = dot(v1, v2);
        constexpr Type v2_dot_v1 = dot(v2, v1);
        CHECK(v1_dot_v2 == 7);
        CHECK(v1_dot_v2 == v2_dot_v1);
    }

    SUBCASE("3D") {
        constexpr auto v1 = getVec<3, Type>(kInput1);
        constexpr auto v2 = getVec<3, Type>(kInput2);
        constexpr Type v1_dot_v2 = dot(v1, v2);
        constexpr Type v2_dot_v1 = dot(v2, v1);
        CHECK(v1_dot_v2 == -14);
        CHECK(v1_dot_v2 == v2_dot_v1);
    }

    SUBCASE("4D") {
        constexpr auto v1 = getVec<4, Type>(kInput1);
        constexpr auto v2 = getVec<4, Type>(kInput2);
        constexpr Type v1_dot_v2 = dot(v1, v2);
        constexpr Type v2_dot_v1 = dot(v2, v1);
        CHECK(v1_dot_v2 == 18);
        CHECK(v1_dot_v2 == v2_dot_v1);
    }
}

TEST_CASE_TEMPLATE("Cross product (floating-point)", Type, VALID_FLOAT_TYPES) {
    // Cross product defined only for 3D vectors
    using vec::Vec3f;
    constexpr Vec3f v1{1.1F, 2.0F, 3.6F};
    constexpr Vec3f v2{-4.0F, 5.9F, 6.0F};

    SUBCASE("Arbitrary") {
        constexpr Vec3f v1_cross_v2 = cross(v1, v2);
        CHECK(v1_cross_v2 == Vec3f{-9.24F, -21.0F, 14.49F});
    }

    SUBCASE("Arbitrary reverse order") {
        constexpr Vec3f v2_cross_v1 = cross(v2, v1);
        CHECK(v2_cross_v1 == Vec3f{9.24F, 21.0F, -14.49F});
    }

    SUBCASE("Self") {
        constexpr Vec3f v1_cross_v1 = cross(v1, v1);
        CHECK(v1_cross_v1 == Vec3f{0.0F, 0.0F, 0.0F});
    }
}

TEST_CASE_TEMPLATE("Cross product (fixed-point)", Type, VALID_INT_TYPES) {
    // Cross product defined only for 3D vectors
    using vec::Vec3i;
    constexpr Vec3i v1{1, 2, 3};
    constexpr Vec3i v2{-4, 5, 6};

    SUBCASE("Arbitrary") {
        constexpr Vec3i v1_cross_v2 = cross(v1, v2);
        CHECK(v1_cross_v2 == Vec3i{-3, -18, 13});
    }

    SUBCASE("Arbitrary reverse order") {
        constexpr Vec3i v2_cross_v1 = cross(v2, v1);
        CHECK(v2_cross_v1 == Vec3i{3, 18, -13});
    }

    SUBCASE("Self") {
        constexpr Vec3i v1_cross_v1 = cross(v1, v1);
        CHECK(v1_cross_v1 == Vec3i{0, 0, 0});
    }
}

TEST_CASE_TEMPLATE("Project onto (floating-point)", Type, VALID_FLOAT_TYPES) {
    // Shared input data:
    constexpr TestArray kInput1{1.0L, -2.1L, 3.5L, 4.0L};
    constexpr TestArray kInput2{-5.0L, 6.0L, 7.2L, 8.2L};

    SUBCASE("2D") {
        constexpr TestArray kExpected{1.442622950819672130980467L,
                                      -1.731147540983606557284981L};
        constexpr auto v1 = getVec<2, Type>(kInput1);
        constexpr auto v2 = getVec<2, Type>(kInput2);
        constexpr Vec<2, Type> v1_proj_v2 = project_onto(v1, v2);
        CHECK(v1_proj_v2 == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr TestArray kExpected{-0.336760014179369018084758L,
                                      0.404112017015242821723394L,
                                      0.484934420418291386046389L};
        constexpr auto v1 = getVec<3, Type>(kInput1);
        constexpr auto v2 = getVec<3, Type>(kInput2);
        constexpr Vec<3, Type> v1_proj_v2 = project_onto(v1, v2);
        CHECK(v1_proj_v2 == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr TestArray kExpected{-1.121723678365171035205619L,
                                      1.346068414038205242225059L,
                                      1.615282096845846290713439L,
                                      1.839626832518880497624458L};
        constexpr auto v1 = getVec<4, Type>(kInput1);
        constexpr auto v2 = getVec<4, Type>(kInput2);
        constexpr Vec<4, Type> v1_proj_v2 = project_onto(v1, v2);
        CHECK(v1_proj_v2 == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Project onto (fixed-point)", Type, VALID_INT_TYPES) {
    // Shared input data:
    constexpr TestArrayInt kInput1{5, -11, 15, 20};
    constexpr TestArrayInt kInput2{-7, 16, 22, 2};

    SUBCASE("2D") {
        constexpr TestArrayInt kExpected{4, -11};
        constexpr auto v1 = getVec<2, Type>(kInput1);
        constexpr auto v2 = getVec<2, Type>(kInput2);
        constexpr Vec<2, Type> v1_proj_v2 = project_onto(v1, v2);
        CHECK(v1_proj_v2 == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr TestArrayInt kExpected{-1, 2, 3};
        constexpr auto v1 = getVec<3, Type>(kInput1);
        constexpr auto v2 = getVec<3, Type>(kInput2);
        constexpr Vec<3, Type> v1_proj_v2 = project_onto(v1, v2);
        CHECK(v1_proj_v2 == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr TestArrayInt kExpected{-1, 3, 4, 0};
        constexpr auto v1 = getVec<4, Type>(kInput1);
        constexpr auto v2 = getVec<4, Type>(kInput2);
        constexpr Vec<4, Type> v1_proj_v2 = project_onto(v1, v2);
        CHECK(v1_proj_v2 == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Project onto unit", Type, VALID_TYPES) {
    // Shared input data:
    constexpr TestArray kInput1{1.0L, -2.1L, 3.5L, 4.0L};
    constexpr TestArray kInput2{-1.0L, 0.0L, 0.0L, 0.0L};

    SUBCASE("2D") {
        constexpr TestArray kExpected{1.0L, 0.0L};
        constexpr auto v1 = getVec<2, Type>(kInput1);
        constexpr auto v2 = getVec<2, Type>(kInput2);
        constexpr Vec<2, Type> v1_proj_unit_v2 = project_onto_unit(v1, v2);
        CHECK(v1_proj_unit_v2 == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr TestArray kExpected{1.0L, 0.0L, 0.0L};
        constexpr auto v1 = getVec<3, Type>(kInput1);
        constexpr auto v2 = getVec<3, Type>(kInput2);
        constexpr Vec<3, Type> v1_proj_unit_v2 = project_onto_unit(v1, v2);
        CHECK(v1_proj_unit_v2 == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr TestArray kExpected{1.0L, 0.0L, 0.0L, 0.0L};
        constexpr auto v1 = getVec<4, Type>(kInput1);
        constexpr auto v2 = getVec<4, Type>(kInput2);
        constexpr Vec<4, Type> v1_proj_unit_v2 = project_onto_unit(v1, v2);
        CHECK(v1_proj_unit_v2 == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Reject from (floating-point)", Type, VALID_FLOAT_TYPES) {
    // Shared input data:
    constexpr TestArray kInput1{1.0L, -2.1L, 3.5L, 4.0L};
    constexpr TestArray kInput2{-5.0L, 6.0L, 7.2L, 8.2L};

    SUBCASE("2D") {
        constexpr TestArray kExpected{-0.442622950819672130980467L,
                                      -0.368852459016393442628283L};
        constexpr auto v1 = getVec<2, Type>(kInput1);
        constexpr auto v2 = getVec<2, Type>(kInput2);
        constexpr Vec<2, Type> v1_rej_v2 = reject_from(v1, v2);
        CHECK(v1_rej_v2 == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr TestArray kExpected{1.336760014179369018111863L,
                                      -2.504112017015242821690868L,
                                      3.015065579581708613953611L};
        constexpr auto v1 = getVec<3, Type>(kInput1);
        constexpr auto v2 = getVec<3, Type>(kInput2);
        constexpr Vec<3, Type> v1_rej_v2 = reject_from(v1, v2);
        CHECK(v1_rej_v2 == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr TestArray kExpected{2.121723678365171035205619L,
                                      -3.446068414038205242246743L,
                                      1.884717903154153709286561L,
                                      2.160373167481119502375542L};
        constexpr auto v1 = getVec<4, Type>(kInput1);
        constexpr auto v2 = getVec<4, Type>(kInput2);
        constexpr Vec<4, Type> v1_rej_v2 = reject_from(v1, v2);
        CHECK(v1_rej_v2 == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Reject from (fixed-point)", Type, VALID_INT_TYPES) {
    // Shared input data:
    constexpr TestArrayInt kInput1{5, -11, 15, 20};
    constexpr TestArrayInt kInput2{-7, 16, 22, 2};

    SUBCASE("2D") {
        constexpr TestArray kExpected{1, 0};
        constexpr auto v1 = getVec<2, Type>(kInput1);
        constexpr auto v2 = getVec<2, Type>(kInput2);
        constexpr Vec<2, Type> v1_rej_v2 = reject_from(v1, v2);
        CHECK(v1_rej_v2 == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr TestArray kExpected{6, -13, 12};
        constexpr auto v1 = getVec<3, Type>(kInput1);
        constexpr auto v2 = getVec<3, Type>(kInput2);
        constexpr Vec<3, Type> v1_rej_v2 = reject_from(v1, v2);
        CHECK(v1_rej_v2 == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr TestArray kExpected{6, -14, 11, 20};
        constexpr auto v1 = getVec<4, Type>(kInput1);
        constexpr auto v2 = getVec<4, Type>(kInput2);
        constexpr Vec<4, Type> v1_rej_v2 = reject_from(v1, v2);
        CHECK(v1_rej_v2 == getVec<4, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Reject from unit", Type, VALID_TYPES) {
    // Shared input data:
    constexpr TestArray kInput1{1.0L, -2.1L, 3.5L, 4.0L};
    constexpr TestArray kInput2{0.0L, 1.0L, 0.0L, 0.0L};

    SUBCASE("2D") {
        constexpr TestArray kExpected{1.0L, 0.0L};
        constexpr auto v1 = getVec<2, Type>(kInput1);
        constexpr auto v2 = getVec<2, Type>(kInput2);
        constexpr Vec<2, Type> v1_rej_unit_v2 = reject_from_unit(v1, v2);
        CHECK(v1_rej_unit_v2 == getVec<2, Type>(kExpected));
    }

    SUBCASE("3D") {
        constexpr TestArray kExpected{1.0L, 0.0L, 3.5L};
        constexpr auto v1 = getVec<3, Type>(kInput1);
        constexpr auto v2 = getVec<3, Type>(kInput2);
        constexpr Vec<3, Type> v1_rej_unit_v2 = reject_from_unit(v1, v2);
        CHECK(v1_rej_unit_v2 == getVec<3, Type>(kExpected));
    }

    SUBCASE("4D") {
        constexpr TestArray kExpected{1.0L, 0.0L, 3.5L, 4.0L};
        constexpr auto v1 = getVec<4, Type>(kInput1);
        constexpr auto v2 = getVec<4, Type>(kInput2);
        constexpr Vec<4, Type> v1_rej_unit_v2 = reject_from_unit(v1, v2);
        CHECK(v1_rej_unit_v2 == getVec<4, Type>(kExpected));
    }
}

