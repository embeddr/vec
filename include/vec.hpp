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

#include "utils.hpp"

using std::size_t;

namespace vec {

// Forward declaration
template<typename Type, size_t M>
class Vec;

// Aliases for supported lengths and types
using Vec2f = Vec<float, 2>;
using Vec3f = Vec<float, 3>;
using Vec4f = Vec<float, 4>;

using Vec2d = Vec<double, 2>;
using Vec3d = Vec<double, 3>;
using Vec4d = Vec<double, 4>;

using Vec2ld = Vec<long double, 2>;
using Vec3ld = Vec<long double, 3>;
using Vec4ld = Vec<long double, 4>;

// Concepts
template<size_t M>
concept Is2D = (M == 2);
template<size_t M>
concept Is3D = (M == 3);
template<size_t M>
concept Is4D = (M == 4);
template<size_t M>
concept IsAtLeast2D = (M >= 2);
template<size_t M>
concept IsAtLeast3D = (M >= 3);
template<size_t M, typename ...Args>
concept IsFullySpecified = (M == sizeof...(Args));

// Vector class template
template<typename Type, size_t M>
class Vec {
    // Template parameter assertions
    static_assert((M >= 2) && (M <= 4), "Vector size must be 2, 3, or 4");
    static_assert(std::is_floating_point_v<Type>, "Vector type must be floating-point");

    // Type alias for convenience
    using VecT = Vec<Type, M>;

public:
    // Construct vector with zero-init elements
    constexpr Vec() : elems_{} {}

    // Construct vector from parameter pack of elements (full specification required)
    template<typename ...Args>
    requires IsFullySpecified<M, Args...>
    constexpr Vec(Args... args) : elems_{args...} {}

    // Construct vector from other vector
    constexpr Vec(const VecT& other) : elems_{other.elems_} {}

    // Construct vector and fill elements with argument value
    // TODO: Consider making this a named static function instead
    constexpr explicit Vec(Type fill_value) {
        elems_.fill(fill_value);
    }

    /**************************************************************************
     * STATIC MEMBER FUNCTIONS
     **************************************************************************/

    // Construct unit vector i
    static constexpr VecT i() {
        VecT out{};
        std::get<0>(out.elems_) = static_cast<Type>(1);
        return out;
    }

    // Construct unit vector j
    static constexpr VecT j() {
        VecT out{};
        std::get<1>(out.elems_) = static_cast<Type>(1);
        return out;
    }

    // Construct unit vector k
    static constexpr VecT k() {
        VecT out{};
        std::get<2>(out.elems_) = static_cast<Type>(1);
        return out;
    }

    /**************************************************************************
     * MEMBER FUNCTIONS
     **************************************************************************/

    // Get the size of the vector
    constexpr size_t size() const {
        return M;
    }

    // Get reference to element at specified index (with bounds check)
    constexpr Type& at(size_t index) {
        return elems_.at(index);
    }

    // Get const reference to element at specified index (with bounds check)
    constexpr const Type& at(size_t index) const {
        return elems_.at(index);
    }

    // Get begin iterator for underlying array
    constexpr auto begin() {
        return elems_.begin();
    }

    // Get const begin iterator for underlying array
    constexpr auto cbegin() const {
        return elems_.cbegin();
    }

    // Get end iterator for underlying array
    constexpr auto end() {
        return elems_.end();
    }

    // Get const end iterator for underlying array
    constexpr auto cend() const {
        return elems_.cend();
    }

    // Get reference to element x
    constexpr Type& x() {
        return std::get<0>(elems_);
    }

    // Get const reference to element x
    constexpr const Type& x() const {
        return std::get<0>(elems_);
    }

    // Get reference to element y
    constexpr Type& y() requires IsAtLeast2D<M> {
        return std::get<1>(elems_);
    }

    // Get const reference to element y
    constexpr const Type& y() const requires IsAtLeast2D<M> {
        return std::get<1>(elems_);
    }

    // Get reference to element z
    constexpr Type& z() requires IsAtLeast3D<M> {
        return std::get<2>(elems_);
    }

    // Get const reference to element z
    constexpr const Type& z() const requires IsAtLeast3D<M> {
        return std::get<2>(elems_);
    }

    // Get reference to element w
    constexpr Type& w() requires Is4D<M> {
        return std::get<3>(elems_);
    }

    // Get const reference to element w
    constexpr const Type& w() const requires Is4D<M> {
        return std::get<3>(elems_);
    }

    // Get manhattan (L1) norm
    constexpr Type manhattan() const {
        auto abs_accum = [](Type a, Type b) { return a + utils::abs(b); };
        return std::accumulate(elems_.cbegin(),
                               elems_.cend(),
                               static_cast<Type>(0),
                               abs_accum);
    }

    // Get euclidean (L2) norm
    constexpr Type euclidean() const {
        return utils::sqrt(euclidean2());
    }

