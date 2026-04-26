#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include "Object.h"
#include "Vector3.h"
#include "Ray.h"

IntersectResult Tetrahedron::Intersect(const Ray& ray) const {

    IntersectResult intersect = IntersectResult(false);
    float minT = 1000000;
    for(int i = 0; i < 4; i++) {
        IntersectResult intr = this->trs[i].Intersect(ray);
        if (intr.hit && intr.t <= minT) {
            intersect = intr;
            minT = intr.t;
        }
    }
    return intersect;
}

std::unique_ptr<Object> Tetrahedron::Instantiate(std::ifstream& inputStream) const {
    std::unique_ptr<Tetrahedron> result = std::make_unique<Tetrahedron>();

    std::string cmd = "";
    while (cmd != "}") {
        if (cmd == "A:") {
            inputStream >> cmd;
            result->P[0].X = std::stod(cmd);
            inputStream >> cmd;
            result->P[0].Y = std::stod(cmd);
            inputStream >> cmd;
            result->P[0].Z = std::stod(cmd);
            continue;
        } else if (cmd == "B:") {
            inputStream >> cmd;
            result->P[1].X = std::stod(cmd);
            inputStream >> cmd;
            result->P[1].Y = std::stod(cmd);
            inputStream >> cmd;
            result->P[1].Z = std::stod(cmd);
            continue;
        } else if (cmd == "C:") {
            inputStream >> cmd;
            result->P[2].X = std::stod(cmd);
            inputStream >> cmd;
            result->P[2].Y = std::stod(cmd);
            inputStream >> cmd;
            result->P[2].Z = std::stod(cmd);
            continue;
        } else if (cmd == "D:") {
            inputStream >> cmd;
            result->P[3].X = std::stod(cmd);
            inputStream >> cmd;
            result->P[3].Y = std::stod(cmd);
            inputStream >> cmd;
            result->P[3].Z = std::stod(cmd);
            continue;
        } else if (cmd == "Material") {
            result->material.FillWithValues(inputStream);
            inputStream >> cmd;
            continue;
        }

        inputStream >> cmd;
    }

    result->trs = { 
        Triangle(result->P[0], result->P[1], result->P[2]),
        Triangle(result->P[0], result->P[1], result->P[3]),
        Triangle(result->P[0], result->P[2], result->P[3]),
        Triangle(result->P[1], result->P[2], result->P[3])
    };

    return result;
}

Tetrahedron::Tetrahedron(Vector3 a, Vector3 b, Vector3 c, Vector3 d) : trs(4) {
    this->P[0] = a;
    this->P[1] = b;
    this->P[2] = c;
    this->P[3] = d;

    this->trs = { 
        Triangle(this->P[0], this->P[1], this->P[2]),
        Triangle(this->P[0], this->P[1], this->P[3]),
        Triangle(this->P[0], this->P[2], this->P[3]),
        Triangle(this->P[1], this->P[2], this->P[3])
    };
}