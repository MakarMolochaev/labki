#pragma once
#include "Material.h"
#include "IntersectResult.h"
#include "Ray.h"

class Object {
public:
    Vector3 position;
    Material material;
    Object() = default;

    virtual IntersectResult Intersect(Ray ray) const = 0;
    virtual ~Object() = default;
};

class Sphere : public Object {
public:
    float radius;
    Sphere(Vector3 pos, float radius, Material mat) {
        this->radius = radius;
        position = pos;
        material = mat;
    }

    IntersectResult Intersect(Ray ray) const override;
};