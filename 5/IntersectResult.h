#pragma once
#include "Vector3.h"

class IntersectResult {
public:
    bool hit = false;
    Vector3 point;
    Vector3 normal;
    float t = 0;

    IntersectResult(bool hit) : hit(hit) {}

    IntersectResult(bool hit, Vector3 point, Vector3 normal, float t) : hit(hit), point(point), normal(normal), t(t) {}
};