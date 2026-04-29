#include "Object.h"
#include "Vector3.h"
#include "Ray.h"
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <cmath>
#include <limits>

IntersectResult Box::Intersect(const Ray& ray) const {
    float tEnter = -std::numeric_limits<float>::infinity();
    float tExit = std::numeric_limits<float>::infinity();
    Vector3 resultNormal = Vector3(0, 0, 0);

    float O[3] = { ray.start.X, ray.start.Y, ray.start.Z };
    float D[3] = { ray.dir.X, ray.dir.Y, ray.dir.Z };
    float pos[3] = { this->position.X, this->position.Y, this->position.Z };
    float sizes[3] = { this->size.X, this->size.Y, this->size.Z };
    Vector3 orts[3] = { Vector3(1,0,0), Vector3(0,1,0), Vector3(0,0,1) };

    for(int i=0;i<3;i++) {
        if (std::abs(D[i]) >= std::numeric_limits<float>::epsilon()) {
            float t0 = (pos[i] - sizes[i] - O[i]) / D[i];
            float t1 = (pos[i] + sizes[i] - O[i]) / D[i];
            if (t0 > t1) {
                std::swap(t0, t1);
            }

            if(t0 > tEnter) {
                tEnter = t0;
                resultNormal = orts[i] * (D[i] > 0 ? -1 : 1);
            }

            tExit  = std::min(tExit,  t1);

            if(tEnter > tExit) {
                return IntersectResult(false);
            }
        } else {
            if (O[i] < pos[i] - sizes[i] || O[i] > pos[i] + sizes[i]) {
                return IntersectResult(false);
            }
        }
    }

    if (tExit < 0 || tEnter < 0) {
        return IntersectResult(false);
    }
    return IntersectResult(true, ray.Travel(tEnter), resultNormal, tEnter);
}

std::unique_ptr<Object> Box::Instantiate(std::ifstream& inputStream) const {
    std::unique_ptr<Box> result = std::make_unique<Box>();

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
        } else if (cmd == "sizeX:") {
            inputStream >> cmd;
            result->size.X = std::stod(cmd);
            continue;
        } else if (cmd == "sizeY:") {
            inputStream >> cmd;
            result->size.Y = std::stod(cmd);
            continue;
        } else if (cmd == "sizeZ:") {
            inputStream >> cmd;
            result->size.Z = std::stod(cmd);
            continue;
        } else if (cmd == "Material") {
            result->material.FillWithValues(inputStream);
            inputStream >> cmd;
            continue;
        }

        inputStream >> cmd;
    }

    std::cout << "Results:\n" << result->position.X << result->position.Y << result->position.Z << "\n";
    std::cout << "Results:\n" << result->size.X << result->size.Y << result->size.Z << "\n";
    
    return result;
}