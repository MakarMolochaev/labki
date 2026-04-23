#pragma once
#include <memory>
#include "Material.h"
#include "IntersectResult.h"
#include "Ray.h"

class Object {
public:
    Vector3 position;
    Material material;
    Object() = default;

    virtual IntersectResult Intersect(Ray ray) const = 0;
    virtual std::unique_ptr<Object> Instantiate(std::ifstream& inputStream) const = 0;
    virtual ~Object() = default;
};

class Sphere : public Object {
public:
    Sphere() = default;
    
    float radius;
    Sphere(Vector3 pos, float radius, Material mat) {
        this->radius = radius;
        position = pos;
        material = mat;
    }

    IntersectResult Intersect(Ray ray) const override;
    std::unique_ptr<Object> Instantiate(std::ifstream& inputStream) const override;
};

class Plane : public Object {
public:
    Plane() = default;

    float size;
    Plane(Vector3 pos, float size, Material mat) {
        this->size = size;
        position = pos;
        material = mat;
    }

    IntersectResult Intersect(Ray ray) const override;
    std::unique_ptr<Object> Instantiate(std::ifstream& inputStream) const override;
};

class Triangle : public Object {
public:
    Triangle() = default;
    Triangle(Vector3 a, Vector3 b, Vector3 c);

    Vector3 A, B, C;

    IntersectResult Intersect(Ray ray) const override;
    std::unique_ptr<Object> Instantiate(std::ifstream& inputStream) const override;
};