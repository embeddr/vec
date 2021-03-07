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
template<size_t M, typename Type>
class Mat;

// Aliases for supported lengths and types
using Mat22f = Mat<2, float>;
using Mat33f = Mat<3, float>;
using Mat44f = Mat<4, float>;

using Mat22d = Mat<2, double>;
using Mat33d = Mat<3, double>;
using Mat44d = Mat<4, double>;

using Mat22ld = Mat<2, long double>;
using Mat33ld = Mat<3, long double>;
using Mat44ld = Mat<4, long double>;

// Matrix class template
template<size_t M, typename Type>
class Mat {
    // Template parameter assertions
    static_assert((M >= 2) && (M <= 4), "Matrix size must be 2x2, 3x3, or 4x4");
    static_assert(std::is_floating_point_v<Type>, "Type must be floating-point");

    // Type aliases for convenience
    using MatT = Mat<M, Type>;
    using VecT = Vec<M, Type>;

public:
    // Construct matrix with zero-init elements
    constexpr Mat() : cols_{} {}

    // Construct matrix from other matrix
    constexpr Mat(const MatT& other) : cols_(other.cols_) {}

    // Construct matrix from column vectors (2x2 specialization)
    constexpr Mat(const VecT& v0, const VecT& v1) requires Is2D<M>
            : cols_{v0, v1} {}

    // Construct matrix from column vectors (3x3 specialization)
    constexpr Mat(const VecT& v0, const VecT& v1, const VecT& v2) requires Is3D<M>
            : cols_{v0, v1, v2} {}

    // Construct matrix from column vectors (4x4 specialization)
    constexpr Mat(const VecT& v0, const VecT& v1, const VecT& v2, const VecT& v3) requires Is4D<M>
            : cols_{v0, v1, v2, v3} {}

    // TODO: Construct matrix from list of individual elements in column_major order?

    // Construct MxM matrix filled with argument value
    constexpr explicit Mat(Type fill_value) {
        for (auto& col : cols_) {
            col.fill(fill_value);
        }
    }

    /**************************************************************************
     * STATIC MEMBER FUNCTIONS
     **************************************************************************/

    // Create a MxM diagonal matrix from the provided vector
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
    [[nodiscard]] constexpr size_t size() const {
        return M;
    }

    // Get reference to element at location (m, n) in the matrix
    constexpr Type& at(size_t m, size_t n) {
        return cols_.at(m)[n];
    }

    // Get read-only reference to element at location (m, n) in the matrix
    constexpr const Type& at(size_t m, size_t n) const {
        return cols_.at(m)[n];
    }

    // Get the matrix determinant (2x2 specialization)
    constexpr Type determinant() const requires Is2D<M> {
        return at(0,0) * at(1,1) - at(0,1) * at(1,0);
    }

    // Get the matrix determinant (3x3 specialization)
    constexpr Type determinant() const requires Is3D<M> {
        return at(0,0) * (at(1,1) * at(2,2) - at(1,2) * at(2,1))
             + at(0,1) * (at(1,2) * at(2,0) - at(1,0) * at(2,2))
             + at(0,2) * (at(1,0) * at(2,1) - at(1,1) * at(2,0));
    }

