#pragma once
#include "Vector3.h"

class IntersectResult {
public:
    bool intersect = false;
    Vector3 point;
    Vector3 normal;

    IntersectResult(bool result) : intersect(intersect) {}

    IntersectResult(bool result, Vector3 point, Vector3 normal) : intersect(result), point(point), normal(normal) {}
};