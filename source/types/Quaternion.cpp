#include "types/Quaternion.h"

#include <iostream>
#include <valarray>

using namespace Types;

void Quaternion::normalize() {
    float norm = std::sqrt(w * w + x * x + y * y + z * z);
    if (norm > 0.0f) {
        w /= norm;
        x /= norm;
        y /= norm;
        z /= norm;
    }
}

Quaternion Quaternion::conjugate() const {
    return {w, -x, -y, -z};
}

Quaternion Quaternion::operator*(const Quaternion& other) const {
    return {
        w * other.w - x * other.x - y * other.y - z * other.z,
        w * other.x + x * other.w + y * other.z - z * other.y,
        w * other.y - x * other.z + y * other.w + z * other.x,
        w * other.z + x * other.y - y * other.x + z * other.w
    };
}

Quaternion Quaternion::operator*(float scalar) const {
    return {w * scalar, x * scalar, y * scalar, z * scalar};
}

Quaternion Quaternion::operator+(const Quaternion& other) const {
    return {w + other.w, x + other.x, y + other.y, z + other.z};
}

Quaternion Quaternion::operator-(const Quaternion& other) const {
    return {w - other.w, x - other.x, y - other.y, z - other.z};
}

float Quaternion::length() const {
    return std::sqrt(w * w + x * x + y * y + z * z);
}

void Quaternion::toRotationMatrix(float matrix[3][3]) const {
    float xx = x * x;
    float xy = x * y;
    float xz = x * z;
    float xw = x * w;

    float yy = y * y;
    float yz = y * z;
    float yw = y * w;

    float zz = z * z;
    float zw = z * w;

    matrix[0][0] = 1.0f - 2.0f * (yy + zz);
    matrix[0][1] = 2.0f * (xy - zw);
    matrix[0][2] = 2.0f * (xz + yw);

    matrix[1][0] = 2.0f * (xy + zw);
    matrix[1][1] = 1.0f - 2.0f * (xx + zz);
    matrix[1][2] = 2.0f * (yz - xw);

    matrix[2][0] = 2.0f * (xz - yw);
    matrix[2][1] = 2.0f * (yz + xw);
    matrix[2][2] = 1.0f - 2.0f * (xx + yy);
}

Quaternion Quaternion::fromAxisAngle(float angle, float ax, float ay, float az) {
    float halfAngle = angle * 0.5f;
    float sinHalfAngle = std::sin(halfAngle);
    return {
        std::cos(halfAngle),
        ax * sinHalfAngle,
        ay * sinHalfAngle,
        az * sinHalfAngle
    };
}

Quaternion Quaternion::lerp(const Quaternion& q1, const Quaternion& q2, float t) {
    return (q1 * (1.0f - t) + q2 * t).normalized();
}

Quaternion Quaternion::slerp(const Quaternion& q1, const Quaternion& q2, float t) {
    float dot = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
    float theta = std::acos(dot);

    if (theta < 0.0f) {
        theta = -theta;
    }

    float sinTheta = std::sin(theta);
    float w1 = std::sin((1.0f - t) * theta) / sinTheta;
    float w2 = std::sin(t * theta) / sinTheta;

    return (q1 * w1 + q2 * w2).normalized();
}

Quaternion Quaternion::normalized() const {
    Quaternion result = *this;
    result.normalize();
    return result;
}

void Quaternion::print() const {
    std::cout << "Quaternion(" << w << ", " << x << ", " << y << ", " << z << ")\n";
}