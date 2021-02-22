// Unit tests for the Vec class implementation

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "include/vec.hpp"

using namespace vec;

TEST_CASE("Construct Vec4f by elements") {
    Vec4f v4{1.0f, 2.0f, 3.0f, 4.0f};
    CHECK(v4[0] == 1.0f);
    CHECK(v4[1] == 2.0f);
}

TEST_CASE("Construct constexpr Vec4f by elements") {
    constexpr Vec4f v4{1.0f, 2.0f, 3.0f, 4.0f};
    CHECK(v4[0] == 1.0f);
    CHECK(v4[1] == 2.0f);
}
