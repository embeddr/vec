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

using std::size_t;

namespace vec {

// Forward declaration
template<size_t M, typename Type>
class Vec;

// Aliases for common vectors
using Vec2f = Vec<2, float>;
using Vec3f = Vec<3, float>;
using Vec4f = Vec<4, float>;

// Vector class template
template<size_t M, typename Type>
class Vec {
    static_assert((M > 0), "vector size M must be positive");
    static_assert(std::is_arithmetic<Type>::value, "Type must be arithmetic");
    using VecT = Vec<M, Type>;
public:
    // Construct vector with zero-init elements
    constexpr Vec() : elems_{} {}

    // Construct vector from other vector
    constexpr Vec(const VecT& other) : elems_{other.elems_} {}

    // Construct vector from parameter pack of elements
    template<typename ...Args>
    constexpr Vec(Type first, Args... args) : elems_{first, args...} {}

    // Construct vector and fill elements with argument value
    constexpr explicit Vec(Type fill_value) {
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

    // Get reference to element y (defined for M > 1)
    template<size_t CheckM = M>
    typename std::enable_if<(M > 1), Type&>::type y() {
        return elems_[1];
    }

    // Get read-only reference to element y (defined for M > 1)
    template<size_t CheckM = M>
    typename std::enable_if<(CheckM > 1), const Type&>::type y() const {
        return elems_[1];
    }

    // Get reference to element z (defined for M > 2)
    template<size_t CheckM = M>
    typename std::enable_if<(CheckM > 2), Type&>::type z() {
        return elems_[2];
    }

    // Get read-only reference to element z (defined for M > 2)
    template<size_t CheckM = M>
    typename std::enable_if<(CheckM > 2), const Type&>::type z() const {
        return elems_[2];
    }

    // Get reference to element w (defined for M > 3)
    template<size_t CheckM = M>
    typename std::enable_if<(CheckM > 3), Type&>::type w() {
        return elems_[3];
    }

    // Get read-only reference to element w (defined for M > 3)
    template<size_t CheckM = M>
    typename std::enable_if<(CheckM > 3), const Type&>::type w() const {
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

    // Add M-dimensional vector to this M-dimensional vector
    VecT& operator+=(const VecT& rhs) {
        std::transform(elems_.cbegin(), elems_.cend(), // this input
                       rhs.elems_.cbegin(),            // rhs input
                       elems_.begin(),                 // output
                       std::plus());                   // operation
        return *this;
    }

    // Subtract M-dimensional vector from this M-dimensional vector
    VecT& operator-=(const VecT& rhs) {
        std::transform(elems_.cbegin(), elems_.cend(), // this input
                       rhs.elems_.cbegin(),            // rhs input
                       elems_.begin(),                 // output
                       std::minus());                  // operation
        return *this;
    }

    // Multiply this M-dimensional vector by scalar
    VecT& operator*=(Type rhs) {
        auto mult_by_rhs = [rhs](Type lhs_elem) { return lhs_elem * rhs; };
        std::transform(elems_.cbegin(), elems_.cend(), // this input
                       elems_.begin(),                 // output
                       mult_by_rhs);                   // operation
        return *this;
    }

    // Divide this M-dimensional vector by scalar
    VecT& operator/=(Type rhs) {
        auto div_by_rhs = [rhs](Type lhs_elem) { return lhs_elem / rhs; };
        std::transform(elems_.cbegin(), elems_.cend(), // this input
                       elems_.begin(),                 // output
                       div_by_rhs);                    // operation
        return *this;
    }

    // Get negation of M-dimensional vector
    friend VecT operator-(const VecT& rhs) {
        VecT out;
        std::transform(rhs.elems_.cbegin(), rhs.elems_.cend(), // this input
                       out.elems_.begin(),                     // output
                       std::negate());                         // operation
        return out;
    }

    // Check equality of two M-dimensional vectors (floating point types)
    template<typename CheckType = Type>
    friend typename std::enable_if<std::is_floating_point<CheckType>::value, bool>::type
            operator==(const VecT& lhs, const VecT& rhs) {
        auto float_compare = [](const Type& lhs_elem, const Type& rhs_elem) {
            return floating_point_eq(lhs_elem, rhs_elem);
        };
        return std::equal(lhs.elems_.cbegin(), lhs.elems_.cend(), // lhs input
                          rhs.elems_.cbegin(),                    // rhs input
                          float_compare);                         // comparison
    }

    // Check equality of two M-dimensional vectors (non-floating point types)
    template<typename CheckType = Type>
    friend typename std::enable_if<!std::is_floating_point<CheckType>::value, bool>::type
    operator==(const VecT& lhs, const VecT& rhs) {
        return lhs.elems_ == rhs.elems_;
    }

    // Check inequality of two M-dimensional vectors
    friend bool operator!=(const VecT& lhs, const VecT& rhs) {
        return !(lhs == rhs); // leverage operator== implementation
    }

    // Add two M-dimensional vectors
    friend VecT operator+(const VecT& lhs, const VecT& rhs) {
        VecT out;
        std::transform(lhs.elems_.cbegin(), lhs.elems_.cend(), // lhs input
                       rhs.elems_.cbegin(),                    // rhs input
                       out.elems_.begin(),                     // output
                       std::plus());                           // operation
        return out;
    }

    // Subtract two M-dimensional vectors
    friend VecT operator-(const VecT& lhs, const VecT& rhs) {
        VecT out;
        std::transform(lhs.elems_.cbegin(), lhs.elems_.cend(), // lhs input
                       rhs.elems_.cbegin(),                    // rhs input
                       out.elems_.begin(),                     // output
                       std::minus());                          // operation
        return out;
    }

    // Multiply M-dimensional vector by scalar
    friend VecT operator*(const VecT& lhs, Type rhs) {
        VecT out;
        auto mult_by_rhs = [rhs](Type lhs_elem) { return lhs_elem * rhs; };
        std::transform(lhs.elems_.cbegin(), lhs.elems_.cend(), // lhs input
                       out.elems_.begin(),                     // output
                       mult_by_rhs);                           // operation
        return out;
    }

    // Multiply M-dimensional vector by scalar (reverse operand order)
    friend VecT operator*(Type lhs, const VecT& rhs) {
        return rhs * lhs;
    }

    // Divide M-dimensional vector by scalar
    friend VecT operator/(const VecT& lhs, Type rhs) {
        VecT out;
        auto div_by_rhs = [rhs](Type lhs_elem) { return lhs_elem / rhs; };
        std::transform(lhs.elems_.cbegin(), lhs.elems_.cend(), // lhs input
                       out.elems_.begin(),                     // output
                       div_by_rhs);                            // operation
        return out;
    }

    // Stream vector contents in human-readable form
    friend std::ostream& operator<<(std::ostream& os, const VecT& rhs) {
        std::ostream_iterator<Type> cout_it(os, " ");
        os << "[ ";
        std::copy(rhs.elems_.cbegin(), rhs.elems_.cend(), cout_it);
        os << "]";
        return os;
    }

    // Get the dot product of two M-dimensional vectors
    friend Type dot(const VecT& lhs, const VecT& rhs) {
        return std::inner_product(lhs.elems_.cbegin(), lhs.elems_.cend(), // lhs input
                                  rhs.elems_.cbegin(),                    // rhs input
                                  0.0f);                                  // init val
    }

    // Get the cross product of two 3-dimensional vectors (defined for M == 3)
    template<size_t CheckM = M>
    friend typename std::enable_if<(CheckM == 3), Vec<3, Type>>::type
            cross(const VecT&lhs, const VecT& rhs) {
        Vec<3, Type> out{
            (lhs.y() * rhs.z() - lhs.z() * rhs.y()),
            (lhs.z() * rhs.x() - lhs.x() * rhs.z()),
            (lhs.x() * rhs.y() - lhs.y() * rhs.x())
        };
        return out;
    }

    // Get the size of the vector
    size_t size() const {
        return M;
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
    VecT normalized() const {
        VecT out;
        const Type inv_mag = static_cast<Type>(1) / mag();
        auto mult_by_inv_mag = [inv_mag](Type lhs_elem) { return lhs_elem * inv_mag; };
        std::transform(elems_.cbegin(), elems_.cend(), // this input
                       out.elems_.begin(),             // output
                       mult_by_inv_mag);               // operation
        return out;
    }

    // Fill the vector with the specified value
    void fill(Type fill_value) {
        elems_.fill(fill_value);
    }

    // Clear the vector (reset to zero)
    void clear() {
        fill(0);
    }

private:
    // Vector elements
    std::array<Type, M> elems_{};
};

} // namespace vec