#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include "Object.h"
#include "Vector3.h"
#include "Ray.h"

IntersectResult Triangle::Intersect(const Ray& ray) const {
    Vector3 P = Vector3::Cross(ray.dir, this->E2);
    float det = Vector3::Dot(this->E1, P);
    if(std::abs(det) <= 0.000001){
        return IntersectResult(false);
    }

    float inv_det = 1.0f / det;
    Vector3 T = ray.start - this->A;
    float u = Vector3::Dot(T, P) * inv_det;
    if(u < 0 || u > 1){
        return IntersectResult(false);
    }
    Vector3 Q = Vector3::Cross(T, this->E1);
    float v = Vector3::Dot(ray.dir, Q) * inv_det;
    if(v < 0 || u + v > 1) {
        return IntersectResult(false);
    }
    float t = Vector3::Dot(this->E2, Q) * inv_det;

    if(t > 0) {
        return IntersectResult(true, ray.Travel(t), (Vector3::Dot(ray.dir, this->normal) > 0) ? this->normal * -1.0f : this->normal, t);
    }

    return IntersectResult(false);
}

std::unique_ptr<Object> Triangle::Instantiate(std::ifstream& inputStream) const {
    std::unique_ptr<Triangle> result = std::make_unique<Triangle>();

    std::string cmd = "";
    while (cmd != "}") {
        if (cmd == "A:") {
            inputStream >> cmd;
            result->A.X = std::stod(cmd);
            inputStream >> cmd;
            result->A.Y = std::stod(cmd);
            inputStream >> cmd;
            result->A.Z = std::stod(cmd);
            continue;
        } else if (cmd == "B:") {
            inputStream >> cmd;
            result->B.X = std::stod(cmd);
            inputStream >> cmd;
            result->B.Y = std::stod(cmd);
            inputStream >> cmd;
            result->B.Z = std::stod(cmd);
            continue;
        } else if (cmd == "C:") {
            inputStream >> cmd;
            result->C.X = std::stod(cmd);
            inputStream >> cmd;
            result->C.Y = std::stod(cmd);
            inputStream >> cmd;
            result->C.Z = std::stod(cmd);
            continue;
        } else if (cmd == "Material") {
            result->material.FillWithValues(inputStream);
            inputStream >> cmd;
            continue;
        }

        inputStream >> cmd;
    }

    result->Precalculate();

    return result;
}

void Triangle::Precalculate() {
    this->E1 = this->B - this->A;
    this->E2 = this->C - this->A;
    this->normal = Vector3::Cross(this->E1, this->E2);
}

Triangle::Triangle(Vector3 a, Vector3 b, Vector3 c) {
    this->A = a;
    this->B = b;
    this->C = c;

    this->Precalculate();
}