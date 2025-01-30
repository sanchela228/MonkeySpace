#ifndef QUATERNION_H
#define QUATERNION_H
namespace Types
{
    struct Quaternion {
        float w, x, y, z;

        Quaternion() : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}
        Quaternion(float w_, float x_, float y_, float z_) : w(w_), x(x_), y(y_), z(z_) {}

        // Нормализация кватерниона
        void normalize();

        // Сопряжённый кватернион
        Quaternion conjugate() const;

        // Умножение кватернионов
        Quaternion operator* (const Quaternion& other) const;

        // Умножение на скаляр
        Quaternion operator* (float scalar) const;

        // Сложение кватернионов
        Quaternion operator+(const Quaternion& other) const;

        // Вычитание кватернионов
        Quaternion operator-(const Quaternion& other) const;

        // Вычисление длины (нормы) кватерниона
        float length() const;

        // Преобразование кватерниона в матрицу вращения (3x3)
        void toRotationMatrix(float matrix[3][3]) const;

        // Создание кватерниона из угла и оси вращения
        static Quaternion fromAxisAngle(float angle, float ax, float ay, float az);

        // Линейная интерполяция между двумя кватернионами (LERP)
        static Quaternion lerp(const Quaternion& q1, const Quaternion& q2, float t);

        // Сферическая линейная интерполяция (SLERP)
        static Quaternion slerp(const Quaternion& q1, const Quaternion& q2, float t);

        // Нормализованный кватернион
        Quaternion normalized() const;

        // Вывод кватерниона в консоль
        void print() const;
    };
}


#endif //QUATERNION_H
