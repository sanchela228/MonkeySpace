#include "types/Vector3.h"
#include "utils/Random.h"

#include <vector>
#include <cmath>

using namespace Utils;
using namespace Types;

Vector3 Vector3::generate_random_position(const Vector3& size) {
    return {
        Random::random_float(0, size.x),
        Random::random_float(0, size.y),
        Random::random_float(0, size.z)
    };
}

Vector3 Vector3::generate_random_position_near(
    const Vector3& position,
    const Vector3& size,
    float max_distance
) {
    float theta = Random::random_float(0, 2 * M_PI);
    float phi = Random::random_float(0, M_PI);
    float distance = Random::random_float(0, max_distance);

    float dx = distance * sin(phi) * cos(theta);
    float dy = distance * sin(phi) * sin(theta);
    float dz = distance * cos(phi);

    dx = std::max(-size.x / 2, std::min(size.x / 2, dx));
    dy = std::max(-size.y / 2, std::min(size.y / 2, dy));
    dz = std::max(-size.z / 2, std::min(size.z / 2, dz));

    return {
        position.x + dx,
        position.y + dy,
        position.z + dz
    };
}

float Vector3::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

float Vector3::distance_between(const Vector3& a, const Vector3& b) {
    return std::sqrt(
        (a.x - b.x) * (a.x - b.x) +
        (a.y - b.y) * (a.y - b.y) +
        (a.z - b.z) * (a.z - b.z)
    );
}