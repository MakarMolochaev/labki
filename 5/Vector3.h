#pragma once
#include <cmath>
#include <string>

class Vector3 {
public:
    float X = 1, Y = 1, Z = 1;
    Vector3() {}
    Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

    float Length() const {
        return std::sqrt(X * X + Y * Y + Z * Z);
    }

    float SquareLength() const {
        return X * X + Y * Y + Z * Z;
    }

    Vector3 operator+(const Vector3& other) const {
        return Vector3(X + other.X, Y + other.Y, Z + other.Z);
    }

    Vector3 operator-(const Vector3& other) const {
        return Vector3(X - other.X, Y - other.Y, Z - other.Z);
    }

    Vector3 operator*(const float mult) const {
        return Vector3(X * mult, Y * mult, Z * mult);
    }

    Vector3 Normalized() const {
        float length = Length();
        return Vector3(X / length, Y / length, Z / length);
    }

    void Normalize() {
        float length = Length();
        X /= length;
        Y /= length;
        Z /= length;
    }

    std::string ToString() {
        return "(" + std::to_string(this->X) + ", " + std::to_string(this->Y) + ", " + std::to_string(this->Z) + ")";
    }

    static float Dot(const Vector3& a, const Vector3& b);
    static float Cos(const Vector3& a, const Vector3& b);
    static float Dist(const Vector3& a, const Vector3& b);
    static Vector3 Cross(const Vector3& a, const Vector3& b);
};