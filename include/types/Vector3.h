#ifndef VECTOR3_H
#define VECTOR3_H

namespace Types
{
    struct Vector3 {
        float x, y, z;
        Vector3() = default;
        Vector3(const float x_, const float y_, const float z_)
            : x(x_), y(y_), z(z_) {}

        static Vector3 generate_random_position(const Vector3& size);
        static Vector3 generate_random_position_near(
            const Vector3& position,
            const Vector3& size,
            float max_distance
        );

        float length() const;
        static float distance_between(const Vector3& a, const Vector3& b);
    };
}



#endif // VECTOR3_H