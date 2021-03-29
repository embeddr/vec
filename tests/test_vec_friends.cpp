// Unit tests for the Vec class implementation (friends)

// Testing headers
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "test_utils.hpp"

// UUT headers
#include "vec.hpp"

TEST_CASE_TEMPLATE("Approximate equality", Type, VALID_TYPES) {
    constexpr TestArray kInput1{1.0, 2.1, -3.0, 4.5};
    constexpr TestArray kInput2{1.0001, 2.1, -3.0, 4.5};

    SUBCASE("4D - Self") {
        constexpr auto v1 = get_vec<Type, 4>(kInput1);
        constexpr bool self_eq = approx_eq(v1, v1);
        CHECK(self_eq);
    }

    SUBCASE("4D - Epsilon") {
        constexpr auto v1 = get_vec<Type, 4>(kInput1);
        constexpr auto v2 = get_vec<Type, 4>(kInput2);
        constexpr bool default_eps_eq = approx_eq(v1, v2);
        constexpr bool custom_eps_eq = approx_eq(v1, v2, 0.001);
        CHECK_FALSE(default_eps_eq);
        CHECK(custom_eps_eq);
    }
}

TEST_CASE_TEMPLATE("Dot product", Type, VALID_TYPES) {
    constexpr TestArray kInput1{1.0, 2.1, -3.0, 4.5};
    constexpr TestArray kInput2{-5.0, 6.9, 7.0, 8.2};

    SUBCASE("2D") {
        constexpr auto v1 = get_vec<Type, 2>(kInput1);
        constexpr auto v2 = get_vec<Type, 2>(kInput2);
        constexpr Type v1_dot_v2 = dot(v1, v2);
        constexpr Type v2_dot_v1 = dot(v2, v1);
        CHECK(v1_dot_v2 == doctest::Approx(9.49));
        CHECK(v1_dot_v2 == v2_dot_v1);
    }

    SUBCASE("3D") {
        constexpr auto v1 = get_vec<Type, 3>(kInput1);
        constexpr auto v2 = get_vec<Type, 3>(kInput2);
        constexpr Type v1_dot_v2 = dot(v1, v2);
        constexpr Type v2_dot_v1 = dot(v2, v1);
        CHECK(v1_dot_v2 == doctest::Approx(-11.51));
        CHECK(v1_dot_v2 == v2_dot_v1);
    }

    SUBCASE("4D") {
        constexpr auto v1 = get_vec<Type, 4>(kInput1);
        constexpr auto v2 = get_vec<Type, 4>(kInput2);
        constexpr Type v1_dot_v2 = dot(v1, v2);
        constexpr Type v2_dot_v1 = dot(v2, v1);
        CHECK(v1_dot_v2 == doctest::Approx(25.39));
        CHECK(v1_dot_v2 == v2_dot_v1);
    }
}

