#include "Object.h"
#include "Vector3.h"
#include "Ray.h"
#include <iostream>
#include <cmath>
#include <limits>

IntersectResult Plane::Intersect(Ray ray) const {
    if (std::abs(ray.dir.Z) < std::numeric_limits<float>::epsilon()) {
        return IntersectResult(false);
    }

    float t = (this->position.Z - ray.start.Z) / ray.dir.Z;

    if (t < 0.001f || t > 100000.0f) {
        return IntersectResult(false);
    }

    Vector3 impactPoint = ray.Travel(t);

    if(std::abs(impactPoint.X - this->position.X) <= this->size && std::abs(impactPoint.Y - this->position.Y) <= this->size) {
        return IntersectResult(true, impactPoint, Vector3(0,0,1), t);
    } else {
        return IntersectResult(false);
    }
}

std::unique_ptr<Object> Plane::Instantiate(std::ifstream& inputStream) const {
    //position: 0 0 0.9
    //radius: 1
    //diffuseColor: 255 0 0
    //specularColor: 255 255 255
    //glossy: 4

    std::string cmd;
    //inputStream >> cmd;
    return std::make_unique<Plane>(Vector3(0, 0, 0), 15, Material(Color(0.25, 0.25, 0.25), Color(0,0,0), 4));
}