    // Get the matrix determinant (4x4 specialization)
    constexpr Type determinant() const requires Is4D<M> {
        return (at(0,3) * at(1,2) * at(2,1) * at(3,0)) - (at(0,2) * at(1,3) * at(2,1) * at(3,0)) -
               (at(0,3) * at(1,1) * at(2,2) * at(3,0)) + (at(0,1) * at(1,3) * at(2,2) * at(3,0)) +
               (at(0,2) * at(1,1) * at(2,3) * at(3,0)) - (at(0,1) * at(1,2) * at(2,3) * at(3,0)) -
               (at(0,3) * at(1,2) * at(2,0) * at(3,1)) + (at(0,2) * at(1,3) * at(2,0) * at(3,1)) +
               (at(0,3) * at(1,0) * at(2,2) * at(3,1)) - (at(0,0) * at(1,3) * at(2,2) * at(3,1)) -
               (at(0,2) * at(1,0) * at(2,3) * at(3,1)) + (at(0,0) * at(1,2) * at(2,3) * at(3,1)) +
               (at(0,3) * at(1,1) * at(2,0) * at(3,2)) - (at(0,1) * at(1,3) * at(2,0) * at(3,2)) -
               (at(0,3) * at(1,0) * at(2,1) * at(3,2)) + (at(0,0) * at(1,3) * at(2,1) * at(3,2)) +
               (at(0,1) * at(1,0) * at(2,3) * at(3,2)) - (at(0,0) * at(1,1) * at(2,3) * at(3,2)) -
               (at(0,2) * at(1,1) * at(2,0) * at(3,3)) + (at(0,1) * at(1,2) * at(2,0) * at(3,3)) +
               (at(0,2) * at(1,0) * at(2,1) * at(3,3)) - (at(0,0) * at(1,2) * at(2,1) * at(3,3)) -
               (at(0,1) * at(1,0) * at(2,2) * at(3,3)) + (at(0,0) * at(1,1) * at(2,2) * at(3,3));
    }

