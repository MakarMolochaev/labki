#include "Shape.h"
#include "Vector3.h"
#include "Ray.h"

IntersectResult Sphere::Intersect(Ray ray) const {
    Vector3 OC = this->position - ray.start;
    float dot1 = Vector3::Dot(ray.dir, OC);
    float D = dot1 * dot1 - 4 * OC.SquareLength() + 4 * this->radius * this->radius;
    if(D >= 0) {
        Vector3 intersectionPoint = ray.start + ray.dir * ((-dot1 - sqrt(D)) / 2);
        Vector3 normal = (intersectionPoint - this->position).Normalized();
        return IntersectResult(true, intersectionPoint, normal);
    } else {
        return IntersectResult(false);
    }
}