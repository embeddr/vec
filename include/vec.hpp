// Basic vector class template definition

#pragma once

#include <algorithm>
#include <array>
#include <numeric>
#include <iostream>
#include <iterator>
#include <type_traits>

#include <cmath>
#include <cstddef>

#include "include/utils.hpp"

using std::placeholders::_1;
using std::size_t;

namespace vec {

// Forward declaration
template<size_t N, typename Type>
class Vec;

// Aliases for common vectors
using Vec2f = Vec<2, float>;
using Vec3f = Vec<3, float>;
using Vec4f = Vec<4, float>;

// Vector class template
template<size_t N, typename Type>
class Vec {
    static_assert((N > 0), "Size N must be positive");
    static_assert(std::is_arithmetic<Type>::value, "Type must be arithmetic");
    using VecNT = Vec<N, Type>; // TODO: name VecT instead?
public:
    // Construct vector with zero-init elements
    Vec() : elems_{} {}

    // Construct vector from other vector
    Vec(const VecNT& other) : elems_{other.elems_} {}

    // Construct vector from parameter pack of elements
    template<typename ...Args>
    Vec(Type first, Args... args) : elems_{first, args...} {}

    // Construct vector and fill elements with argument value
    explicit Vec(Type fill_value) {
        elems_.fill(fill_value);
    }

    // Get reference to element x
    Type& x() {
        return elems_[0];
    }

    // Get read-only reference to element x
    const Type& x() const {
        return elems_[0];
    }

    // Get reference to element y (defined for N > 1)
    template<size_t CheckN = N>
    typename std::enable_if<(N > 1), Type&>::type y() {
        return elems_[1];
    }

    // Get read-only reference to element y (defined for N > 1)
    template<size_t CheckN = N>
    typename std::enable_if<(CheckN > 1), const Type&>::type y() const {
        return elems_[1];
    }

    // Get reference to element z (defined for N > 2)
    template<size_t CheckN = N>
    typename std::enable_if<(CheckN > 2), Type&>::type z() {
        return elems_[2];
    }

    // Get read-only reference to element z (defined for N > 2)
    template<size_t CheckN = N>
    typename std::enable_if<(CheckN > 2), const Type&>::type z() const {
        return elems_[2];
    }

    // Get reference to element w (defined for N > 3)
    template<size_t CheckN = N>
    typename std::enable_if<(CheckN > 3), Type&>::type w() {
        return elems_[3];
    }

    // Get read-only reference to element w (defined for N > 3)
    template<size_t CheckN = N>
    typename std::enable_if<(CheckN > 3), const Type&>::type w() const {
        return elems_[3];
    }

    // Get reference to element by index
    Type& operator[](size_t index) {
        return elems_.at(index);
    }

    // Get read-only reference to element index
    const Type& operator[](size_t index) const {
        return elems_.at(index);
    }

    // Add N-dimensional vector to this N-dimensional vector
    VecNT& operator+=(const VecNT& rhs) {
        std::transform(elems_.cbegin(), elems_.cend(), // this input
                       rhs.elems_.cbegin(),            // rhs input
                       elems_.begin(),                 // output
                       std::plus());                   // operation
        return *this;
    }

    // Subtract N-dimensional vector from this N-dimensional vector
    VecNT& operator-=(const VecNT& rhs) {
        std::transform(elems_.cbegin(), elems_.cend(), // this input
                       rhs.elems_.cbegin(),            // rhs input
                       elems_.begin(),                 // output
                       std::minus());                  // operation
        return *this;
    }

    // Multiply this N-dimensional vector by scalar
    VecNT& operator*=(Type scalar) {
        auto mult_by_scalar = std::bind(std::multiplies(), _1, scalar);
        std::transform(elems_.cbegin(), elems_.cend(), // this input
                       elems_.begin(),                 // output
                       mult_by_scalar);                // operation
        return *this;
    }

    // Divide this N-dimensional vector by scalar
    VecNT& operator/=(Type scalar) {
        auto div_by_scalar = std::bind(std::divides(), _1, scalar);
        std::transform(elems_.cbegin(), elems_.cend(), // this input
                       elems_.begin(),                 // output
                       div_by_scalar);                 // operation
        return *this;
    }

    // Get negation of N-dimensional vector
    friend VecNT operator-(const VecNT& rhs) {
        VecNT out{};
        std::transform(rhs.elems_.cbegin(), rhs.elems_.cend(), // this input
                       out.elems_.begin(),                     // output
                       std::negate());                         // operation
        return out;
    }

    // Check equality of two N-dimensional vectors (floating point types)
    template<typename CheckType = Type>
    friend typename std::enable_if<std::is_floating_point<CheckType>::value, bool>::type
            operator==(const VecNT& lhs, const VecNT& rhs) {
        auto float_compare = [](const Type& a, const Type& b) {
            return floating_point_eq(a, b);
        };
        return std::equal(lhs.elems_.cbegin(), lhs.elems_.cend(), // lhs input
                          rhs.elems_.cbegin(),                    // rhs input
                          float_compare);                         // operation
    }

