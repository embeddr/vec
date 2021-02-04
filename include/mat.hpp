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
template<size_t N, size_t M, typename Type>
class Mat;

// Aliases for common matrices
using Mat22f = Mat<2, 2, float>;
using Mat33f = Mat<3, 3, float>;
using Mat44f = Mat<4, 4, float>;

// Matrix class template
template<size_t N, size_t M, typename Type>
class Mat {
    static_assert((N > 0), "Number of rows N must be positive");
    static_assert((M > 0), "Number of cols M must be positive");
    static_assert(std::is_arithmetic<Type>::value, "Type must be arithmetic");
    using MatNMT = Mat<N, M, Type>; // TODO: name MatT instead?
    using VecNT = Vec<N, Type>;     // TODO: name VecT instead?
public:
    // Construct matrix with zero-init elements
    Mat() : cols_{} {}

    // Construct matrix from other matrix
    Mat(const MatNMT& other) : cols_(other.cols_) {}

    // Construct matrix from parameter pack of columns
    template<typename ...Args>
    explicit Mat(VecNT first, Args... args) : cols_{first, args...} {}

    // TODO: Construct matrix from list of individual elements in column_major order?

    // Construct matrix and fill elements with argument value
    explicit Mat(Type fill_value) {
        for (auto& col : cols_) {
            col.fill(fill_value);
        }
    }

    // Get reference to column by index
    Type& operator[](size_t index) {
        return cols_.at(index);
    }

    // Get read-only reference to column index
    const Type& operator[](size_t index) const {
        return cols_.at(index);
    }

    // Add N-by-M matrix to this N-by-M matrix
    MatNMT& operator+=(const MatNMT& rhs) {
        std::transform(cols_.cbegin(), cols_.cend(), // this input
                       rhs.cols_.cbegin(),           // rhs input
                       cols_.begin(),                // output
                       std::plus<>{});               // operation
        return *this;
    }

    // Subtract N-by-M matrix from this N-by-M matrix
    MatNMT& operator-=(const MatNMT& rhs) {
        std::transform(cols_.cbegin(), cols_.cend(), // this input
                       rhs.cols_.cbegin(),           // rhs input
                       cols_.begin(),                // output
                       std::minus<>{});              // operation
        return *this;
    }

    // Multiply this N-by-M matrix by scalar
    MatNMT& operator*=(Type scalar) {
        auto mult_by_scalar = std::bind(std::multiplies(), _1, scalar);
        std::transform(cols_.cbegin(), cols_.cend(), // this input
                       cols_.begin(),                // output
                       mult_by_scalar);              // operation
        return *this;
    }

    // Divide this N-by-M matrix by scalar
    MatNMT& operator/=(Type scalar) {
        auto div_by_scalar = std::bind(std::divides(), _1, scalar);
        std::transform(cols_.cbegin(), cols_.cend(), // this input
                       cols_.begin(),                // output
                       div_by_scalar);               // operation
        return *this;
    }

    // Get negation of N-by-M matrix
    friend MatNMT operator-(const MatNMT& rhs) {
        MatNMT out{};
        std::transform(rhs.cols_.cbegin(), rhs.cols_.cend(), // this input
                       out.cols_.begin(),                    // output
                       std::negate<>());                     // operation
        return out;
    }

    // Check equality of two N-by-M matrices (all types)
    friend bool operator==(const MatNMT& lhs, const MatNMT& rhs) {
        return lhs.cols_ == rhs.cols_;
    }

    // Check inequality of two N-by-M matrices (all types)
    friend bool operator!=(const MatNMT& lhs, const MatNMT& rhs) {
        return lhs.cols_ != rhs.cols_;
    }

    // Add two N-by-M matrices
    friend MatNMT operator+(const MatNMT& lhs, const MatNMT& rhs) {
        MatNMT out{};
        std::transform(lhs.cols_.cbegin(), lhs.cols_.cend(), // lhs input
                       rhs.cols_.cbegin(),                   // rhs input
                       out.cols_.begin(),                    // output
                       std::plus());                         // operation
        return out;
    }

    // Subtract two N-by-M matrices
    friend MatNMT operator-(const MatNMT& lhs, const MatNMT& rhs) {
        MatNMT out{};
        std::transform(lhs.cols_.cbegin(), lhs.cols_.cend(), // lhs input
                       rhs.cols_.cbegin(),                   // rhs input
                       out.cols_.begin(),                    // output
                       std::minus());                        // operation
        return out;
    }

    // Multiply N-by-M matrix by scalar
    friend MatNMT operator*(const MatNMT& lhs, Type rhs) {
        MatNMT out{};
        auto mult_by_rhs = std::bind(std::multiplies(), _1, rhs);
        std::transform(lhs.cols_.cbegin(), lhs.cols_.cend(), // lhs input
                       rhs.cols_.cbegin(),                   // rhs input
                       out.cols_.begin(),                    // output
                       mult_by_rhs);                         // operation
    }

    // Multiply N-by-M matrix by scalar (reverse operand order)
    friend MatNMT operator*(Type lhs, const MatNMT& rhs) {
        return rhs * lhs;
    }

    // Divide N-by-M matrix by scalar
    friend MatNMT operator/(const MatNMT& lhs, Type rhs) {
        MatNMT out{};
        auto div_by_rhs = std::bind(std::divides(), _1, rhs);
        std::transform(lhs.cols_.cbegin(), lhs.cols_.cend(), // lhs input
                       rhs.cols_.cbegin(),                   // rhs input
                       out.cols_.begin(),                    // output
                       div_by_rhs);                          // operation
    }

    // TODO: Multiply N-by-M matrix by N-by-M matrix

    // Stream matrix contents in human-readable form
    friend std::ostream& operator<<(std::ostream& os, const MatNMT& rhs) {
        auto joiner = std::experimental::make_ostream_joiner(os, "\n ");
        // TODO: Should this actually print the transpose for visual correctness?
        os << "\n[";
        std::copy(rhs.cols_.cbegin(), rhs.cols_.cend(), joiner);
        os << "]";
        return os;
    }

    // Get the size of the matrix (rows, columns)
    std::pair<size_t, size_t> size() const {
        return std::make_pair(N, M);
    }

    // TODO: Determinant

    // TODO: Transpose

private:
    // Matrix columns
    std::array<VecNT, M> cols_{};
};

} // namespace vec