// Basic matrix class template definition

#pragma once

#include <algorithm>
#include <array>
#include <experimental/iterator>
#include <type_traits>

#include "vec.hpp"

using std::size_t;

namespace vec {

// Forward declaration
template<typename Type, size_t M>
class Mat;

// Aliases for supported lengths and types
using Mat22f = Mat<float, 2>;
using Mat33f = Mat<float, 3>;
using Mat44f = Mat<float, 4>;

using Mat22d = Mat<double, 2>;
using Mat33d = Mat<double, 3>;
using Mat44d = Mat<double, 4>;

using Mat22ld = Mat<long double, 2>;
using Mat33ld = Mat<long double, 3>;
using Mat44ld = Mat<long double, 4>;

// Matrix class template
template<typename Type, size_t M>
class Mat {
    // Template parameter assertions
    static_assert((M >= 2) && (M <= 4), "Matrix size must be 2x2, 3x3, or 4x4");
    static_assert(std::is_floating_point_v<Type>, "Type must be floating-point");

    // Type aliases for convenience
    using MatT = Mat<Type, M>;
    using VecT = Vec<Type, M>;

public:
    // Construct matrix with zero-init elements
    constexpr Mat() : rows_{} {}

    // Construct matrix from row vectors (2x2 specialization)
    constexpr Mat(const VecT& v0, const VecT& v1) requires Is2D<M>
            : rows_{v0, v1} {}

    // Construct matrix from row vectors (3x3 specialization)
    constexpr Mat(const VecT& v0, const VecT& v1, const VecT& v2) requires Is3D<M>
            : rows_{v0, v1, v2} {}

    // Construct matrix from row vectors (4x4 specialization)
    constexpr Mat(const VecT& v0, const VecT& v1, const VecT& v2, const VecT& v3) requires Is4D<M>
            : rows_{v0, v1, v2, v3} {}

    // Construct matrix from individual elements (2x2 specialization)
    constexpr Mat(Type e00, Type e01,
                  Type e10, Type e11) requires Is2D<M>
        : rows_{{e00, e01},
                {e10, e11}} {}

    // Construct matrix from individual elements (3x3 specialization)
    constexpr Mat(Type e00, Type e01, Type e02,
                  Type e10, Type e11, Type e12,
                  Type e20, Type e21, Type e22) requires Is3D<M>
            : rows_{{e00, e01, e02},
                    {e10, e11, e12},
                    {e20, e21, e22}} {}

    // Construct matrix from individual elements (4x4 specialization)
    constexpr Mat(Type e00, Type e01, Type e02, Type e03,
                  Type e10, Type e11, Type e12, Type e13,
                  Type e20, Type e21, Type e22, Type e23,
                  Type e30, Type e31, Type e32, Type e33) requires Is4D<M>
            : rows_{{e00, e01, e02, e03},
                    {e10, e11, e12, e13},
                    {e20, e21, e22, e23},
                    {e30, e31, e32, e33}} {}

    // Construct matrix from other matrix
    constexpr Mat(const MatT& other) : rows_(other.rows_) {}

    // Construct MxM matrix filled with argument value
    constexpr explicit Mat(Type fill_value) {
        for (auto& row : rows_) {
            row.fill(fill_value);
        }
    }

    /**************************************************************************
     * STATIC MEMBER FUNCTIONS
     **************************************************************************/

    // Create a MxM diagonal matrix from the provided diagonal vector
    constexpr static MatT diagonal(VecT vec) {
        MatT out{};
        for (int i = 0; i < M; i++) {
            out(i, i) = vec[i];
        }
        return out;
    }

    // Get the MxM identity matrix
    constexpr static MatT identity() {
        return diagonal(VecT(static_cast<Type>(1)));
    }

    /**************************************************************************
     * MEMBER FUNCTIONS
     **************************************************************************/

    // Get the size of the matrix (always square)
    constexpr size_t size() const {
        return M;
    }

    // Get reference to element at index (i, j) with bounds checks
    constexpr Type& at(size_t i, size_t j) {
        return rows_.at(i).at(j);
    }

