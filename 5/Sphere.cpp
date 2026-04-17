#include "Object.h"
#include "Vector3.h"
#include "Ray.h"
#include <iostream>

IntersectResult Sphere::Intersect(Ray ray) const {
    Vector3 OC = ray.start - this->position;
    float B = Vector3::Dot(ray.dir, OC) * 2.0f;
    float D = B * B - 4 * OC.SquareLength() + 4.0f * this->radius * this->radius;
    if(D >= 0) {
        float t = ((-B - sqrt(D)) / 2);
        Vector3 intersectionPoint = ray.start + ray.dir * t;
        Vector3 normal = (intersectionPoint - this->position).Normalized();
        return IntersectResult(true, intersectionPoint, normal, t);
    } else {
        return IntersectResult(false);
    }
}