// Unit tests for the Mat class implementation (friends)

// Testing headers
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "test_utils.hpp"

// UUT headers
#include "transform.hpp"

TEST_CASE_TEMPLATE("Construct default transform with no arguments", Type, VALID_TYPES) {
    SUBCASE("2D") {
        constexpr TestGrid kExpected{{
                {1.0, 0.0, 0.0},
                {0.0, 1.0, 0.0},
                {0.0, 0.0, 1.0},
        }};
        constexpr AffineTransform<Type, 2> affine_transform;
        CHECK(affine_transform == get_approx_mat<Type, 3>(kExpected));
    }

    SUBCASE("3D") {
        constexpr TestGrid kExpected{{
                {1.0, 0.0, 0.0, 0.0},
                {0.0, 1.0, 0.0, 0.0},
                {0.0, 0.0, 1.0, 0.0},
                {0.0, 0.0, 0.0, 1.0},
        }};
        constexpr AffineTransform<Type, 3> affine_transform;
        CHECK(affine_transform == get_approx_mat<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Construct transform with matrix and vector", Type, VALID_TYPES) {
    constexpr TestGrid kInputTransform{{
            {1.0, 2.0, -3.0},
            {4.0, -5.0, 6.0},
            {-7.0, 8.0, 9.0},
    }};
    constexpr TestArray kInputTranslation{1.0, 2.0, 3.0};

    SUBCASE("2D") {
        constexpr TestGrid kExpected{{
                {1.0, 2.0, 0.0},
                {4.0, -5.0, 0.0},
                {1.0, 2.0, 1.0},
        }};
        constexpr auto transform_in = get_mat<Type, 2>(kInputTransform);
        constexpr auto translation_in = get_vec<Type, 2>(kInputTranslation);
        constexpr AffineTransform<Type, 2> affine_transform(transform_in, translation_in);
        CHECK(affine_transform == get_approx_mat<Type, 3>(kExpected));
    }

    SUBCASE("3D") {
        constexpr TestGrid kExpected{{
                {1.0, 2.0, -3.0, 0.0},
                {4.0, -5.0, 6.0, 0.0},
                {-7.0, 8.0, 9.0, 0.0},
                {1.0, 2.0, 3.0, 1.0},
        }};
        constexpr auto transform_in = get_mat<Type, 3>(kInputTransform);
        constexpr auto translation_in = get_vec<Type, 3>(kInputTranslation);
        constexpr AffineTransform<Type, 3> affine_transform(transform_in, translation_in);
        CHECK(affine_transform == get_approx_mat<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Construct transform with matrix only", Type, VALID_TYPES) {
    constexpr TestGrid kInputTransform{{
            {1.0, 2.0, -3.0},
            {4.0, -5.0, 6.0},
            {-7.0, 8.0, 9.0},
    }};
    SUBCASE("2D") {
        constexpr TestGrid kExpected{{
                {1.0, 2.0, 0.0},
                {4.0, -5.0, 0.0},
                {0.0, 0.0, 1.0},
        }};
        constexpr auto transform_in = get_mat<Type, 2>(kInputTransform);
        constexpr AffineTransform<Type, 2> affine_transform(transform_in);
        CHECK(affine_transform == get_approx_mat<Type, 3>(kExpected));
    }

    SUBCASE("3D") {
        constexpr TestGrid kExpected{{
                {1.0, 2.0, -3.0, 0.0},
                {4.0, -5.0, 6.0, 0.0},
                {-7.0, 8.0, 9.0, 0.0},
                {0.0, 0.0, 0.0, 1.0},
        }};
        constexpr auto transform_in = get_mat<Type, 3>(kInputTransform);
        constexpr AffineTransform<Type, 3> affine_transform(transform_in);
        CHECK(affine_transform == get_approx_mat<Type, 4>(kExpected));
    }
}
TEST_CASE_TEMPLATE("Construct transform with vector only", Type, VALID_TYPES) {
    constexpr TestArray kInputTranslation{1.0, 2.0, 3.0};
    SUBCASE("2D") {
        constexpr TestGrid kExpected{{
                {1.0, 0.0, 0.0},
                {0.0, 1.0, 0.0},
                {1.0, 2.0, 1.0},
        }};
        constexpr auto translation_in = get_vec<Type, 2>(kInputTranslation);
        constexpr AffineTransform<Type, 2> affine_transform(translation_in);
        CHECK(affine_transform == get_approx_mat<Type, 3>(kExpected));
    }

    SUBCASE("3D") {
        constexpr TestGrid kExpected{{
                {1.0, 0.0, 0.0, 0.0},
                {0.0, 1.0, 0.0, 0.0},
                {0.0, 0.0, 1.0, 0.0},
                {1.0, 2.0, 3.0, 1.0},
        }};
        constexpr auto translation_in = get_vec<Type, 3>(kInputTranslation);
        constexpr AffineTransform<Type, 3> affine_transform(translation_in);
        CHECK(affine_transform == get_approx_mat<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Test getting linear transform", Type, VALID_TYPES) {
    constexpr TestGrid kInput{{
            {1.0, 2.0, -3.0},
            {4.0, -5.0, 6.0},
            {-7.0, 8.0, 9.0},
    }};
    constexpr TestGrid kExpected{kInput};

    SUBCASE("2D") {
        constexpr AffineTransform<Type, 2> affine_transform(get_mat<Type, 2>(kInput));
        constexpr Mat<Type, 2> linear_transform = affine_transform.get_linear_transform();
        CHECK(linear_transform == get_mat<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr AffineTransform<Type, 3> affine_transform(get_mat<Type, 3>(kInput));
        constexpr Mat<Type, 3> linear_transform = affine_transform.get_linear_transform();
        CHECK(linear_transform == get_mat<Type, 3>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Test setting linear transform", Type, VALID_TYPES) {
    constexpr TestGrid kInput{{
            {1.0, 2.0, -3.0},
            {4.0, -5.0, 6.0},
            {-7.0, 8.0, 9.0},
    }};

    SUBCASE("2D") {
        constexpr TestGrid kExpected{{
                {1.0, 2.0,  0.0},
                {4.0, -5.0, 0.0},
                {0.0, 0.0,  1.0},
        }};
        AffineTransform<Type, 2> affine_transform;
        affine_transform.set_linear_transform(get_mat<Type, 2>(kInput));
        CHECK(affine_transform == get_mat<Type, 3>(kExpected));
    }

    SUBCASE("3D") {
        constexpr TestGrid kExpected{{
                {1.0, 2.0, -3.0, 0.0},
                {4.0, -5.0, 6.0, 0.0},
                {-7.0, 8.0, 9.0, 0.0},
                {0.0, 0.0, 0.0, 1.0},
        }};
        AffineTransform<Type, 3> affine_transform;
        affine_transform.set_linear_transform(get_mat<Type, 3>(kInput));
        CHECK(affine_transform == get_mat<Type, 4>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Test getting translation", Type, VALID_TYPES) {
    constexpr TestArray kInput{1.0, 2.0, 3.0};
    constexpr TestArray kExpected{kInput};

    SUBCASE("2D") {
        constexpr AffineTransform<Type, 2> affine_transform(get_vec<Type, 2>(kInput));
        constexpr Vec<Type, 2> translation = affine_transform.get_translation();
        CHECK(translation == get_vec<Type, 2>(kExpected));
    }

    SUBCASE("3D") {
        constexpr AffineTransform<Type, 3> affine_transform(get_vec<Type, 3>(kInput));
        constexpr Vec<Type, 3> translation = affine_transform.get_translation();
        CHECK(translation == get_vec<Type, 3>(kExpected));
    }
}

TEST_CASE_TEMPLATE("Test setting translation", Type, VALID_TYPES) {
    constexpr TestArray kInput{1.0, 2.0, 3.0};

    SUBCASE("2D") {
        constexpr TestGrid kExpected{{
                {1.0, 0.0, 0.0},
                {0.0, 1.0, 0.0},
                {1.0, 2.0, 1.0},
        }};
        AffineTransform<Type, 2> affine_transform;
        affine_transform.set_translation(get_vec<Type, 2>(kInput));
        CHECK(affine_transform == get_mat<Type, 3>(kExpected));
    }

    SUBCASE("3D") {
        constexpr TestGrid kExpected{{
                {1.0, 0.0, 0.0, 0.0},
                {0.0, 1.0, 0.0, 0.0},
                {0.0, 0.0, 1.0, 0.0},
                {1.0, 2.0, 3.0, 1.0},
        }};
        AffineTransform<Type, 3> affine_transform;
        affine_transform.set_translation(get_vec<Type, 3>(kInput));
        CHECK(affine_transform == get_mat<Type, 4>(kExpected));
    }
}