    // Get read-only reference to element at index (i, j) with bounds checks
    constexpr const Type& at(size_t i, size_t j) const {
        return rows_.at(i).at(j);
    }

    // Get reference to row vector at index i with bounds check
    constexpr VecT& at(size_t i) {
        return rows_.at(i);
    }

    // Get read-only reference to row vector at index i with bounds check
    constexpr const VecT& at(size_t i) const {
        return rows_.at(i);
    }

    // Get begin iterator for underlying array of rows
    constexpr auto begin() {
        return rows_.begin();
    }

    // Get const begin iterator for underlying array of rows
    constexpr auto cbegin() const {
        return rows_.cbegin();
    }

    // Get end iterator for underlying array of rows
    constexpr auto end() {
        return rows_.end();
    }

    // Get const end iterator for underlying array of rows
    constexpr auto cend() const {
        return rows_.cend();
    }

    // Get the matrix determinant (2x2 specialization)
    constexpr Type determinant() const requires Is2D<M> {
        const MatT& m = *this;
        return m(0,0) * m(1,1) - m(0,1) * m(1,0);
    }

    // Get the matrix determinant (3x3 specialization)
    constexpr Type determinant() const requires Is3D<M> {
        const MatT& m = *this;
        return m(0,0) * (m(1,1) * m(2,2) - m(1,2) * m(2,1))
             + m(0,1) * (m(1,2) * m(2,0) - m(1,0) * m(2,2))
             + m(0,2) * (m(1,0) * m(2,1) - m(1,1) * m(2,0));
    }

    // Get the matrix determinant (4x4 specialization)
    constexpr Type determinant() const requires Is4D<M> {
        const MatT& m = *this;
        return (m(0,3) * m(1,2) * m(2,1) * m(3,0)) - (m(0,2) * m(1,3) * m(2,1) * m(3,0)) -
               (m(0,3) * m(1,1) * m(2,2) * m(3,0)) + (m(0,1) * m(1,3) * m(2,2) * m(3,0)) +
               (m(0,2) * m(1,1) * m(2,3) * m(3,0)) - (m(0,1) * m(1,2) * m(2,3) * m(3,0)) -
               (m(0,3) * m(1,2) * m(2,0) * m(3,1)) + (m(0,2) * m(1,3) * m(2,0) * m(3,1)) +
               (m(0,3) * m(1,0) * m(2,2) * m(3,1)) - (m(0,0) * m(1,3) * m(2,2) * m(3,1)) -
               (m(0,2) * m(1,0) * m(2,3) * m(3,1)) + (m(0,0) * m(1,2) * m(2,3) * m(3,1)) +
               (m(0,3) * m(1,1) * m(2,0) * m(3,2)) - (m(0,1) * m(1,3) * m(2,0) * m(3,2)) -
               (m(0,3) * m(1,0) * m(2,1) * m(3,2)) + (m(0,0) * m(1,3) * m(2,1) * m(3,2)) +
               (m(0,1) * m(1,0) * m(2,3) * m(3,2)) - (m(0,0) * m(1,1) * m(2,3) * m(3,2)) -
               (m(0,2) * m(1,1) * m(2,0) * m(3,3)) + (m(0,1) * m(1,2) * m(2,0) * m(3,3)) +
               (m(0,2) * m(1,0) * m(2,1) * m(3,3)) - (m(0,0) * m(1,2) * m(2,1) * m(3,3)) -
               (m(0,1) * m(1,0) * m(2,2) * m(3,3)) + (m(0,0) * m(1,1) * m(2,2) * m(3,3));
    }

    // Get the MxM inverse of this MxM matrix (2x2 specialization)
    constexpr MatT inverse() const requires Is2D<M> {
        // TODO: handle determinant() == 0
        const MatT& m = *this;
        return MatT{{m(1,1), -m(0,1)}, {-m(1,0), m(0,0)}} / determinant();
    }

