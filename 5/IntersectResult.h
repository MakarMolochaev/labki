#pragma once
#include "Vector3.h"

class IntersectResult {
public:
    bool intersect = false;
    Vector3 point;
    Vector3 normal;
    float t = 0;

    IntersectResult(bool result) : intersect(result) {}

    IntersectResult(bool result, Vector3 point, Vector3 normal, float t) : intersect(result), point(point), normal(normal), t(t) {}
};