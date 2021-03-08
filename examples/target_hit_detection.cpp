// Vec library usage example: target hit detection
//
// This is an example of a basic interview-style problem on vector geometry for game programming.
// The premise is that we want to implement the hit-detection logic for a simple shooting gallery
// mini-game. There exists a flat, circular target at some position and orientation in 3D space, and
// a player shooting in a known direction from some other point in space.
//
// We can fully describe a circular target with the following:
//     1. The point in space at which the center of the target lies (p0)
//     2. The vector normal to the plane on which the target lies (n)
//     3. The radius of the target (r)
//
// Similarly, we can fully describe a player shot with the following:
//     1. The point in space at which the player is shooting from (s)
//     2. The vector describing the direction of the player's shot (v)
//
// The player's shot projects a ray with parametric equation:
//
//     ps = s + tv
//
// Where t is a scalar in the range [0, inf) since we only want to project in the forward direction.
// We can sweep t across this range to generate any point ps along the trajectory of the shot.
//
// The target lies on a plane described by the implicit equation:
//
//     (p - p0) dot n = 0
//
// The vector formed by the difference between any arbitrary point p on the plane and the known
// center of the target p0 will be orthogonal to the normal vector, meaning the dot product is zero.
//
// We can plug the above parametric ray equation in for point p in the implicit plane equation
// and attempt to solve for t to see if the ray actually intersects the plane:
//
//     (s + tv - p0) dot n = 0
//     ((s - p0) dot n) + (tv dot n) = 0
//     tv dot n = (p0 - s) dot n
//     t = ((p0 - s) dot n) / (v dot n)
//
// At this point we can check the denominator (v dot n) for zero, as that would blow up the
// equation and also indicates that the shot is parallel to the surface of the plane, meaning
// there is no intersect point (unless the shooting point s was actually on the surface of the
// plane, which we'll choose to not worry about).
//
// Assuming the denominator is not zero, we can solve for t. If t is positive, there is an
// intersect point in the direction of the player's shot. If t is negative, then there is an
// intersect on the line, but in the opposite direction of the player's shot, so the shot is
// obviously a miss.
//
// If t is positive, we can plug that back into the original ray equation to solve for the actual
// intersect point:
//
//     p1 = s + tv
//
// We can then check the euclidean distance between intersect point p1 and target center point
// p0, and compare that to the radius of the target. However, calculating the euclidean distance
// requires taking the square root of (p1 - p0) dot (p1 - p0), and square roots are relatively
// expensive. It's more computationally efficient to instead square the radius and compare the
// square of both sides:
//
//     If (p1 - p0) dot (p1 - p0) < r^2 , the shot is a hit.
//
// This logic is implemented below in check_target_hit().

#include <iostream>
#include <iomanip>

#include "vec.hpp"

using vec::Vec3f;
using std::cout;
using std::endl;

// Shot parameters
struct Shot {
    Vec3f position;  // Position of shot relative to arbitrary origin [m_x,m_y,m_z]
    Vec3f direction; // Direction of shot [unitless]
};

// Target parameters
struct CircleTarget {
    Vec3f position; // Position of center of target relative to arbitrary origin [m_x,m_y,m_z]
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