    // Get the MxM inverse of this MxM matrix (3x3 specialization)
    constexpr MatT inverse() const requires Is3D<M> {
        const MatT &m = *this;

        const VecT col0 = cross(m[1], m[2]);
        const VecT col1 = cross(m[2], m[0]);
        const VecT col2 = cross(m[0], m[1]);

        // TODO: handle determinant() == 0
        const Type inv_det = static_cast<Type>(1) / dot(col2, m[2]);
        auto scale = [inv_det](auto elem) { return elem * inv_det; };

        return MatT{{scale(col0.x()), scale(col1.x()), scale(col2.x())},
                    {scale(col0.y()), scale(col1.y()), scale(col2.y())},
                    {scale(col0.z()), scale(col1.z()), scale(col2.z())}
        };
    }

    // Get the MxM inverse of this MxM matrix (4x4 specialization)
    constexpr MatT inverse() const requires Is4D<M> {
        const MatT &m = *this;

        const VecT& a = m[0];
        const VecT& b = m[1];
        const VecT& c = m[2];
        const VecT& d = m[3];

        const float& x = m(0, 3);
        const float& y = m(1, 3);
        const float& z = m(2, 3);
        const float& w = m(3, 3);

        using Vec3T = Vec<Type, 3>;
        Vec3T s = cross_slice(a, b);
        Vec3T t = cross_slice(c, d);
        Vec3T u = (a * y) - (b * x); // 3D <- 4D
        Vec3T v = (c * w) - (d * z); // 3D <- 4D

        // TODO: handle determinant() == 0
        const float inv_det = static_cast<Type>(1) / (dot(s, v) + dot(t, u));

        s *= inv_det;
        t *= inv_det;
        u *= inv_det;
        v *= inv_det;

        const Vec3T col0 = cross(b, v) + (t * y);
        const Vec3T col1 = cross(v, a) - (t * x);
        const Vec3T col2 = cross(d, u) + (s * w);
        const Vec3T col3 = cross(u, c) - (s * z);

        return MatT{
            {col0.x(), col1.x(), col2.x(), col3.x()},
            {col0.y(), col1.y(), col2.y(), col3.y()},
            {col0.z(), col1.z(), col2.z(), col3.z()},
            {-dot(b, t), dot(a, t), -dot(d, s), dot(c, s)},
        };
    }

