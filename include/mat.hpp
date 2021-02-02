// Basic matrix class template definition

#pragma once

#include <algorithm>
#include <array>
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
    using MatNMT = Mat<N, M, Type>;
public:
    // Construct matrix with zero-init elements
    Mat() = default;

private:
    // Matrix columns
    std::array<vec::Vec<N, Type>, M> cols_{};
};

} // namespace vec