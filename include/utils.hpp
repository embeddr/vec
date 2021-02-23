// Utilities used in other vec headers

#pragma once

#include <limits>

namespace vec {

template <typename Type>
bool floating_point_eq(Type a, Type b) {
    static constexpr Type epsilon = 128 * std::numeric_limits<Type>::epsilon();
    static constexpr Type relative_threshold = std::numeric_limits<Type>::min();

    static_assert(std::is_floating_point<Type>::value,
            "Type must be floating point (e.g. float, double)");
    static_assert(epsilon >= std::numeric_limits<Type>::epsilon(),
            "Provided template parameter epsilon must be >= numeric limits epsilon");
    static_assert(epsilon < static_cast<Type>(1),
            "Provided template parameter relative threshold must be >= 1");

    // TODO: Add stackoverflow reference for this - it's useful reading
    if (a == b) { return true; }
    auto diff = std::abs(a - b);
    auto norm = std::min(std::abs(a + b), std::numeric_limits<Type>::max());

    return (diff < std::max(relative_threshold, (epsilon * norm)));
}

}