    // Get euclidean (L2) norm squared
    constexpr Type euclidean2() const {
        return dot(*this, *this);
    }

    // Get normalization of vector (to the provided length, default one)
    [[nodiscard]] constexpr VecT normalize(Type desired_length=static_cast<Type>(1)) const {
        VecT out{*this};
        out.normalize_in_place(desired_length);
        return out;
    }

    // Normalize vector in-place (to the provided length, default one)
    constexpr void normalize_in_place(Type desired_length=static_cast<Type>(1)) {
        *this *= (desired_length / euclidean());
    }


    // Fill the vector with the specified value
    constexpr void fill(Type fill_value) {
        elems_.fill(fill_value);
    }

    // Clear the vector (reset to zero)
    constexpr void clear() {
        fill(0);
    }

    /**************************************************************************
     * MEMBER OPERATORS
     **************************************************************************/

    // Get reference to element by index (no bounds check)
    constexpr Type& operator[](size_t index) {
        return elems_[index];
    }

    // Get const reference to element by index (no bounds check)
    constexpr const Type& operator[](size_t index) const {
        return elems_[index];
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

    /**************************************************************************
     * FRIEND OPERATORS
     **************************************************************************/

    // Get negation of M-dimensional vector
    friend constexpr VecT operator-(const VecT& rhs) {
        VecT out;
        std::transform(rhs.elems_.cbegin(), rhs.elems_.cend(), // rhs input
                       out.elems_.begin(),                     // output
                       std::negate());                         // operation
        return out;
    }

    // Check equality of two M-dimensional vectors
    friend constexpr bool operator==(const VecT& lhs, const VecT& rhs) {
        auto float_compare = [](const Type& lhs_elem, const Type& rhs_elem) {
            return utils::floating_point_eq(lhs_elem, rhs_elem);
        };
        return std::equal(lhs.elems_.cbegin(), lhs.elems_.cend(), // lhs input
                          rhs.elems_.cbegin(),                    // rhs input
                          float_compare);                         // comparison
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
        std::ostream_iterator<Type> cout_it(os, "  ");
        os << "[  ";
        std::copy(rhs.elems_.cbegin(), rhs.elems_.cend(), cout_it);
        os << "]";
        return os;
    }

    /**************************************************************************
     * FRIEND FUNCTIONS
     **************************************************************************/

    // Get the dot product of M-dimensional vectors a and b
    friend constexpr Type dot(const VecT& a, const VecT& b) {
        return std::inner_product(a.cbegin(), a.cend(),  // a input
                                  b.cbegin(),            // b input
                                  static_cast<Type>(0)); // init val
    }

    // Get the cross product of 3-dimensional vectors a and b
    friend constexpr VecT cross(const VecT& a, const VecT& b) requires Is3D<M> {
        VecT out{
            static_cast<Type>(a.y() * b.z() - a.z() * b.y()),
            static_cast<Type>(a.z() * b.x() - a.x() * b.z()),
            static_cast<Type>(a.x() * b.y() - a.y() * b.x())
        };
        return out;
    }

    // Get the manhattan distance between M-dimensional vectors a and b
    friend constexpr Type manhattan(const VecT& a, const VecT& b) {
        return VecT{a-b}.manhattan();
    }

    // Get the euclidean distance between M-dimensional vectors a and b
    friend constexpr Type euclidean(const VecT& a, const VecT& b) {
        return VecT{a-b}.euclidean();
    }

    // Get the euclidean distance squared between M-dimensional vectors a and b
    friend constexpr Type euclidean2(const VecT& a, const VecT& b) {
        return VecT{a-b}.euclidean2();
    }

    // Get the vector triple product for 3-dimensional vectors a, b, and c
    friend constexpr VecT vector_triple(const VecT& a, const VecT& b, const VecT& c)
    requires Is3D<M> {
        return cross(a, cross(b, c));
    }

    // Get the scalar triple product for 3-dimensional vectors a, b, and c
    friend constexpr Type scalar_triple(const VecT& a, const VecT& b, const VecT& c)
    requires Is3D<M> {
        return dot(cross(a, b), c);
    }

    // Project M-dimensional vector a onto M-dimensional vector b
    friend constexpr VecT project_onto(const VecT& a, const VecT& b) {
        return (b * dot(a, b) / b.euclidean2());
    }

    // Project M-dimensional vector a onto M-dimensional unit-length vector b
    friend constexpr VecT project_onto_unit(const VecT& a, const VecT& b) {
        return (b * dot(a, b));
    }

    // Reject M-dimensional vector a from M-dimensional vector b
    friend constexpr VecT reject_from(const VecT& a, const VecT& b) {
        return a - project_onto(a, b);
    }

    // Reject M-dimensional vector a from M-dimensional unit-length vector b
    friend constexpr VecT reject_from_unit(const VecT& a, const VecT& b) {
        return a - project_onto_unit(a, b);
    }

private:
    // Vector elements
    std::array<Type, M> elems_;
};

} // namespace vec