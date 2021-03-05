// Vec library usage example: target hit detection

#include <iostream>
#include <iomanip>

#include "vec.hpp"

using vec::Vec3f;
using std::cout;
using std::endl;

// Shot parameters
struct Shot {
    Vec3f position;  // Position of shot relative to arbitrary origin [m,m,m]
    Vec3f direction; // Direction of shot [unitless]
};

// Target parameters
struct CircleTarget {
    Vec3f position; // Position of center of target relative to arbitrary origin [m,m,m]
    Vec3f normal;   // Normal of the plane on which the target lies [unitless]
    float radius;   // Radius of target [m]
};

std::ostream& operator<<(std::ostream& os, const Shot& rhs) {
    os << "Shot:" << endl;
    os << "  position: " << rhs.position << endl;
    os << "  direction: " << rhs.direction << endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const CircleTarget& rhs) {
    os << "CircleTarget:" << endl;
    os << "  position: " << rhs.position << endl;
    os << "  normal: " << rhs.normal << endl;
    os << "  radius: " << rhs.radius << endl;
    return os;
}

// Check if the provided shot hit the provided circular target
constexpr bool check_target_hit(const Shot& shot, const CircleTarget& target) {
    const float denominator = dot(shot.direction, target.normal);
    if (std::abs(denominator) < 0.00001f) {
        // Shot is approximately parallel with the plane; no hit
        return false;
    }

    const float numerator = dot((target.position - shot.position), target.normal);
    const float t = numerator / denominator;
    if (t < 0.0f) {
        // Shot is in wrong direction; no hit
        return false;
    }

    // Intersect point exists; check distance from target center against radius
    // Note: checking square of distance against square of radius for efficiency
    const Vec3f intersect = shot.position + (t * shot.direction);
    return euclidean2(intersect, target.position) < (target.radius * target.radius);
}

int main() {
    cout << "Vec example: circular target hit detection" << endl;

    // Arbitrary constexpr example
    constexpr Shot shot{
        .position = Vec3f{0.0f, -0.5f, 0.0f},
        .direction = Vec3f{1.0f, 0.2f, 0.0f},
    };

    constexpr CircleTarget target{
        .position = Vec3f{5.0f, 0.0f, 0.0f},
        .normal = Vec3f{-1.0f, 0.0f, 0.5f},
        .radius = 1.0f,
    };

    constexpr bool hit = check_target_hit(shot, target);

    cout << std::fixed << std::setprecision(1);
    cout << shot << target << "Result: " << (hit ? "hit!" : "miss") << endl;

    // TODO: runtime example with user input

    return EXIT_SUCCESS;
}