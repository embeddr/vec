// Utilities used in other vec headers

#pragma once

#include <limits>

namespace vec {

template <typename Type>
struct FloatEqParams final {
    Type epsilon = 128 * std::numeric_limits<Type>::epsilon(); // TODO: better default
    Type rel_threshold = std::numeric_limits<Type>::min();     // TODO: better default
};

template <typename Type, auto params=FloatEqParams<Type>()>
bool floating_point_eq(Type a, Type b) {
    static_assert(std::is_floating_point<Type>::value,
            "Type must be floating point (e.g. float, double)");
    static_assert(std::numeric_limits<Type>::epsilon() <= params.epsilon,
            "Provided template parameter epsilon must be >= numeric limits epsilon");
    static_assert(params.epsilon < static_cast<Type>(1.0),
            "Provided template parameter relative threshold must be >= 1");

    if (a == b) { return true; }
    auto diff = std::abs(a - b);
    auto norm = std::min(std::abs(a + b), std::numeric_limits<Type>::max());

    return diff < std::max(params.rel_threshold, params.epsilon * norm);
}

}