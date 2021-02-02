// Test main file for vec library

#include <iostream>
#include "include/vec.hpp"
#include "include/mat.hpp"

using std::cout;
using std::endl;

int main() {
    cout << "Hello, world! Testing out vectors:" << endl;

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

    cout << "\nv.hat(): " << v.hat() << endl;
    cout << "v.mag(): " << v.mag() << endl;
    cout << "v.mag2(): " << v.mag2() << endl;
    cout << "v.normalized(): " << v.normalized() << endl;
    cout << "v.normalized().mag(): " << v.normalized().mag() << endl;
    cout << "\n-v: " << -v << endl;

    float s = 2.0f;
    cout << "\ns: " << s << endl;
    cout << "\nv * s: " << v * s << endl;
    cout << "s * v: " << s * v << endl;
    cout << "v / s: " << v / s << endl;

    vec::Vec3f v2{1.0f, 1.0f, 1.0f};
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

    vec::Mat44f m1{};
}