// Utilities used in other vec headers

#pragma once

#include <limits>

namespace vec {

template <typename Type>
static constexpr Type floating_point_eq_epsilon = 128 * std::numeric_limits<Type>::epsilon();
template <typename Type>
static constexpr Type floating_point_eq_threshold = std::numeric_limits<Type>::min();

template <typename Type>
bool floating_point_eq(Type a, Type b) {
    static_assert(std::is_floating_point<Type>::value,
            "Type must be floating point (e.g. float, double)");
    static_assert(floating_point_eq_epsilon<Type> >= std::numeric_limits<Type>::epsilon(),
            "Provided template parameter epsilon must be >= numeric limits epsilon");
    static_assert(floating_point_eq_epsilon<Type> < static_cast<Type>(1.0),
            "Provided template parameter relative threshold must be >= 1");

    if (a == b) { return true; }
    auto diff = std::abs(a - b);
    auto norm = std::min(std::abs(a + b), std::numeric_limits<Type>::max());

    return diff < std::max(floating_point_eq_threshold<Type>,
            (floating_point_eq_epsilon<Type> * norm));
}

}