#pragma once
#include <vector>
#include <limits>
#include <memory>
#include <omp.h>
#include <string>
#include "Object.h"
#include "Material.h"
#include "IntersectResult.h"
#include "PointLight.h"

//38400x21600 - 55s
class Scene {
public:
    std::vector<std::unique_ptr<Object>> objects;
    std::vector<std::unique_ptr<PointLight>> lights;

    unsigned int Width = 1920;
    unsigned int Height = 1080;
    float PlaneDistance = 1;
    Vector3 CameraPosition = Vector3(-7, 0, 3);
    Vector3 CameraForward = Vector3(1, 0, 0).Normalized();
    Vector3 CameraUp = Vector3(0, 0, 1).Normalized();
    Vector3 CameraRight = Vector3(0, 1, 0).Normalized();
    
    Color worldColor = Color(1, 1, 1);
    unsigned int SSAA = 2;
    bool SSAAJitter = true;
    float AOSize = 0.1f;
    bool AOEnabled = true;
    bool ShadowsEnabled = true;


    void AddObject(std::unique_ptr<Object> obj) {
        objects.push_back(std::move(obj));
    }

    void AddLight(std::unique_ptr<PointLight> light) {
        lights.push_back(std::move(light));
    }

    void LoadScene(std::string filename);

    bool FindClosestIntersection(const Ray& ray, float& outMinT, Vector3& outNormal, Vector3& outPoint, Material& outMaterial) const;

    bool RayCast(const Ray& ray, float maxDistance = std::numeric_limits<float>::infinity(), float* outT = nullptr) const;

    void Render();

    Color Trace(Ray &ray);

private:

    Ray Perspective(int x, int y, float aspectRatio, float offsetX, float offsetY);

    Ray Orthogonal(int x, int y, float aspectRatio, float size = 1);
};