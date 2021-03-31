// Affine transformation class template (and related helpers)

#pragma once

#include "mat.hpp"

namespace vec {

// Forward declaration
template<typename Type, size_t M>
class AffineTransform;

// Aliases for supported types and sizes
using Transform2f = AffineTransform<float, 2>;
using Transform3f = AffineTransform<float, 3>;

using Transform2d = AffineTransform<double, 2>;
using Transform3d = AffineTransform<double, 3>;

using Transform2ld = AffineTransform<long double, 2>;
using Transform3ld = AffineTransform<long double, 3>;

// Affine transform class template
// Extends matrix class template with size M+1 to enable homogeneous coordinate representation
template<typename Type, size_t M>
class AffineTransform final : public Mat<Type, M+1> {
    // Template parameter assertions
    static_assert((M >= 2) && (M <= 3), "Transform must be 2D or 3D (3x3 or 4x4 matrix)");
    static_assert(std::is_floating_point_v<Type>, "Type must be floating-point");

    // Type aliases for convenience
    using BaseMatT = Mat<Type, M+1>;
    using MatT = Mat<Type, M>;
    using VecT = Vec<Type, M>;

    // Template-param dependent parent members
    using BaseMatT::rows_;
    using BaseMatT::begin;

public:
    // Construct default affine transform (identity transform, zero translation)
    constexpr AffineTransform() : AffineTransform(MatT::identity(), VecT(0)) {}

    // Construct affine transform from MxM transform matrix and M-dimensional translation vector
    constexpr AffineTransform(MatT m_linear_transform, VecT v_translation) {
        set_linear_transform(m_linear_transform);
        set_translation(v_translation);
        rows_[M][M] = 1;
    }

    // Construct affine transform from MxM transform matrix (zero translation)
    constexpr explicit AffineTransform(MatT m_linear_transform)
            : AffineTransform(m_linear_transform, VecT(0)) {}

    // Construct affine transform from M-dimensional translation vector (identity transform)
    constexpr explicit AffineTransform(VecT v_translation)
            : AffineTransform(MatT::identity(), v_translation) {}

    // Get the MxM matrix representing the linear transform
    constexpr MatT get_linear_transform() const {
        MatT out;
        std::transform(rows_.cbegin(), rows_.cbegin() + M,
                       out.begin(),
                       slice_vec);
        return out;
    }

    // Set the MxM matrix representing the linear transform
    constexpr void set_linear_transform(const MatT& m_linear_transform) {
        std::transform(m_linear_transform.cbegin(), m_linear_transform.cend(),
                       begin(),
                       pad_vec);
    }

    // Get the M-dimensional vector representing the translation
    constexpr VecT get_translation() const {
        return VecT(rows_[M]);
    }

    // Set the M-dimensional vector representing the translation
    constexpr void set_translation(const VecT& v_translation) {
        // Note: copy elements directly to prevent overwriting bottom-rightmost element
        std::copy(v_translation.cbegin(), v_translation.cend(), rows_[M].begin());
    }
private:
    // Helper to pad vector with trailing 0
    static constexpr auto pad_vec = [](const Vec<Type, M>& blah) {
        return Vec<Type, M+1>(blah);
    };

    // Helper to slice vector (drop final element)
    static constexpr auto slice_vec = [](const Vec<Type, M+1>& blah) {
        return Vec<Type, M>(blah);
    };
};

// TODO: Helpers for rotation, reflection, scale, skew

} // namespace vec

