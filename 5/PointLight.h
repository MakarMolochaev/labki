#pragma once
#include "Color.h"
#include "Vector3.h"

class PointLight {
public:
    Vector3 position;
    Color color;
    float intensity;

    PointLight() = default;

    PointLight(Vector3 pos, Color clr, float intensity = 1) : position(pos), color(clr), intensity(intensity) {}

    void FillWithValues(std::ifstream& inputStream);
};