    // Check equality of two N-dimensional vectors (non-floating point types)
    template<typename CheckType = Type>
    friend typename std::enable_if<!std::is_floating_point<CheckType>::value, bool>::type
    operator==(const VecNT& lhs, const VecNT& rhs) {
        return lhs.elems_ == rhs.elems_;
    }

    // Check inequality of two N-dimensional vectors
    friend bool operator!=(const VecNT& lhs, const VecNT& rhs) {
        return !(lhs == rhs); // leverage operator== implementation
    }

    // Add two N-dimensional vectors
    friend VecNT operator+(const VecNT& lhs, const VecNT& rhs) {
        VecNT out{};
        std::transform(lhs.elems_.cbegin(), lhs.elems_.cend(), // lhs input
                       rhs.elems_.cbegin(),                    // rhs input
                       out.elems_.begin(),                     // output
                       std::plus());                           // operation
        return out;
    }

    // Subtract two N-dimensional vectors
    friend VecNT operator-(const VecNT& lhs, const VecNT& rhs) {
        VecNT out{};
        std::transform(lhs.elems_.cbegin(), lhs.elems_.cend(), // lhs input
                       rhs.elems_.cbegin(),                    // rhs input
                       out.elems_.begin(),                     // output
                       std::minus());                          // operation
        return out;
    }

    // Multiply N-dimensional vector by scalar
    friend VecNT operator*(const VecNT& lhs, Type rhs) {
        VecNT out{};
        auto mult_by_rhs = std::bind(std::multiplies(), _1, rhs);
        std::transform(lhs.elems_.cbegin(), lhs.elems_.cend(), // lhs input
                       out.elems_.begin(),                     // output
                       mult_by_rhs);                           // operation
        return out;
    }

    // Multiply N-dimensional vector by scalar (reverse operand order)
    friend VecNT operator*(Type lhs, const VecNT& rhs) {
        return rhs * lhs;
    }

    // Divide N-dimensional vector by scalar
    friend VecNT operator/(const VecNT& lhs, Type rhs) {
        VecNT out{};
        auto div_by_rhs = bind(std::divides(), _1, rhs);
        std::transform(lhs.elems_.cbegin(), lhs.elems_.cend(), // lhs input
                       out.elems_.begin(),                     // output
                       div_by_rhs);                            // operation
        return out;
    }

    // Stream vector contents in human-readable form
    friend std::ostream& operator<<(std::ostream& os, const VecNT& rhs) {
        std::ostream_iterator<Type> cout_it(os, " ");
        os << "[ ";
        std::copy(rhs.elems_.cbegin(), rhs.elems_.cend(), cout_it);
        os << "]";
        return os;
    }

    // Get the dot product of two N-dimensional vectors
    friend Type dot(const VecNT& lhs, const VecNT& rhs) {
        return std::inner_product(lhs.elems_.cbegin(), lhs.elems_.cend(), // lhs input
                                  rhs.elems_.cbegin(),                    // rhs input
                                  0.0f);                                  // init val
    }

    // Get the cross product of two 3-dimensional vectors (defined for N == 3)
    template<size_t CheckN = N>
    friend typename std::enable_if<(CheckN == 3), Vec<3, Type>>::type
            cross(const VecNT&lhs, const VecNT& rhs) {
        Vec<3, Type> out{
            (lhs.y() * rhs.z() - lhs.z() * rhs.y()),
            (lhs.z() * rhs.x() - lhs.x() * rhs.z()),
            (lhs.x() * rhs.y() - lhs.y() * rhs.x())
        };
        return out;
    }

    // Get the size of the vector
    size_t size() const {
        return N;
    }

    // Get manhattan distance (L1-norm)
    Type hat() const {
        return std::accumulate(elems_.cbegin(),
                               elems_.cend(),
                               0);
    }

    // Get vector magnitude (L2-norm)
    Type mag() const {
        return std::sqrt(mag2());
    }

    // Get vector magnitude squared (L2-norm squared)
    Type mag2() const {
        return std::inner_product(elems_.cbegin(), elems_.cend(), // this input
                                  elems_.cbegin(),                // this input (again)
                                  0.0f);                          // init val
    }

    // Get normalization of vector
    VecNT normalized() const {
        VecNT out{};
        auto div_by_inv_mag = bind(std::multiplies(), _1, (1 / mag()));
        std::transform(elems_.cbegin(), elems_.cend(), // this input
                       out.elems_.begin(),             // output
                       div_by_inv_mag);                // operation
        return out;
    }

    // Fill the vector with the specified value
    void fill(Type fill_value) {
        elems_.fill(fill_value);
    }

    // Clear the vector (reset to zero)
    void clear() {
        elems_.fill(0);
    }

private:
    // Vector elements
    std::array<Type, N> elems_{};
};

} // namespace vec