// Basic matrix class template definition

#pragma once

#include <algorithm>
#include <array>
#include <experimental/iterator>
#include <type_traits>

#include "include/vec.hpp"

using std::size_t;

namespace vec {

// Forward declaration
template<size_t M, size_t N, typename Type>
class Mat;

// Aliases for common matrices
using Mat22f = Mat<2, 2, float>;
using Mat33f = Mat<3, 3, float>;
using Mat44f = Mat<4, 4, float>;

// Matrix class template
template<size_t M, size_t N, typename Type>
class Mat {
    static_assert((M > 1) && (M < 5), "Supported matrix sizes: M = 2, 3, 4");
    static_assert((N > 1) && (N < 5), "Supported matrix sizes: N = 2, 3, 4");
    static_assert(std::is_arithmetic<Type>::value, "Type must be arithmetic");
    using MatT = Mat<M, N, Type>;
    using VecT = Vec<M, Type>;
public:
    // Construct matrix with zero-init elements
    constexpr Mat() : cols_{} {}

    // Construct matrix from other matrix
    constexpr Mat(const MatT& other) : cols_(other.cols_) {}

    // Construct matrix from parameter pack of columns
    template<typename ...Args>
    constexpr explicit Mat(const VecT& first, Args... args) : cols_{first, args...} {}

    // TODO: Construct matrix from list of individual elements in column_major order?

    // Construct matrix and fill elements with argument value
    constexpr explicit Mat(Type fill_value) {
        for (auto& col : cols_) {
            col.fill(fill_value);
        }
    }

    // Create a diagonal matrix from the provided vector
    template <size_t CheckM = M, size_t CheckN = N>
    constexpr static typename std::enable_if<(CheckM == CheckN), MatT>::type diagonal(VecT vec) {
        MatT out{};
        for (int i = 0; i < M; i++) {
            out(i, i) = vec[i];
        }
        return out;
    }

    // Get the identity matrix
    template <size_t CheckM = M, size_t CheckN = N>
    constexpr static typename std::enable_if<(CheckM == CheckN), MatT>::type identity() {
        return diagonal(VecT(static_cast<Type>(1)));
    }

    // Get reference to element at location (m, n) in the matrix
    constexpr Type& operator()(size_t m, size_t n) {
        return at(m, n);
    }

    // Get read-only reference to element at location (m, n) in the matrix
    constexpr const Type& operator()(size_t m, size_t n) const {
        return at(m, n);
    }

    // Add M-by-N matrix to this M-by-N matrix
    constexpr MatT& operator+=(const MatT& rhs) {
        std::transform(cols_.cbegin(), cols_.cend(), // this input
                       rhs.cols_.cbegin(),           // rhs input
                       cols_.begin(),                // output
                       std::plus<>{});               // operation
        return *this;
    }

    // Add a scalar to this M-by-N matrix
    constexpr MatT& operator+=(const Type rhs) {
        auto add_rhs = [rhs](Type lhs_elem) { return lhs_elem + rhs; };
        std::transform(cols_.cbegin(), cols_.cend(), // this input
                       rhs.cols_.cbegin(),           // rhs input
                       cols_.begin(),                // output
                       add_rhs);                     // operation
        return *this;
    }

    // Subtract M-by-N matrix from this M-by-N matrix
    constexpr MatT& operator-=(const MatT& rhs) {
        std::transform(cols_.cbegin(), cols_.cend(), // this input
                       rhs.cols_.cbegin(),           // rhs input
                       cols_.begin(),                // output
                       std::minus<>{});              // operation
        return *this;
    }

    // Subtract a scalar from this M-by-N matrix
    constexpr MatT& operator-=(const Type rhs) {
        auto subtract_rhs = [rhs](Type lhs_elem) { return lhs_elem - rhs; };
        std::transform(cols_.cbegin(), cols_.cend(), // this input
                       rhs.cols_.cbegin(),           // rhs input
                       cols_.begin(),                // output
                       subtract_rhs);                // operation
        return *this;
    }

    // Multiply this M-by-N matrix by scalar
    constexpr MatT& operator*=(Type rhs) {
        auto mult_by_rhs = [rhs](Type lhs_elem) { return lhs_elem * rhs; };
        std::transform(cols_.cbegin(), cols_.cend(), // this input
                       cols_.begin(),                // output
                       mult_by_rhs);                 // operation
        return *this;
    }

    // Divide this M-by-N matrix by scalar
    constexpr MatT& operator/=(Type rhs) {
        auto div_by_rhs = [rhs](Type lhs_elem) { return lhs_elem * rhs; };
        std::transform(cols_.cbegin(), cols_.cend(), // this input
                       cols_.begin(),                // output
                       div_by_rhs);                  // operation
        return *this;
    }

    // Get negation of M-by-N matrix
    friend constexpr MatT operator-(const MatT& rhs) {
        MatT out;
        std::transform(rhs.cols_.cbegin(), rhs.cols_.cend(), // this input
                       out.cols_.begin(),                    // output
                       std::negate<>());                     // operation
        return out;
    }

