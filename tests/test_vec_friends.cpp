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
    // Shared input data:
    constexpr TestArray kInput1{1.1L, 2.0L, 3.6L};
    constexpr TestArray kInput2{-4.0L, 5.9L, 6.0L};
    constexpr auto v1 = getVec<3, Type>(kInput1);
    constexpr auto v2 = getVec<3, Type>(kInput2);

    SUBCASE("Arbitrary") {
        constexpr TestArray kExpected{-9.24L, -21.0L, 14.49L};
        constexpr Vec<3, Type> v1_cross_v2 = cross(v1, v2);
        CHECK(v1_cross_v2 == getVec<3, Type>(kExpected));
    }

    SUBCASE("Arbitrary reverse order") {
        constexpr TestArray kExpected{9.24L, 21.0L, -14.49L};
        constexpr Vec<3, Type> v2_cross_v1 = cross(v2, v1);
        CHECK(v2_cross_v1 == getVec<3, Type>(kExpected));
    }

    SUBCASE("Self") {
        constexpr TestArray kExpected{0.0L, 0.0L, 0.0L};
        constexpr Vec<3, Type> v1_cross_v1 = cross(v1, v1);
        CHECK(v1_cross_v1 == getVec<3, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Cross product (fixed-point)", Type, short, int /*VALID_INT_TYPES*/) {
    // Cross product defined only for 3D vectors
    constexpr TestArrayInt kInput1{1, 2, 3};
    constexpr TestArrayInt kInput2{-4, 5, 6};
    constexpr auto v1 = getVec<3, Type>(kInput1);
    constexpr auto v2 = getVec<3, Type>(kInput2);

    SUBCASE("Arbitrary") {
        constexpr TestArrayInt kExpected{-3, -18, 13};
        constexpr Vec<3, Type> v1_cross_v2 = cross(v1, v2);
        CHECK(v1_cross_v2 == getVec<3, Type>(kExpected));
    }

    SUBCASE("Arbitrary reverse order") {
        constexpr TestArrayInt kExpected{3, 18, -13};
        constexpr Vec<3, Type> v2_cross_v1 = cross(v2, v1);
        CHECK(v2_cross_v1 == getVec<3, Type>(kExpected));
    }

    SUBCASE("Self") {
        constexpr TestArrayInt kExpected{0, 0, 0};
        constexpr Vec<3, Type> v1_cross_v1 = cross(v1, v1);
        CHECK(v1_cross_v1 == getVec<3, Type>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Manhattan distance (floating-point)", Type, VALID_FLOAT_TYPES) {
    // Shared input data:
    constexpr TestArray kInput1{1.0L, -2.1L, 3.5L, 4.0L};
    constexpr TestArray kInput2{-5.0L, 6.0L, 7.2L, 8.2L};

    SUBCASE("2D") {
        constexpr auto v1 = getVec<2, Type>(kInput1);
        constexpr auto v2 = getVec<2, Type>(kInput2);
        constexpr Type distance = manhattan(v1, v2);
        CHECK(distance == doctest::Approx(14.1L));
        CHECK(manhattan(v1, v2) == doctest::Approx(14.1L)); // non-constexpr use
    }

    SUBCASE("3D") {
        constexpr auto v1 = getVec<3, Type>(kInput1);
        constexpr auto v2 = getVec<3, Type>(kInput2);
        constexpr Type distance = manhattan(v1, v2);
        CHECK(distance == doctest::Approx(17.8L));
        CHECK(manhattan(v1, v2) == doctest::Approx(17.8L)); // non-constexpr use
    }

    SUBCASE("4D") {
        constexpr auto v1 = getVec<4, Type>(kInput1);
        constexpr auto v2 = getVec<4, Type>(kInput2);
        constexpr Type distance = manhattan(v1, v2);
        CHECK(distance == doctest::Approx(22.0L));
        CHECK(manhattan(v1, v2) == doctest::Approx(22.0L)); // non-constexpr use
    }
}

TEST_CASE_TEMPLATE("Manhattan distance (fixed-point)", Type, VALID_INT_TYPES) {
    // Shared input data:
    constexpr TestArrayInt kInput1{1, 2, -3, 4};
    constexpr TestArrayInt kInput2{-5, 6, 7, 8};

    SUBCASE("2D") {
        constexpr auto v1 = getVec<2, Type>(kInput1);
        constexpr auto v2 = getVec<2, Type>(kInput2);
        constexpr Type distance = manhattan(v1, v2);
        CHECK(distance == 10);
        CHECK(manhattan(v1, v2) == 10); // non-constexpr use
    }

    SUBCASE("3D") {
        constexpr auto v1 = getVec<3, Type>(kInput1);
        constexpr auto v2 = getVec<3, Type>(kInput2);
        constexpr Type distance = manhattan(v1, v2);
        CHECK(distance == 20);
        CHECK(manhattan(v1, v2) == 20); // non-constexpr use
    }

    SUBCASE("4D") {
        constexpr auto v1 = getVec<4, Type>(kInput1);
        constexpr auto v2 = getVec<4, Type>(kInput2);
        constexpr Type distance = manhattan(v1, v2);
        CHECK(distance == 24);
        CHECK(manhattan(v1, v2) == 24); // non-constexpr use
    }
}

TEST_CASE_TEMPLATE("Euclidean distance (floating-point)", Type, VALID_FLOAT_TYPES) {
    // Shared input data:
    constexpr TestArray kInput1{1.0L, -2.1L, 3.5L, 4.0L};
    constexpr TestArray kInput2{-5.0L, 6.0L, 7.2L, 8.2L};

    SUBCASE("2D") {
        constexpr auto v1 = getVec<2, Type>(kInput1);
        constexpr auto v2 = getVec<2, Type>(kInput2);
        constexpr Type distance = euclidean(v1, v2);
        CHECK(distance == doctest::Approx(10.0801785698L));
        CHECK(euclidean(v1, v2) == doctest::Approx(10.0801785698L)); // non-constexpr use
    }

    SUBCASE("3D") {
        constexpr auto v1 = getVec<3, Type>(kInput1);
        constexpr auto v2 = getVec<3, Type>(kInput2);
        constexpr Type distance = euclidean(v1, v2);
        CHECK(distance == doctest::Approx(10.7377837564L));
        CHECK(euclidean(v1, v2) == doctest::Approx(10.7377837564L)); // non-constexpr use
    }

    SUBCASE("4D") {
        constexpr auto v1 = getVec<4, Type>(kInput1);
        constexpr auto v2 = getVec<4, Type>(kInput2);
        constexpr Type distance = euclidean(v1, v2);
        CHECK(distance == doctest::Approx(11.5299609713L));
        CHECK(euclidean(v1, v2) == doctest::Approx(11.5299609713L)); // non-constexpr use
    }
}

TEST_CASE_TEMPLATE("Euclidean distance (fixed-point)", Type, VALID_INT_TYPES) {
    // Shared input data:
    constexpr TestArrayInt kInput1{1, 2, -3, 4};
    constexpr TestArrayInt kInput2{-5, 6, 7, 8};

    SUBCASE("2D") {
        constexpr auto v1 = getVec<2, Type>(kInput1);
        constexpr auto v2 = getVec<2, Type>(kInput2);
        constexpr Type distance = euclidean(v1, v2);
        CHECK(distance == 7);
        CHECK(euclidean(v1, v2) == 7); // non-constexpr use
    }

    SUBCASE("3D") {
        constexpr auto v1 = getVec<3, Type>(kInput1);
        constexpr auto v2 = getVec<3, Type>(kInput2);
        constexpr Type distance = euclidean(v1, v2);
        CHECK(distance == 12);
        CHECK(euclidean(v1, v2) == 12); // non-constexpr use
    }

    SUBCASE("4D") {
        constexpr auto v1 = getVec<4, Type>(kInput1);
        constexpr auto v2 = getVec<4, Type>(kInput2);
        constexpr Type distance = euclidean(v1, v2);
        CHECK(distance == 12);
        CHECK(euclidean(v1, v2) == 12); // non-constexpr use
    }
}

TEST_CASE_TEMPLATE("Euclidean distance squared (floating-point)", Type, VALID_FLOAT_TYPES) {
    // Shared input data:
    constexpr TestArray kInput1{1.0L, -2.1L, 3.5L, 4.0L};
    constexpr TestArray kInput2{-5.0L, 6.0L, 7.2L, 8.2L};

    SUBCASE("2D") {
        constexpr auto v1 = getVec<2, Type>(kInput1);
        constexpr auto v2 = getVec<2, Type>(kInput2);
        constexpr Type distance = euclidean2(v1, v2);
        CHECK(distance == doctest::Approx(101.61L));
        CHECK(euclidean2(v1, v2) == doctest::Approx(101.61L)); // non-constexpr use
    }

    SUBCASE("3D") {
        constexpr auto v1 = getVec<3, Type>(kInput1);
        constexpr auto v2 = getVec<3, Type>(kInput2);
        constexpr Type distance = euclidean2(v1, v2);
        CHECK(distance == doctest::Approx(115.3L));
        CHECK(euclidean2(v1, v2) == doctest::Approx(115.3L)); // non-constexpr use
    }

    SUBCASE("4D") {
        constexpr auto v1 = getVec<4, Type>(kInput1);
        constexpr auto v2 = getVec<4, Type>(kInput2);
        constexpr Type distance = euclidean2(v1, v2);
        CHECK(distance == doctest::Approx(132.94L));
        CHECK(euclidean2(v1, v2) == doctest::Approx(132.94L)); // non-constexpr use
    }
}

TEST_CASE_TEMPLATE("Euclidean distance squared (fixed-point)", Type, VALID_INT_TYPES) {
    // Shared input data:
    constexpr TestArrayInt kInput1{1, 2, -3, 4};
    constexpr TestArrayInt kInput2{-5, 6, 7, 8};

    SUBCASE("2D") {
        constexpr auto v1 = getVec<2, Type>(kInput1);
        constexpr auto v2 = getVec<2, Type>(kInput2);
        constexpr Type distance = euclidean2(v1, v2);
        CHECK(distance == 52);
        CHECK(euclidean2(v1, v2) == 52); // non-constexpr use
    }

    SUBCASE("3D") {
        constexpr auto v1 = getVec<3, Type>(kInput1);
        constexpr auto v2 = getVec<3, Type>(kInput2);
        constexpr Type distance = euclidean2(v1, v2);
        CHECK(distance == 152);
        CHECK(euclidean2(v1, v2) == 152); // non-constexpr use
    }

    SUBCASE("4D") {
        constexpr auto v1 = getVec<4, Type>(kInput1);
        constexpr auto v2 = getVec<4, Type>(kInput2);
        constexpr Type distance = euclidean2(v1, v2);
        CHECK(distance == 168);
        CHECK(euclidean2(v1, v2) == 168); // non-constexpr use
    }
}

TEST_CASE_TEMPLATE("Vector triple product (floating-point)", Type, VALID_FLOAT_TYPES) {
    // Shared input data:
    constexpr TestArray kInput1{1.1L, 2.0L, 3.6L};
    constexpr TestArray kInput2{-4.0L, 5.9L, 6.0L};
    constexpr TestArray kInput3{0.0L, 7.0L, -1.1L};
    constexpr TestArray kExpected{-40.16L, -143.764L, 92.14L};
    constexpr auto v1 = getVec<3, Type>(kInput1);
    constexpr auto v2 = getVec<3, Type>(kInput2);
    constexpr auto v3 = getVec<3, Type>(kInput3);

    // Only defined for 3D vectors
    CHECK(vector_triple(v1, v2, v3) == getVec<3, Type>(kExpected));
}

TEST_CASE_TEMPLATE("Vector triple product (fixed-point)", Type, VALID_INT_TYPES) {
    // Shared input data:
    constexpr TestArray kInput1{1, 2, 4};
    constexpr TestArray kInput2{-4, 5, 6};
    constexpr TestArray kInput3{0, 7, -1};
    constexpr TestArray kExpected{-40L, -160, 90};
    constexpr auto v1 = getVec<3, Type>(kInput1);
    constexpr auto v2 = getVec<3, Type>(kInput2);
    constexpr auto v3 = getVec<3, Type>(kInput3);

    // Only defined for 3D vectors
    CHECK(vector_triple(v1, v2, v3) == getVec<3, Type>(kExpected));
}

TEST_CASE_TEMPLATE("Scalar triple product (floating-point)", Type, VALID_FLOAT_TYPES) {
    // Shared input data:
    constexpr TestArray kInput1{1.1L, 2.0L, 3.6L};
    constexpr TestArray kInput2{-4.0L, 5.9L, 6.0L};
    constexpr TestArray kInput3{0.0L, 7.0L, -1.1L};
    constexpr auto v1 = getVec<3, Type>(kInput1);
    constexpr auto v2 = getVec<3, Type>(kInput2);
    constexpr auto v3 = getVec<3, Type>(kInput3);
    constexpr Type kExpected{-162.939L};

    // Only defined for 3D vectors
    CHECK(scalar_triple(v1, v2, v3) == doctest::Approx(kExpected));
}

TEST_CASE_TEMPLATE("Scalar triple product (fixed-point)", Type, VALID_INT_TYPES) {
    // Shared input data:
    constexpr TestArray kInput1{1, 2, 4};
    constexpr TestArray kInput2{-4, 5, 6};
    constexpr TestArray kInput3{0, 7, -1};
    constexpr auto v1 = getVec<3, Type>(kInput1);
    constexpr auto v2 = getVec<3, Type>(kInput2);
    constexpr auto v3 = getVec<3, Type>(kInput3);
    constexpr Type kExpected{-167};

    // Only defined for 3D vectors
    CHECK(scalar_triple(v1, v2, v3) == kExpected);
}

TEST_CASE_TEMPLATE("Project onto (floating-point)", Type, VALID_FLOAT_TYPES) {
    // Shared input data:
    constexpr TestArray kInput1{1.0L, -2.1L, 3.5L, 4.0L};
    constexpr TestArray kInput2{-5.0L, 6.0L, 7.2L, 8.2L};

    SUBCASE("2D") {
        // Note: higher resolution provided for operator== check below
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
        // Note: higher resolution provided for operator== check below
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

