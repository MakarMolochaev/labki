#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <string>
#include <cstdlib>
#include "Vector3.h"
#include "Object.h"


std::vector<std::unique_ptr<Triangle>> loadOBJ(const std::string& filename) {

    Material mat = Material(Color(0.6,0.6,0.6), Color(1,1,1), 8);

    std::vector<std::unique_ptr<Triangle>> triangles;
    std::vector<Vector3> vertices;
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return triangles;
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t start = line.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) continue; // пустая строка

        // Комментарии
        if (line[start] == '#') continue;

        std::istringstream iss(line.substr(start));
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            float x, y, z;
            if (!(iss >> x >> y >> z)) continue;
            vertices.push_back(Vector3(x, y, z));
        }
        else if (prefix == "f") {
            std::vector<int> faceIndices;
            std::string token;
            while (iss >> token) {
                size_t slashPos = token.find('/');
                std::string indexStr = (slashPos == std::string::npos) ? token : token.substr(0, slashPos);
                int idx = std::atoi(indexStr.c_str());
                if (idx == 0) continue;

                if (idx < 0) {
                    idx = static_cast<int>(vertices.size()) + idx + 1;
                }
                faceIndices.push_back(idx);
            }

            if (faceIndices.size() < 3) {
                continue;
            }

            const int numVertices = static_cast<int>(faceIndices.size());
            for (int i = 1; i < numVertices - 1; ++i) {
                int i0 = faceIndices[0] - 1;     // OBJ индексы с 1
                int i1 = faceIndices[i] - 1;
                int i2 = faceIndices[i + 1] - 1;

                if (i0 < 0 || i0 >= (int)vertices.size() ||
                    i1 < 0 || i1 >= (int)vertices.size() ||
                    i2 < 0 || i2 >= (int)vertices.size()) {
                    continue;
                }

                std::unique_ptr<Triangle> tr = std::make_unique<Triangle>(vertices[i0], vertices[i1], vertices[i2]);
                tr->material = mat;

                triangles.push_back(std::move(tr));
            }
        }
    }

    return triangles;
}