    // Check equality of two M-by-N matrices (all types)
    friend constexpr bool operator==(const MatT& lhs, const MatT& rhs) {
        return lhs.cols_ == rhs.cols_;
    }

    // Check inequality of two M-by-N matrices (all types)
    friend constexpr bool operator!=(const MatT& lhs, const MatT& rhs) {
        return lhs.cols_ != rhs.cols_;
    }

    // Add two M-by-N matrices
    friend constexpr MatT operator+(const MatT& lhs, const MatT& rhs) {
        MatT out;
        std::transform(lhs.cols_.cbegin(), lhs.cols_.cend(), // lhs input
                       rhs.cols_.cbegin(),                   // rhs input
                       out.cols_.begin(),                    // output
                       std::plus());                         // operation
        return out;
    }

    // Subtract two M-by-N matrices
    friend constexpr MatT operator-(const MatT& lhs, const MatT& rhs) {
        MatT out;
        std::transform(lhs.cols_.cbegin(), lhs.cols_.cend(), // lhs input
                       rhs.cols_.cbegin(),                   // rhs input
                       out.cols_.begin(),                    // output
                       std::minus());                        // operation
        return out;
    }

    // Multiply M-by-N matrix by scalar
    friend constexpr MatT operator*(const MatT& lhs, Type rhs) {
        MatT out;
        auto mult_by_rhs = [rhs](Type lhs_elem) { return lhs_elem * rhs; };
        std::transform(lhs.cols_.cbegin(), lhs.cols_.cend(), // lhs input
                       rhs.cols_.cbegin(),                   // rhs input
                       out.cols_.begin(),                    // output
                       mult_by_rhs);                         // operation
    }

    // Multiply M-by-N matrix by scalar (reverse operand order)
    friend constexpr MatT operator*(Type lhs, const MatT& rhs) {
        return rhs * lhs;
    }

    // Divide M-by-N matrix by scalar
    friend constexpr MatT operator/(const MatT& lhs, Type rhs) {
        MatT out;
        auto div_by_rhs = [rhs](Type lhs_elem) { return lhs_elem * rhs; };
        std::transform(lhs.cols_.cbegin(), lhs.cols_.cend(), // lhs input
                       rhs.cols_.cbegin(),                   // rhs input
                       out.cols_.begin(),                    // output
                       div_by_rhs);                          // operation
    }

    // Get M-by-N product of M-by-P and P-by-N matrices
    template<size_t P>
    friend constexpr MatT operator*(const Mat<M, P, Type>& lhs, const Mat<P, N, Type>& rhs) {
        auto calc_element = [lhs, rhs](size_t i, size_t j) {
            Type sum = 0;
            for (int p = 0; p < P; p++) {
                sum += lhs(i, p) * rhs(p, j);
            }
            return sum;
        };
        MatT out;
        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
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

    // Get the shape of the matrix as a pair (M rows, N columns)
    constexpr std::pair<size_t, size_t> shape() const {
        return std::make_pair(M, N);
    }

    // Check if the matrix is square
    constexpr bool is_square() const {
        return (N == M);
    }

    // Get reference to element at location (m, n) in the matrix
    constexpr Type& at(size_t m, size_t n) {
        return cols_.at(m)[n];
    }

    // Get read-only reference to element at location (m, n) in the matrix
    constexpr const Type& at(size_t m, size_t n) const {
        return cols_.at(m)[n];
    }

    // Get the matrix determinant (2-by-2 specialization)
    template<size_t CheckM = M, size_t CheckN = N>
    constexpr typename std::enable_if<((CheckM == 2) && (CheckN == 2)), Type>::type
    determinant() const {
        return at(0,0) * at(1,1) - at(0,1) * at(1,0);
    }

    // Get the matrix determinant (3-by-3 specialization)
    template<size_t CheckM = M, size_t CheckN = N>
    constexpr typename std::enable_if<((CheckM == 3) && (CheckN == 3)), Type>::type
    determinant() const {
        return at(0,0) * (at(1,1) * at(2,2) - at(1,2) * at(2,1))
             + at(0,1) * (at(1,2) * at(2,0) - at(1,0) * at(2,2))
             + at(0,2) * (at(1,0) * at(2,1) - at(1,1) * at(2,0));
    }

    // Get the matrix determinant (4-by-4 specialization)
    template<size_t CheckM = M, size_t CheckN = N>
    constexpr typename std::enable_if<((CheckM == 4) && (CheckN == 4)), Type>::type
    determinant() const {
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

    // Get the N-by-M transpose of this M-by-N matrix
    constexpr Mat<N, M, Type> transpose() const {
        Mat<N, M, Type> out;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
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

private:
    // Matrix columns
    std::array<VecT, N> cols_;
};

} // namespace vec