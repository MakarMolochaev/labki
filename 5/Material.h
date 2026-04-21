#pragma once
#include <fstream>
#include <cmath>
#include "Color.h"

class Material {
public:
    Color diffuseColor;
    Color specularColor;
    float glossy = 4;
    float reflectFactor = 0.5f;

    Material() = default;

    Material(Color diffuse){
        diffuseColor = diffuse;
        specularColor = Color(0, 0, 0);
        glossy = 8;
    }

    Material(Color diffuse, float glossiness){
        diffuseColor = diffuse;
        specularColor = Color(1, 1, 1);
        glossy = glossiness;
    }

    Material(Color diffuse, Color specular, float glossiness) {
        diffuseColor = diffuse;
        specularColor = specular;
        glossy = std::min(std::max(2.0f, glossiness), 256.0f);
    }

    void FillWithValues(std::ifstream& inputStream);
};