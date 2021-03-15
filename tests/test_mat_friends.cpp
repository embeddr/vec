// Unit tests for the Mat class implementation (friends)

// Testing headers
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "test_utils.hpp"

// UUT headers
#include "mat.hpp"

TEST_CASE_TEMPLATE("Approximate equality", Type, VALID_TYPES) {
    constexpr TestGrid kInput1{{
            {1.0L, 2.0L, 3.0L, 4.0L},
            {5.0L, 6.0L, 7.0L, 8.0L},
            {-1.0L, -2.0L, -3.0L, -4.0L},
            {-5.0L, -6.0L, -7.0L, -8.0L},
    }};
    constexpr TestGrid kInput2{{
            {1.0001L, 2.0L, 3.0L, 4.0L}, // 0.0001 offset
            {5.0L, 6.0L, 7.0L, 8.0L},
            {-1.0L, -2.0L, -3.0L, -4.0L},
            {-5.0L, -6.0L, -7.0L, -8.0L},
    }};

    SUBCASE("4D - Self") {
        constexpr auto m1 = get_mat<Type, 4>(kInput1);
        constexpr bool self_eq = approx_eq(m1, m1);
        CHECK(self_eq);
    }

    SUBCASE("4D - Epsilon") {
        constexpr auto m1 = get_mat<Type, 4>(kInput1);
        constexpr auto m2 = get_mat<Type, 4>(kInput2);
        constexpr bool default_eps_eq = approx_eq(m1, m2);
        constexpr bool custom_eps_eq = approx_eq(m1, m2, static_cast<Type>(0.001));
        CHECK_FALSE(default_eps_eq);
        CHECK(custom_eps_eq);
    }
}
