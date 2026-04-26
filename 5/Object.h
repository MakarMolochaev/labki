#pragma once
#include <memory>
#include <vector>
#include "Material.h"
#include "IntersectResult.h"
#include "Ray.h"

class Object {
public:
    Vector3 position;
    Material material;
    Object() = default;

    virtual IntersectResult Intersect(const Ray& ray) const = 0;
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

    IntersectResult Intersect(const Ray& ray) const override;
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

    IntersectResult Intersect(const Ray& ray) const override;
    std::unique_ptr<Object> Instantiate(std::ifstream& inputStream) const override;
};

class Triangle : public Object {
public:
    Triangle() = default;
    Triangle(Vector3 a, Vector3 b, Vector3 c);

    Vector3 A, B, C;
    Vector3 E1, E2, normal;

    IntersectResult Intersect(const Ray& ray) const override;
    std::unique_ptr<Object> Instantiate(std::ifstream& inputStream) const override;
    void Precalculate();
};

class Tetrahedron : public Object {
public:
    Tetrahedron() = default;
    Tetrahedron(Vector3 a, Vector3 b, Vector3 c, Vector3 d);

    Vector3 P[4];
    std::vector<Triangle> trs;

    IntersectResult Intersect(const Ray& ray) const override;
    std::unique_ptr<Object> Instantiate(std::ifstream& inputStream) const override;
};