    // Get the MxM transpose of this MxM matrix
    constexpr MatT transpose() const {
        MatT out;
        // TODO: Can we do this without a raw loop?
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                out(j, i) = at(i, j);
            }
        }
        return out;
    }

    // Fill the matrix with the specified value
    constexpr void fill(Type fill_value) {
        for (auto& col : cols_) {
            col.fill(fill_value);
        }
    }

    // Clear the matrix (reset to zero)
    constexpr void clear() {
        fill(0);
    }

    /**************************************************************************
     * MEMBER OPERATORS
     **************************************************************************/

    // Get reference to element at location (m, n) in the matrix
    constexpr Type& operator()(size_t m, size_t n) {
        return at(m, n);
    }

    // Get read-only reference to element at location (m, n) in the matrix
    constexpr const Type& operator()(size_t m, size_t n) const {
        return at(m, n);
    }

    // Add MxM matrix to this MxM matrix
    constexpr MatT& operator+=(const MatT& rhs) {
        std::transform(cols_.cbegin(), cols_.cend(), // this input
                       rhs.cols_.cbegin(),           // rhs input
                       cols_.begin(),                // output
                       std::plus<>{});               // operation
        return *this;
    }

    // Add a scalar to this MxM matrix
    constexpr MatT& operator+=(const Type rhs) {
        auto add_rhs = [rhs](Type lhs_elem) { return lhs_elem + rhs; };
        std::transform(cols_.cbegin(), cols_.cend(), // this input
                       rhs.cols_.cbegin(),           // rhs input
                       cols_.begin(),                // output
                       add_rhs);                     // operation
        return *this;
    }

    // Subtract MxM matrix from this MxM matrix
    constexpr MatT& operator-=(const MatT& rhs) {
        std::transform(cols_.cbegin(), cols_.cend(), // this input
                       rhs.cols_.cbegin(),           // rhs input
                       cols_.begin(),                // output
                       std::minus<>{});              // operation
        return *this;
    }

    // Subtract a scalar from this MxM matrix
    constexpr MatT& operator-=(const Type rhs) {
        auto subtract_rhs = [rhs](Type lhs_elem) { return lhs_elem - rhs; };
        std::transform(cols_.cbegin(), cols_.cend(), // this input
                       rhs.cols_.cbegin(),           // rhs input
                       cols_.begin(),                // output
                       subtract_rhs);                // operation
        return *this;
    }

    // Multiply this MxM matrix by scalar
    constexpr MatT& operator*=(Type rhs) {
        auto mult_by_rhs = [rhs](Type lhs_elem) { return lhs_elem * rhs; };
        std::transform(cols_.cbegin(), cols_.cend(), // this input
                       cols_.begin(),                // output
                       mult_by_rhs);                 // operation
        return *this;
    }

    // TODO: operator*= for matrix (since they're all square)

    // Divide this MxM matrix by scalar
    constexpr MatT& operator/=(Type rhs) {
        auto div_by_rhs = [rhs](Type lhs_elem) { return lhs_elem * rhs; };
        std::transform(cols_.cbegin(), cols_.cend(), // this input
                       cols_.begin(),                // output
                       div_by_rhs);                  // operation
        return *this;
    }

    /**************************************************************************
     * FRIEND OPERATORS
     **************************************************************************/

    // Get negation of MxM matrix
    friend constexpr MatT operator-(const MatT& rhs) {
        MatT out;
        std::transform(rhs.cols_.cbegin(), rhs.cols_.cend(), // this input
                       out.cols_.begin(),                    // output
                       std::negate<>());                     // operation
        return out;
    }

    // Check equality of two MxM matrices (all types)
    friend constexpr bool operator==(const MatT& lhs, const MatT& rhs) {
        return lhs.cols_ == rhs.cols_;
    }

    // Check inequality of two MxM matrices (all types)
    friend constexpr bool operator!=(const MatT& lhs, const MatT& rhs) {
        return lhs.cols_ != rhs.cols_;
    }

    // Add two MxM matrices
    friend constexpr MatT operator+(const MatT& lhs, const MatT& rhs) {
        MatT out;
        std::transform(lhs.cols_.cbegin(), lhs.cols_.cend(), // lhs input
                       rhs.cols_.cbegin(),                   // rhs input
                       out.cols_.begin(),                    // output
                       std::plus());                         // operation
        return out;
    }

    // Subtract two MxM matrices
    friend constexpr MatT operator-(const MatT& lhs, const MatT& rhs) {
        MatT out;
        std::transform(lhs.cols_.cbegin(), lhs.cols_.cend(), // lhs input
                       rhs.cols_.cbegin(),                   // rhs input
                       out.cols_.begin(),                    // output
                       std::minus());                        // operation
        return out;
    }

    // Multiply MxM matrix by scalar
    friend constexpr MatT operator*(const MatT& lhs, Type rhs) {
        MatT out;
        auto mult_by_rhs = [rhs](Type lhs_elem) { return lhs_elem * rhs; };
        std::transform(lhs.cols_.cbegin(), lhs.cols_.cend(), // lhs input
                       rhs.cols_.cbegin(),                   // rhs input
                       out.cols_.begin(),                    // output
                       mult_by_rhs);                         // operation
    }

    // Multiply MxM matrix by scalar (reverse operand order)
    friend constexpr MatT operator*(Type lhs, const MatT& rhs) {
        return rhs * lhs;
    }

    // Divide MxM matrix by scalar
    friend constexpr MatT operator/(const MatT& lhs, Type rhs) {
        MatT out;
        auto div_by_rhs = [rhs](Type lhs_elem) { return lhs_elem * rhs; };
        std::transform(lhs.cols_.cbegin(), lhs.cols_.cend(), // lhs input
                       rhs.cols_.cbegin(),                   // rhs input
                       out.cols_.begin(),                    // output
                       div_by_rhs);                          // operation
    }

    // Get MxM product of two MxM matrices
    friend constexpr MatT operator*(const MatT& lhs, const MatT& rhs) {
        // TODO: Can we do this without raw loops?
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

    // Stream matrix contents in human-readable form (row by row)
    friend std::ostream& operator<<(std::ostream& os, const MatT& rhs) {
        const auto rhs_transposed = rhs.transpose();
        auto joiner = std::experimental::make_ostream_joiner(os, "\n ");
        os << "\n[";
        std::copy(rhs_transposed.cols_.cbegin(), rhs_transposed.cols_.cend(), joiner);
        os << "]";
        return os;
    }

private:
    // Matrix columns
    std::array<VecT, M> cols_;
};

} // namespace vec