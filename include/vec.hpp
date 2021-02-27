// Basic vector class template definition

#pragma once

#include <algorithm>
#include <array>
#include <numeric>
#include <iomanip>
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
    static_assert((M > 0), "Vector size M must be positive");
    static_assert(std::is_signed<Type>::value, "Type must be signed, real arithmetic");
    using VecT = Vec<M, Type>;
public:
    // Construct vector with zero-init elements
    constexpr Vec() : elems_{} {}

    // Construct vector from parameter pack of elements
    template<typename ...Args>
    constexpr explicit Vec(Type first, Args... args) : elems_{first, args...} {}

    // Construct vector from other vector
    constexpr Vec(const VecT& other) : elems_{other.elems_} {}

    // Construct vector and fill elements with argument value
    constexpr explicit Vec(Type fill_value) {
        elems_.fill(fill_value);
    }

    // Construct unit vector i
    static constexpr VecT i() {
        VecT out{};
        out.elems_[0] = static_cast<Type>(1);
        return out;
    }

    // Construct unit vector j
    static constexpr VecT j() {
        VecT out{};
        out.elems_[1] = static_cast<Type>(1);
        return out;
    }

    // Construct unit vector k
    static constexpr VecT k() {
        VecT out{};
        out.elems_[2] = static_cast<Type>(1);
        return out;
    }

    // Get reference to element x
    constexpr Type& x() {
        return std::get<0>(elems_);
    }

    // Get read-only reference to element x
    constexpr const Type& x() const {
        return std::get<0>(elems_);
    }

    // Get reference to element y (defined for M > 1)
    template<size_t CheckM = M>
    constexpr typename std::enable_if<(M > 1), Type&>::type y() {
        return std::get<1>(elems_);
    }

    // Get read-only reference to element y (defined for M > 1)
    template<size_t CheckM = M>
    constexpr typename std::enable_if<(CheckM > 1), const Type&>::type y() const {
        return std::get<1>(elems_);
    }

    // Get reference to element z (defined for M > 2)
    template<size_t CheckM = M>
    constexpr typename std::enable_if<(CheckM > 2), Type&>::type z() {
        return std::get<2>(elems_);
    }

    // Get read-only reference to element z (defined for M > 2)
    template<size_t CheckM = M>
    constexpr typename std::enable_if<(CheckM > 2), const Type&>::type z() const {
        return std::get<2>(elems_);
    }

    // Get reference to element w (defined for M > 3)
    template<size_t CheckM = M>
    constexpr typename std::enable_if<(CheckM > 3), Type&>::type w() {
        return std::get<3>(elems_);
    }

    // Get read-only reference to element w (defined for M > 3)
    template<size_t CheckM = M>
    constexpr typename std::enable_if<(CheckM > 3), const Type&>::type w() const {
        return std::get<3>(elems_);
    }

    // Get reference to element by index
    constexpr Type& operator[](size_t index) {
        return elems_.at(index);
    }

    // Get read-only reference to element index
    constexpr const Type& operator[](size_t index) const {
        return elems_.at(index);
    }

    // Add M-dimensional vector to this M-dimensional vector
    constexpr VecT& operator+=(const VecT& rhs) {
        std::transform(elems_.cbegin(), elems_.cend(), // this input
                       rhs.elems_.cbegin(),            // rhs input
                       elems_.begin(),                 // output
                       std::plus());                   // operation
        return *this;
    }

    // Subtract M-dimensional vector from this M-dimensional vector
    constexpr VecT& operator-=(const VecT& rhs) {
        std::transform(elems_.cbegin(), elems_.cend(), // this input
                       rhs.elems_.cbegin(),            // rhs input
                       elems_.begin(),                 // output
                       std::minus());                  // operation
        return *this;
    }

    // Multiply this M-dimensional vector by scalar
    constexpr VecT& operator*=(Type rhs) {
        auto mult_by_rhs = [rhs](Type lhs_elem) { return lhs_elem * rhs; };
        std::transform(elems_.cbegin(), elems_.cend(), // this input
                       elems_.begin(),                 // output
                       mult_by_rhs);                   // operation
        return *this;
    }

    // Divide this M-dimensional vector by scalar
    constexpr VecT& operator/=(Type rhs) {
        auto div_by_rhs = [rhs](Type lhs_elem) { return lhs_elem / rhs; };
        std::transform(elems_.cbegin(), elems_.cend(), // this input
                       elems_.begin(),                 // output
                       div_by_rhs);                    // operation
        return *this;
    }

    // Get negation of M-dimensional vector
    friend constexpr VecT operator-(const VecT& rhs) {
        VecT out;
        std::transform(rhs.elems_.cbegin(), rhs.elems_.cend(), // this input
                       out.elems_.begin(),                     // output
                       std::negate());                         // operation
        return out;
    }

    // Check equality of two M-dimensional vectors
    friend constexpr bool operator==(const VecT& lhs, const VecT& rhs) {
        if constexpr (std::is_floating_point<Type>()) {
            // Floating-point comparison (approximate)
            auto float_compare = [](const Type& lhs_elem, const Type& rhs_elem) {
                return floating_point_eq(lhs_elem, rhs_elem);
            };
            return std::equal(lhs.elems_.cbegin(), lhs.elems_.cend(), // lhs input
                              rhs.elems_.cbegin(),                    // rhs input
                              float_compare);                         // comparison
        } else {
            // Fixed-point comparison (exact)
            return lhs.elems_ == rhs.elems_;
        }
    }

    // Check inequality of two M-dimensional vectors
    friend constexpr bool operator!=(const VecT& lhs, const VecT& rhs) {
        return !(lhs == rhs); // leverage operator== implementation
    }

    // Add two M-dimensional vectors
    friend constexpr VecT operator+(const VecT& lhs, const VecT& rhs) {
        VecT out;
        std::transform(lhs.elems_.cbegin(), lhs.elems_.cend(), // lhs input
                       rhs.elems_.cbegin(),                    // rhs input
                       out.elems_.begin(),                     // output
                       std::plus());                           // operation
        return out;
    }

    // Subtract two M-dimensional vectors
    friend constexpr VecT operator-(const VecT& lhs, const VecT& rhs) {
        VecT out;
        std::transform(lhs.elems_.cbegin(), lhs.elems_.cend(), // lhs input
                       rhs.elems_.cbegin(),                    // rhs input
                       out.elems_.begin(),                     // output
                       std::minus());                          // operation
        return out;
    }

    // Multiply M-dimensional vector by scalar
    friend constexpr VecT operator*(const VecT& lhs, Type rhs) {
        VecT out;
        auto mult_by_rhs = [rhs](Type lhs_elem) { return lhs_elem * rhs; };
        std::transform(lhs.elems_.cbegin(), lhs.elems_.cend(), // lhs input
                       out.elems_.begin(),                     // output
                       mult_by_rhs);                           // operation
        return out;
    }

    // Multiply M-dimensional vector by scalar (reverse operand order)
    friend constexpr VecT operator*(Type lhs, const VecT& rhs) {
        return rhs * lhs;
    }

    // Divide M-dimensional vector by scalar
    friend constexpr VecT operator/(const VecT& lhs, Type rhs) {
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
        os << std::fixed << std::setprecision(12) << "[ "; // TODO: configurable precision?
        std::copy(rhs.elems_.cbegin(), rhs.elems_.cend(), cout_it);
        os << "]";
        return os;
    }

    // Get the dot product of two M-dimensional vectors
    friend constexpr Type dot(const VecT& lhs, const VecT& rhs) {
        return std::inner_product(lhs.elems_.cbegin(), lhs.elems_.cend(), // lhs input
                                  rhs.elems_.cbegin(),                    // rhs input
                                  0.0f);                                  // init val
    }

    // Get the cross product of two 3-dimensional vectors (defined for M == 3)
    template<size_t CheckM = M>
    friend constexpr typename std::enable_if<(CheckM == 3), Vec<3, Type>>::type
            cross(const VecT&lhs, const VecT& rhs) {
        Vec<3, Type> out{
            (lhs.y() * rhs.z() - lhs.z() * rhs.y()),
            (lhs.z() * rhs.x() - lhs.x() * rhs.z()),
            (lhs.x() * rhs.y() - lhs.y() * rhs.x())
        };
        return out;
    }

    // Project the left M-dimensional vector onto the right M-dimensional vector
    friend constexpr VecT project_onto(const VecT& lhs, const VecT& rhs) {
        return (rhs * dot(lhs, rhs) / rhs.euclidean2());
    }

    // Project the left M-dimensional vector onto the right unit-length M-dimensional vector
    friend constexpr VecT project_onto_unit(const VecT& lhs, const VecT& rhs) {
        return (rhs * dot(lhs, rhs));
    }

    // Reject the left M-dimensional vector from the right M-dimensional vector
    friend constexpr VecT reject_from(const VecT& lhs, const VecT& rhs) {
        return lhs - project_onto(lhs, rhs);
    }

    // Reject the left M-dimensional vector from the right unit-length M-dimensional vector
    friend constexpr VecT reject_from_unit(const VecT& lhs, const VecT& rhs) {
        return lhs - project_onto_unit(lhs, rhs);
    }

    // Get the size of the vector
    constexpr size_t size() const {
        return M;
    }

    // Get manhattan (L1) norm
    constexpr Type manhattan() const {
        auto abs_accum = [](Type a, Type b) { return a + std::abs(b); };
        return std::accumulate(elems_.cbegin(),
                               elems_.cend(),
                               static_cast<Type>(0),
                               abs_accum);
    }

    // TODO: Get manhattan distance between two vectors

    // Get euclidean (L2) norm
    constexpr Type euclidean() const {
        // FIXME: std::sqrt() isn't actually constexpr! Roll your own?
        return std::sqrt(euclidean2());
    }

    // TODO: Get euclidean distance between two vectors

    // Get euclidean (L2) norm squared
    constexpr Type euclidean2() const {
        return std::inner_product(elems_.cbegin(), elems_.cend(), // this input
                                  elems_.cbegin(),                // this input (again)
                                  0.0f);                          // init val
    }

    // TODO: Get euclidean distance squared between two vectors

    // Get normalization of vector (to the provided length, default one)
    constexpr VecT normalize(Type desired_length=static_cast<Type>(1)) const {
        VecT out{*this};
        if constexpr (std::is_floating_point<Type>()) {
            return (out * (desired_length / euclidean()));
        } else {
            // Note: Too much resolution is lost for int types by calculating the scalar ratio
            //       first, but this approach also increases risk of overflow for smaller ints.
            return ((out * desired_length) / euclidean());
        }
    }

    // Fill the vector with the specified value
    constexpr void fill(Type fill_value) {
        elems_.fill(fill_value);
    }

    // Clear the vector (reset to zero)
    constexpr void clear() {
        fill(0);
    }

private:
    // Vector elements
    std::array<Type, M> elems_;
};

} // namespace vec