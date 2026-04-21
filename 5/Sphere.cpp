#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include "Object.h"
#include "Vector3.h"
#include "Ray.h"

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

std::unique_ptr<Object> Sphere::Instantiate(std::ifstream& inputStream) const {
    std::unique_ptr<Sphere> result = std::make_unique<Sphere>();

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
        } else if (cmd == "radius:") {
            inputStream >> cmd;
            result->radius = std::stod(cmd);
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