    // Get the MxM transpose of this MxM matrix
    constexpr MatT transpose() const {
        MatT out;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                out(j, i) = (*this)(i, j);
            }
        }
        return out;
    }

    // Fill this matrix with the specified value
    constexpr void fill(Type fill_value) {
        for (auto& row : rows_) {
            row.fill(fill_value);
        }
    }

    // Clear this matrix (reset to zero)
    constexpr void clear() {
        fill(0);
    }

    /**************************************************************************
     * MEMBER OPERATORS
     **************************************************************************/

    // Get reference to row at index i without bounds checks
    constexpr VecT& operator[](size_t i) {
        return rows_[i];
    }

    // Get read-only reference to row at index i without bounds checks
    constexpr const VecT& operator[](size_t i) const {
        return rows_[i];
    }

    // Get reference to element at index (i, j) without bounds checks
    constexpr Type& operator()(size_t i, size_t j) {
        return rows_[i][j];
    }

    // Get read-only reference to element at index (i, j) without bounds checks
    constexpr const Type& operator()(size_t i, size_t j) const {
        return rows_[i][j];
    }

    // Add MxM matrix to this MxM matrix
    constexpr MatT& operator+=(const MatT& rhs) {
        std::transform(cbegin(), cend(), // this input
                       rhs.cbegin(),     // rhs input
                       begin(),          // output
                       std::plus());     // operation
        return *this;
    }

    // Subtract MxM matrix from this MxM matrix
    constexpr MatT& operator-=(const MatT& rhs) {
        std::transform(cbegin(), cend(), // this input
                       rhs.cbegin(),     // rhs input
                       begin(),          // output
                       std::minus());    // operation
        return *this;
    }

    // Multiply this MxM matrix by scalar
    constexpr MatT& operator*=(Type rhs) {
        auto mult_by_rhs = [rhs](auto& lhs_elem) { return lhs_elem * rhs; };
        std::transform(cbegin(), cend(), // this input
                       begin(),          // output
                       mult_by_rhs);     // operation
        return *this;
    }

    // TODO: operator*= for matrix (since they're all square)

    // Divide this MxM matrix by scalar
    constexpr MatT& operator/=(Type rhs) {
        auto div_by_rhs = [rhs](auto& lhs_elem) { return lhs_elem * rhs; };
        std::transform(cbegin(), cend(), // this input
                       begin(),          // output
                       div_by_rhs);      // operation
        return *this;
    }

    /**************************************************************************
     * FRIEND OPERATORS
     **************************************************************************/

    // Get negation of MxM matrix
    friend constexpr MatT operator-(const MatT& rhs) {
        MatT out;
        std::transform(rhs.cbegin(), rhs.cend(), // rhs input
                       out.begin(),              // output
                       std::negate());           // operation
        return out;
    }

    // Check equality of two MxM matrices
    friend constexpr bool operator==(const MatT& lhs, const MatT& rhs) {
        return lhs.rows_ == rhs.rows_;
    }

    // Check inequality of two MxM matrices
    friend constexpr bool operator!=(const MatT& lhs, const MatT& rhs) {
        return lhs.rows_ != rhs.rows_;
    }

    // Add two MxM matrices
    friend constexpr MatT operator+(const MatT& lhs, const MatT& rhs) {
        MatT out;
        std::transform(lhs.cbegin(), lhs.cend(), // lhs input
                       rhs.cbegin(),             // rhs input
                       out.begin(),              // output
                       std::plus());             // operation
        return out;
    }

    // Subtract two MxM matrices
    friend constexpr MatT operator-(const MatT& lhs, const MatT& rhs) {
        MatT out;
        std::transform(lhs.cbegin(), lhs.cend(), // lhs input
                       rhs.cbegin(),             // rhs input
                       out.begin(),              // output
                       std::minus());            // operation
        return out;
    }

    // Multiply MxM matrix by scalar
    friend constexpr MatT operator*(const MatT& lhs, Type rhs) {
        MatT out;
        auto mult_by_rhs = [rhs](auto& lhs_elem) { return lhs_elem * rhs; };
        std::transform(lhs.cbegin(), lhs.cend(), // lhs input
                       rhs.cbegin(),             // rhs input
                       out.begin(),              // output
                       mult_by_rhs);             // operation
    }

    // Multiply MxM matrix by scalar (reverse operand order)
    friend constexpr MatT operator*(Type lhs, const MatT& rhs) {
        return rhs * lhs;
    }

    // TODO: Multiply MxM matrix by M-dimensional vector

    // Get MxM product of two MxM matrices
    friend constexpr MatT operator*(const MatT& lhs, const MatT& rhs) {
        // TODO: Can we do this without raw loops?
        // NOTE: SO suggests loop order matters here (for caching)
        auto calc_element = [lhs, rhs](size_t i, size_t j) {
            Type sum = 0;
            for (int k = 0; k < M; k++) {
                sum += lhs(i, k) * rhs(k, j);
            }
            return sum;
        };
        MatT out;
        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < M; j++) {
                out(i, j) = calc_element(i, j);
            }
        }
        return out;
    }

    // Divide MxM matrix by scalar
    friend constexpr MatT operator/(const MatT& lhs, Type rhs) {
        MatT out;
        auto div_by_rhs = [rhs](auto& lhs_elem) { return lhs_elem / rhs; };
        std::transform(lhs.cbegin(), lhs.cend(), // lhs input
                       out.begin(),              // output
                       div_by_rhs);              // operation
       return out;
    }

    // Stream matrix contents in readable form (row by row)
    friend std::ostream& operator<<(std::ostream& os, const MatT& rhs) {
        auto joiner = std::experimental::make_ostream_joiner(os, "\n ");
        os << "\n[";
        std::copy(rhs.rows_.cbegin(), rhs.rows_.cend(), joiner);
        os << "]";
        return os;
    }

private:
    // Matrix rows
    std::array<VecT, M> rows_;
};

} // namespace vec