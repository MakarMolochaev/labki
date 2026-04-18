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
    //position: 0 0 0.9
    //radius: 1
    //diffuseColor: 255 0 0
    //specularColor: 255 255 255
    //glossy: 4

    std::string cmd;
    //inputStream >> cmd;
    return std::make_unique<Sphere>(Vector3(0, 0, 0.5), 1, Material(Color(1, 0, 0), Color(1, 1, 1), 4));
}