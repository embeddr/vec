// Math utilities used in other vec headers

#pragma once

#include <limits>

namespace vec {
namespace utils {

template<typename Type>
using IsFloatingPoint = std::enable_if_t<std::is_floating_point_v<Type>>;
template<typename Type>
using IsFixedPoint = std::enable_if_t<std::is_integral_v<Type>>;
template<typename Type>
using IsArithmetic = std::enable_if_t<std::is_arithmetic_v<Type>>;

namespace constexpr_impl {

// Implementation for constexpr absolute value
template<typename Type, typename=IsArithmetic<Type>>
constexpr auto abs(Type const &x) {
    return (x < 0) ? -x : x;
}

// Implementation for constexpr floating-point square root
template<typename Type, typename=IsFloatingPoint<Type>>
constexpr Type sqrt_floating_point_helper(Type x, Type current, Type previous) {
    return (current == previous)
            ? current
            : sqrt_floating_point_helper<Type>(x, 0.5 * (current + (x / current)), current);
}

template<typename Type, typename=IsFloatingPoint<Type>>
constexpr Type sqrt_floating_point(Type x) {
    // TODO: error on negative/infinite inputs
    return (x >= 0) && (x < std::numeric_limits<Type>::infinity())
            ? sqrt_floating_point_helper<Type>(x, x, 0)
            : std::numeric_limits<Type>::quiet_NaN();
}


// Implementation for constexpr fixed-point square root
template<typename Type, typename=IsFixedPoint<Type>>
constexpr Type sqrt_fixed_point_helper(Type x, Type low, Type high) {
    if (low == high) { return low; }
    const Type mid = (low + high + 1) / 2;
    return (x / mid) < mid
            ? sqrt_fixed_point_helper<Type>(x, low, mid - 1)
            : sqrt_fixed_point_helper<Type>(x, mid, high);
}

template<typename Type, typename=IsFixedPoint<Type>>
constexpr Type sqrt_fixed_point(Type x) {
    // TODO: error on negative inputs
    return (x >= 0) ? sqrt_fixed_point_helper<Type>(x, 0, (x / 2) + 1) : 0;
}

} // namespace constexpr_impl

// Get the absolute value of arithmetic value x
template<typename Type, typename=IsArithmetic<Type>>
constexpr auto abs(Type const &x) {
    if (std::is_constant_evaluated()) {
        return constexpr_impl::abs(x);
    } else {
        // Use standard library implementation at runtime
        return std::abs(x);
    }
}

// Get the square root of arithmetic value x
template<typename Type, typename=IsArithmetic<Type>>
constexpr Type sqrt(Type const &x) {
    if (std::is_constant_evaluated()) {
        if constexpr (std::is_floating_point<Type>()) {
            return constexpr_impl::sqrt_floating_point<Type>(x);
        } else {
            return constexpr_impl::sqrt_fixed_point<Type>(x);
        }
    } else {
        // Use standard library implementation at runtime
        // TODO: might not even want to use this for integers at runtime...
        return std::sqrt(x);
    }
}

// Check approximate equality of two floating-point values a and b
template<typename Type, typename=IsFloatingPoint<Type>>
constexpr bool floating_point_eq(Type a, Type b) {
    // Configurable constants
    // These can become template parameters once floating-point NTTPs are supported
    constexpr Type epsilon = 128 * std::numeric_limits<Type>::epsilon();
    constexpr Type abs_threshold = std::numeric_limits<Type>::min();

    static_assert(epsilon >= std::numeric_limits<Type>::epsilon(),
                  "Provided epsilon must be at least the numeric limits epsilon");
    static_assert(epsilon < static_cast<Type>(1),
                  "Provided epsilon must be less than 1");

    // TODO: Add stackoverflow reference for this - it's useful reading
    if (a == b) { return true; }
    auto diff = abs(a - b); // utils::abs()
    auto norm = std::min(std::abs(a + b), std::numeric_limits<Type>::max());
    return (diff < std::max(abs_threshold, (epsilon * norm)));
}

} // namespace utils
} // namespace vec