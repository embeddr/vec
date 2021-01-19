// Basic vec class definition(s)

#pragma once

#include <algorithm>
#include <array>
#include <numeric>
#include <iostream>
#include <iterator>

#include <cmath>
#include <cstddef>

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
    static_assert((N > 0), "Dimension must be positive");
    static_assert(std::is_arithmetic<Type>::value, "Type must be arithmetic");
    using VecNT = Vec<N, Type>;
public:
    // Construct vector with zero-init elements
    Vec() : elems_{} {}

    // Construct vector from other vector
    Vec(const VecNT& other) : elems_{other.elems_} {}

    // Construct vector from parameter pack
    template<typename ...Args>
    explicit Vec(Args... args) : elems_{args...} {}

    // Get reference to element x
    Type& x() {
        return elems_[0];
    }

    // Get read-only reference to element x
    const Type& x() const {
        return elems_[0];
    }

    // Get reference to element y (defined for N > 1)
    //template<size_t checkN = N>
    typename std::enable_if<(N > 1), Type&>::type y() {
        return elems_[1];
    }

    // Get read-only reference to element y (defined for N > 1)
    template<size_t checkN = N>
    typename std::enable_if<(checkN > 1), const Type&>::type y() const {
        return elems_[1];
    }

    // Get reference to element z (defined for N > 2)
    template<size_t checkN = N>
    typename std::enable_if<(checkN > 2), Type&>::type z() {
        return elems_[2];
    }

    // Get read-only reference to element z (defined for N > 2)
    template<size_t checkN = N>
    typename std::enable_if<(checkN > 2), const Type&>::type z() const {
        return elems_[2];
    }

    // Get reference to element w (defined for N > 3)
    template<size_t checkN = N>
    typename std::enable_if<(checkN > 3), Type&>::type w() {
        return elems_[3];
    }

    // Get read-only reference to element w (defined for N > 3)
    template<size_t checkN = N>
    typename std::enable_if<(checkN > 3), const Type&>::type w() const {
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
        std::transform(elems_.cbegin(),
                       elems_.cend(),
                       rhs.elems_.cbegin(),
                       elems_.begin(),
                       std::plus<>{}); // vector sum rhs and this
    }

    // Subtract N-dimensional vector from this N-dimensional vector
    VecNT& operator-=(const VecNT& rhs) {
        std::transform(elems_.cbegin(),
                       elems_.cend(),
                       rhs.elems_.cbegin(),
                       elems_.begin(),
                       std::minus<>{}); // vector difference rhs and this
    }

    // Multiply this N-dimensional vector by scalar
    VecNT& operator*=(Type scalar) {
        for (Type& elem : elems_) {
            elem *= scalar;
        }
        return *this;
    }

    // Divide this N-dimensional vector by scalar
    VecNT& operator/=(Type scalar) {
        for (auto& elem : elems_) {
            elem /= scalar;
        }
        return *this;
    }

    // Get negation of N-dimensional vector
    friend VecNT operator-(const VecNT& rhs) {
        VecNT out{};
        std::transform(rhs.elems_.cbegin(),
                       rhs.elems_.cend(),
                       out.elems_.begin(),
                       std::negate<>());
        return out;
    }

    // Check equality of two N-dimensional vectors
    friend bool operator==(const VecNT& lhs, const VecNT& rhs) {
        // TODO: use reasonable epsilon for float comparison
        return lhs.elems_ == rhs.elems_;
    }

    // Check inequality of two N-dimensional vectors
    friend bool operator!=(const VecNT& lhs, const VecNT& rhs) {
        // TODO: use reasonable epsilon for float comparison
        return lhs.elems_ != rhs.elems_;
    }

    // Add two N-dimensional vectors
    friend VecNT operator+(const VecNT& lhs, const VecNT& rhs) {
        VecNT out{};
        std::transform(lhs.elems_.cbegin(),
                       lhs.elems_.cend(),
                       rhs.elems_.cbegin(),
                       out.elems_.begin(),
                       std::plus());
        return out;
    }

    // Subtract two N-dimensional vectors
    friend VecNT operator-(const VecNT& lhs, const VecNT& rhs) {
        VecNT out{};
        std::transform(lhs.elems_.cbegin(),
                       lhs.elems_.cend(),
                       rhs.elems_.cbegin(),
                       out.elems_.begin(),
                       std::minus());
        return out;
    }

    // Multiply N-dimensional vector by scalar
    friend VecNT operator*(const VecNT& lhs, Type rhs) {
        VecNT out{};
        auto mult_by_rhs = std::bind(std::multiplies(), _1, rhs);
        std::transform(lhs.elems_.cbegin(),
                       lhs.elems_.cend(),
                       out.elems_.begin(),
                       mult_by_rhs);
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
        std::transform(lhs.elems_.cbegin(),
                       lhs.elems_.cend(),
                       out.elems_.begin(),
                       div_by_rhs);
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
        return std::inner_product(lhs.elems_.cbegin(),
                                  lhs.elems_.cend(),
                                  rhs.elems_.cbegin(),
                                  0.0f);
    }

    // Get the cross product of two 3-dimensional vectors (defined for N == 3)
    template<size_t checkN = N>
    friend typename std::enable_if<(checkN == 3), Vec<3, Type>>::type
        cross(const VecNT&lhs, const VecNT& rhs) {
        Vec<3, Type> out{
            (lhs.y() * rhs.z() - lhs.z() * rhs.y()),
            (lhs.z() * rhs.x() - lhs.x() * rhs.z()),
            (lhs.x() * rhs.y() - lhs.y() * rhs.x())
        };
        return out;
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
        return std::inner_product(elems_.cbegin(),
                                  elems_.cend(),
                                  elems_.cbegin(),
                                  0.0f);
    }

    // Get normalization of vector
    VecNT norm() const {
        VecNT out{};
        auto div_by_inv_mag = bind(std::multiplies(), _1, (1 / mag()));
        std::transform(elems_.cbegin(),
                       elems_.cend(),
                       out.elems_.begin(),
                       div_by_inv_mag);
        return out;
    }

private:
    // Vector elements
    std::array<Type, N> elems_{};
};

} // namespace vec