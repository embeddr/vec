// Test main file for vec library
// TODO: Remove this file - keeping temporarily as unit tests are added

#include <iostream>
#include "include/vec.hpp"
#include "include/mat.hpp"

using std::cout;
using std::endl;

constexpr vec::Vec2f test_constexpr_add(vec::Vec2f v1, vec::Vec2f v2) {
   return v1 + v2;
}

constexpr vec::Vec2f test_constexpr_double(vec::Vec2f v) {
    v *= 2.0f;
    return v;
}

int main() {
    cout << "Hello, world! Testing out vectors:" << endl;

    constexpr vec::Vec2f vc1{5.0f, 5.0f};
    constexpr vec::Vec2f vc2{1.0f, 1.0f};
    constexpr vec::Vec2f vc1p2 = test_constexpr_add(vc1, vc2);
    constexpr vec::Vec2f vc1_doubled = test_constexpr_double(vc1);

    vec::Vec3f v{1.0f, 2.0f, 3.0f};
    cout << "\nv: " << v << endl;
    cout << "v.size(): " << v.size() << endl;

    cout << "\nv.x(): " << v.x() << endl;
    cout << "v.y(): " << v.y() << endl;
    cout << "v.z(): " << v.z() << endl;
    cout << "(v.w() doesn't exist for N = 3)" << endl;
    // cout << "w: " << v2.w() << endl;

    cout << "\nv[0]: " << v[0] << endl;
    cout << "v[1]: " << v[1] << endl;
    cout << "v[2]: " << v[2] << endl;
    cout << "(v[3] or higher is out of bounds)" << endl;
    // cout << "v[3]: " << v[3] << endl;

    cout << "\nv.manhattan(): " << v.manhattan() << endl;
    cout << "v.euclidean(): " << v.euclidean() << endl;
    cout << "v.euclidean2(): " << v.euclidean2() << endl;
    cout << "v.normalize(): " << v.normalize() << endl;
    cout << "v.normalize().euclidean(): " << v.normalize().euclidean() << endl;
    cout << "\n-v: " << -v << endl;

    float s = 2.0f;
    cout << "\ns: " << s << endl;
    cout << "\nv * s: " << v * s << endl;
    cout << "s * v: " << s * v << endl;
    cout << "v / s: " << v / s << endl;

    constexpr vec::Vec3f v2{1.0f, 1.0f, 1.0f};
    cout << "\nv2: " << v2 << endl;

    cout << "\nv == v: " << ((v == v) ? "true" : "false") << endl;
    cout << "v == v2: " << ((v == v2) ? "true" : "false") << endl;
    cout << "v != v: " << ((v != v) ? "true" : "false") << endl;
    cout << "v != v2: " << ((v != v2) ? "true" : "false") << endl;

    cout << "\nv + v2: " << v + v2 << endl;
    cout << "v - v2: " << v - v2 << endl;

    v += v2;
    cout << "\nv += v2; v: " << v << endl;

    v -= v2;
    cout << "v -= v2; v: " << v << endl;

    cout << "\ndot(v, v2): " << dot(v, v2) << endl;
    cout << "cross(v, v2): " << cross(v, v2) << endl;

    vec::Vec4f v3{1.0f, 2.0f, 3.0f, 4.0f};
    vec::Vec4f v4(1.0f); // fill
    cout << "\nv3: " << v3 << endl;
    cout << "v4: " << v4 << endl;
    cout << "\n(cross(v3, v4) is not defined since N != 3)" << endl;
    // cout << "cross(v3, v4): " << cross(v3, v4) << endl;

    vec::Vec2f v_test{1.0f, 2.0f};

    vec::Vec<3, int> v_int{2};
    cout << (v_int == v_int) << endl;

    constexpr vec::Mat22f m1{vec::Vec2f{1.0f, 2.0f}, vec::Vec2f{3.0f, 4.0f}};
    vec::Mat22f m2(1.0f);
    m2 += m1;
    cout << "m2 += m1; m2: " << m2 << endl;

    constexpr auto i33 = vec::Mat33f::identity();
    cout << "3x3 identity: " << i33 << endl;

    auto diag33 = vec::Mat33f::diagonal(vec::Vec3f{1.0f, 2.5f, 3.0f});
    cout << "3x3 diagonal: " << diag33 << endl;

    auto i3 = vec::Vec3f::i();
    auto j3 = vec::Vec3f::j();
    auto k3 = vec::Vec3f::k();
    cout << "i3: " << i3 << endl;
    cout << "j3: " << j3 << endl;
    cout << "k3: " << k3 << endl;
}