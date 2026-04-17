#pragma once
#include "Color.h"
#include <cmath>

class Material {
public:
    Color diffuseColor;
    Color specularColor;
    float glossy;

    Material(Color diffuse, Color specular, float glossiness) {
        diffuseColor = diffuse;
        specularColor = specular;
        glossy = std::fmin(std::fmax(2.0, glossiness), 256);
    }
};