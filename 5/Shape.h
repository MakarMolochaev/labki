#pragma once
#include "Material.h"
#include "IntersectResult.h"
#include "Ray.h"

class Shape {
public:
    Vector3 position;
    Material material;
    Shape();

    virtual IntersectResult Intersect(Ray ray) const = 0;
    virtual ~Shape() = default;
};

class Sphere : public Shape {
public:
    float radius;
    Sphere(Vector3 pos, float radius, Material mat) {
        this->radius = radius;
        position = pos;
        material = mat;
    }

    IntersectResult Intersect(Ray ray) const override;
};