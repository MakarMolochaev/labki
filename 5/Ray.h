#pragma once
#include "math.h"
#include "Vector3.h"

class Ray {
public:
    Vector3 start;
    Vector3 dir;

    Ray(Vector3 point, Vector3 direction) : start(point), dir(direction) {}
};