TEST_CASE_TEMPLATE("Cross product", Type, VALID_TYPES) {
    constexpr TestArray kInput1{1.1, 2.0, 3.6};
    constexpr TestArray kInput2{-4.0, 5.9, 6.0};
    constexpr auto v1 = get_vec<Type, 3>(kInput1);
    constexpr auto v2 = get_vec<Type, 3>(kInput2);

    SUBCASE("Arbitrary") {
        constexpr TestArray kExpected{-9.24, -21.0, 14.49};
        constexpr Vec<Type, 3> v1_cross_v2 = cross(v1, v2);
        CHECK(v1_cross_v2 == get_approx_vec<Type, 3>(kExpected));
    }

    SUBCASE("Arbitrary reverse order") {
        constexpr TestArray kExpected{9.24, 21.0, -14.49};
        constexpr Vec<Type, 3> v2_cross_v1 = cross(v2, v1);
        CHECK(v2_cross_v1 == get_approx_vec<Type, 3>(kExpected));
    }

    SUBCASE("Self") {
        constexpr TestArray kExpected{0.0, 0.0, 0.0};
        constexpr Vec<Type, 3> v1_cross_v1 = cross(v1, v1);
        CHECK(v1_cross_v1 == get_approx_vec<Type, 3>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Manhattan distance", Type, VALID_TYPES) {
    constexpr TestArray kInput1{1.0, -2.1, 3.5, 4.0};
    constexpr TestArray kInput2{-5.0, 6.0, 7.2, 8.2};

    SUBCASE("2D") {
        constexpr auto v1 = get_vec<Type, 2>(kInput1);
        constexpr auto v2 = get_vec<Type, 2>(kInput2);
        constexpr Type distance = manhattan(v1, v2);
        CHECK(distance == doctest::Approx(14.1));
        CHECK(manhattan(v1, v2) == doctest::Approx(14.1)); // non-constexpr use
    }

    SUBCASE("3D") {
        constexpr auto v1 = get_vec<Type, 3>(kInput1);
        constexpr auto v2 = get_vec<Type, 3>(kInput2);
        constexpr Type distance = manhattan(v1, v2);
        CHECK(distance == doctest::Approx(17.8));
        CHECK(manhattan(v1, v2) == doctest::Approx(17.8)); // non-constexpr use
    }

    SUBCASE("4D") {
        constexpr auto v1 = get_vec<Type, 4>(kInput1);
        constexpr auto v2 = get_vec<Type, 4>(kInput2);
        constexpr Type distance = manhattan(v1, v2);
        CHECK(distance == doctest::Approx(22.0));
        CHECK(manhattan(v1, v2) == doctest::Approx(22.0)); // non-constexpr use
    }
}

TEST_CASE_TEMPLATE("Euclidean distance", Type, VALID_TYPES) {
    constexpr TestArray kInput1{1.0, -2.1, 3.5, 4.0};
    constexpr TestArray kInput2{-5.0, 6.0, 7.2, 8.2};

    SUBCASE("2D") {
        constexpr auto v1 = get_vec<Type, 2>(kInput1);
        constexpr auto v2 = get_vec<Type, 2>(kInput2);
        constexpr Type distance = euclidean(v1, v2);
        CHECK(distance == doctest::Approx(10.0801785698));
        CHECK(euclidean(v1, v2) == doctest::Approx(10.0801785698)); // non-constexpr use
    }

    SUBCASE("3D") {
        constexpr auto v1 = get_vec<Type, 3>(kInput1);
        constexpr auto v2 = get_vec<Type, 3>(kInput2);
        constexpr Type distance = euclidean(v1, v2);
        CHECK(distance == doctest::Approx(10.7377837564));
        CHECK(euclidean(v1, v2) == doctest::Approx(10.7377837564)); // non-constexpr use
    }

    SUBCASE("4D") {
        constexpr auto v1 = get_vec<Type, 4>(kInput1);
        constexpr auto v2 = get_vec<Type, 4>(kInput2);
        constexpr Type distance = euclidean(v1, v2);
        CHECK(distance == doctest::Approx(11.5299609713));
        CHECK(euclidean(v1, v2) == doctest::Approx(11.5299609713)); // non-constexpr use
    }
}

TEST_CASE_TEMPLATE("Euclidean distance squared", Type, VALID_TYPES) {
    constexpr TestArray kInput1{1.0, -2.1, 3.5, 4.0};
    constexpr TestArray kInput2{-5.0, 6.0, 7.2, 8.2};

    SUBCASE("2D") {
        constexpr auto v1 = get_vec<Type, 2>(kInput1);
        constexpr auto v2 = get_vec<Type, 2>(kInput2);
        constexpr Type distance = euclidean2(v1, v2);
        CHECK(distance == doctest::Approx(101.61));
        CHECK(euclidean2(v1, v2) == doctest::Approx(101.61)); // non-constexpr use
    }

    SUBCASE("3D") {
        constexpr auto v1 = get_vec<Type, 3>(kInput1);
        constexpr auto v2 = get_vec<Type, 3>(kInput2);
        constexpr Type distance = euclidean2(v1, v2);
        CHECK(distance == doctest::Approx(115.3));
        CHECK(euclidean2(v1, v2) == doctest::Approx(115.3)); // non-constexpr use
    }

    SUBCASE("4D") {
        constexpr auto v1 = get_vec<Type, 4>(kInput1);
        constexpr auto v2 = get_vec<Type, 4>(kInput2);
        constexpr Type distance = euclidean2(v1, v2);
        CHECK(distance == doctest::Approx(132.94));
        CHECK(euclidean2(v1, v2) == doctest::Approx(132.94)); // non-constexpr use
    }
}

TEST_CASE_TEMPLATE("Vector triple product", Type, VALID_TYPES) {
    constexpr TestArray kInput1{1.1, 2.0, 3.6};
    constexpr TestArray kInput2{-4.0, 5.9, 6.0};
    constexpr TestArray kInput3{0.0, 7.0, -1.1};
    constexpr TestArray kExpected{-40.16, -143.764, 92.14};
    constexpr auto v1 = get_vec<Type, 3>(kInput1);
    constexpr auto v2 = get_vec<Type, 3>(kInput2);
    constexpr auto v3 = get_vec<Type, 3>(kInput3);

    // Only defined for 3D vectors
    CHECK(vector_triple(v1, v2, v3) == get_approx_vec<Type, 3>(kExpected));
}

TEST_CASE_TEMPLATE("Scalar triple product", Type, VALID_TYPES) {
    constexpr TestArray kInput1{1.1, 2.0, 3.6};
    constexpr TestArray kInput2{-4.0, 5.9, 6.0};
    constexpr TestArray kInput3{0.0, 7.0, -1.1};
    constexpr auto v1 = get_vec<Type, 3>(kInput1);
    constexpr auto v2 = get_vec<Type, 3>(kInput2);
    constexpr auto v3 = get_vec<Type, 3>(kInput3);
    constexpr Type kExpected{-162.939};

    // Only defined for 3D vectors
    CHECK(scalar_triple(v1, v2, v3) == doctest::Approx(kExpected));
}

TEST_CASE_TEMPLATE("Project onto", Type, VALID_TYPES) {
    constexpr TestArray kInput1{1.0, -2.1, 3.5, 4.0};
    constexpr TestArray kInput2{-5.0, 6.0, 7.2, 8.2};

    SUBCASE("2D") {
        // Note: higher resolution provided for operator== check below
        constexpr TestArray kExpected{1.4426229508, -1.7311475409};
        constexpr auto v1 = get_vec<Type, 2>(kInput1);
        constexpr auto v2 = get_vec<Type, 2>(kInput2);
        constexpr Vec<Type, 2> v1_proj_v2 = project_onto(v1, v2);
        CHECK(v1_proj_v2 == get_approx_vec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr TestArray kExpected{-0.3367600141, 0.4041120170, 0.4849344204};
        constexpr auto v1 = get_vec<Type, 3>(kInput1);
        constexpr auto v2 = get_vec<Type, 3>(kInput2);
        constexpr Vec<Type, 3> v1_proj_v2 = project_onto(v1, v2);
        CHECK(v1_proj_v2 == get_approx_vec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr TestArray kExpected{-1.1217236783, 1.3460684140, 1.6152820968, 1.8396268325};
        constexpr auto v1 = get_vec<Type, 4>(kInput1);
        constexpr auto v2 = get_vec<Type, 4>(kInput2);
        constexpr Vec<Type, 4> v1_proj_v2 = project_onto(v1, v2);
        CHECK(v1_proj_v2 == get_approx_vec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Project onto unit", Type, VALID_TYPES) {
    constexpr TestArray kInput1{1.0, -2.1, 3.5, 4.0};
    constexpr TestArray kInput2{-1.0, 0.0, 0.0, 0.0};

    SUBCASE("2D") {
        constexpr TestArray kExpected{1.0, 0.0};
        constexpr auto v1 = get_vec<Type, 2>(kInput1);
        constexpr auto v2 = get_vec<Type, 2>(kInput2);
        constexpr Vec<Type, 2> v1_proj_unit_v2 = project_onto_unit(v1, v2);
        CHECK(v1_proj_unit_v2 == get_approx_vec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr TestArray kExpected{1.0, 0.0, 0.0};
        constexpr auto v1 = get_vec<Type, 3>(kInput1);
        constexpr auto v2 = get_vec<Type, 3>(kInput2);
        constexpr Vec<Type, 3> v1_proj_unit_v2 = project_onto_unit(v1, v2);
        CHECK(v1_proj_unit_v2 == get_approx_vec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr TestArray kExpected{1.0, 0.0, 0.0, 0.0};
        constexpr auto v1 = get_vec<Type, 4>(kInput1);
        constexpr auto v2 = get_vec<Type, 4>(kInput2);
        constexpr Vec<Type, 4> v1_proj_unit_v2 = project_onto_unit(v1, v2);
        CHECK(v1_proj_unit_v2 == get_approx_vec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Reject from", Type, VALID_TYPES) {
    constexpr TestArray kInput1{1.0, -2.1, 3.5, 4.0};
    constexpr TestArray kInput2{-5.0, 6.0, 7.2, 8.2};

    SUBCASE("2D") {
        // Note: higher resolution provided for operator== check below
        constexpr TestArray kExpected{-0.4426229508, -0.3688524590};
        constexpr auto v1 = get_vec<Type, 2>(kInput1);
        constexpr auto v2 = get_vec<Type, 2>(kInput2);
        constexpr Vec<Type, 2> v1_rej_v2 = reject_from(v1, v2);
        CHECK(v1_rej_v2 == get_approx_vec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr TestArray kExpected{1.3367600141, -2.5041120170, 3.0150655795};
        constexpr auto v1 = get_vec<Type, 3>(kInput1);
        constexpr auto v2 = get_vec<Type, 3>(kInput2);
        constexpr Vec<Type, 3> v1_rej_v2 = reject_from(v1, v2);
        CHECK(v1_rej_v2 == get_approx_vec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr TestArray kExpected{2.1217236783, -3.4460684140, 1.8847179031, 2.1603731674};
        constexpr auto v1 = get_vec<Type, 4>(kInput1);
        constexpr auto v2 = get_vec<Type, 4>(kInput2);
        constexpr Vec<Type, 4> v1_rej_v2 = reject_from(v1, v2);
        CHECK(v1_rej_v2 == get_approx_vec<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Reject from unit", Type, VALID_TYPES) {
    constexpr TestArray kInput1{1.0, -2.1, 3.5, 4.0};
    constexpr TestArray kInput2{0.0, 1.0, 0.0, 0.0};

    SUBCASE("2D") {
        constexpr TestArray kExpected{1.0, 0.0};
        constexpr auto v1 = get_vec<Type, 2>(kInput1);
        constexpr auto v2 = get_vec<Type, 2>(kInput2);
        constexpr Vec<Type, 2> v1_rej_unit_v2 = reject_from_unit(v1, v2);
        CHECK(v1_rej_unit_v2 == get_approx_vec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr TestArray kExpected{1.0, 0.0, 3.5};
        constexpr auto v1 = get_vec<Type, 3>(kInput1);
        constexpr auto v2 = get_vec<Type, 3>(kInput2);
        constexpr Vec<Type, 3> v1_rej_unit_v2 = reject_from_unit(v1, v2);
        CHECK(v1_rej_unit_v2 == get_approx_vec<Type, 3>(kExpected));
    }

    SUBCASE("4D") {
        constexpr TestArray kExpected{1.0, 0.0, 3.5, 4.0};
        constexpr auto v1 = get_vec<Type, 4>(kInput1);
        constexpr auto v2 = get_vec<Type, 4>(kInput2);
        constexpr Vec<Type, 4> v1_rej_unit_v2 = reject_from_unit(v1, v2);
        CHECK(v1_rej_unit_v2 == get_approx_vec<Type, 4>(kExpected));
    }
}
