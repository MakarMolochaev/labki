#include "Vector3.h"

float Vector3::Dot(const Vector3& a, const Vector3& b) {
    return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
}

float Vector3::Cos(const Vector3& a, const Vector3& b) {
    return Vector3::Dot(a, b) / (a.Length() * b.Length());
}

float Vector3::Dist(const Vector3& a, const Vector3& b) {
    return (a - b).Length();
}

Vector3 Vector3::Cross(const Vector3& a, const Vector3& b) {
    return Vector3(a.Y * b.Z - b.Y * a.Z, b.X * a.Z - a.X * b.Z, a.X * b.Y - b.X * a.Y);
}