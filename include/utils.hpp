// Math utilities for Vec

#pragma once

#include <cassert>
#include <limits>

namespace vec::utils {

template <typename Type>
constexpr Type kFloatEqDefaultEpsilon = 128 * std::numeric_limits<Type>::epsilon();
template <typename Type>
constexpr Type kFloatEqDefaultAbsThreshold = std::numeric_limits<Type>::min();

// Concepts
template<typename Type>
concept IsArithmetic = std::is_arithmetic_v<Type>;
template<typename Type>
concept IsFloatingPoint = std::is_floating_point_v<Type>;

namespace constexpr_impl {

// Implementation for constexpr absolute value
template<typename Type>
requires IsArithmetic<Type>
constexpr auto abs(Type const &x) {
    return (x < 0) ? -x : x;
}

// Implementation for constexpr floating-point square root
template<typename Type>
requires IsFloatingPoint<Type>
constexpr Type sqrt_floating_point_helper(Type x, Type current, Type previous) {
    return (current == previous)
            ? current
            : sqrt_floating_point_helper<Type>(x, 0.5 * (current + (x / current)), current);
}

template<typename Type>
requires IsFloatingPoint<Type>
constexpr Type sqrt_floating_point(Type x) {
    // TODO: error on negative/infinite inputs
    return (x >= 0) && (x < std::numeric_limits<Type>::infinity())
            ? sqrt_floating_point_helper<Type>(x, x, 0)
            : std::numeric_limits<Type>::quiet_NaN();
}

} // namespace constexpr_impl

// Get the absolute value of arithmetic value x
template<typename Type>
requires IsArithmetic<Type>
constexpr auto abs(Type const &x) {
    if (std::is_constant_evaluated()) {
        return constexpr_impl::abs(x);
    } else {
        // Use standard library implementation at runtime
        return std::abs(x);
    }
}

// Get the square root of arithmetic value x
template<typename Type>
requires IsArithmetic<Type>
constexpr Type sqrt(Type const &x) {
    if (std::is_constant_evaluated()) {
        return constexpr_impl::sqrt_floating_point<Type>(x);
    } else {
        // Use standard library implementation at runtime
        return std::sqrt(x);
    }
}

// Check approximate equality of two floating-point values a and b
template<typename Type>
requires IsFloatingPoint<Type>
constexpr bool floating_point_eq(Type a, Type b,
                                 Type epsilon = kFloatEqDefaultEpsilon<Type>,
                                 Type abs_threshold = kFloatEqDefaultAbsThreshold<Type>) {
    // TODO: throw exception instead?
    assert(epsilon >= std::numeric_limits<Type>::epsilon());
    assert(epsilon < static_cast<Type>(1));

    // See https://stackoverflow.com/a/32334103 for a great post on float comparisons
    if (a == b) { return true; }
    auto diff = abs(a - b); // utils::abs()
    auto norm = std::min(std::abs(a + b), std::numeric_limits<Type>::max());
    return (diff < std::max(abs_threshold, (epsilon * norm)));
}

} // namespace vec::utils