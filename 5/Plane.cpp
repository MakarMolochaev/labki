#include "Object.h"
#include "Vector3.h"
#include "Ray.h"
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <cmath>
#include <limits>

IntersectResult Plane::Intersect(const Ray& ray) const {
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
    std::unique_ptr<Plane> result = std::make_unique<Plane>();

    std::string cmd = "";
    while (cmd != "}") {
        if (cmd == "position:") {
            inputStream >> cmd;
            result->position.X = std::stod(cmd);
            inputStream >> cmd;
            result->position.Y = std::stod(cmd);
            inputStream >> cmd;
            result->position.Z = std::stod(cmd);
            continue;
        } else if (cmd == "size:") {
            inputStream >> cmd;
            result->size = std::stod(cmd);
            continue;
        } else if (cmd == "Material") {
            result->material.FillWithValues(inputStream);
            inputStream >> cmd;
            continue;
        }

        inputStream >> cmd;
    }

    return result;
}