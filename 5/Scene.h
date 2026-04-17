#pragma once
#include <vector>
#include <limits>
#include "Object.h"
#include "Material.h"
#include "IntersectResult.h"

class Scene {
public:
    std::vector<Object&> objects;
    unsigned int Width = 500;
    unsigned int Height = 500;
    float planeDistance = 1;
    Vector3 cameraPosition = Vector3(0, 0, 0);
    Vector3 cameraForward = Vector3(1, 0, 0);
    Vector3 cameraUp = Vector3(0, 0, 1);
    Vector3 cameraRight = Vector3(0, 1, 0);

    Color ambientColor = Color(0.1, 0.1, 0.1);

    void AddObject(Object& obj) {
        objects.push_back(obj);
    }

    void Render() {
        float aspectRatio = (float)Width / (float)Height;
        cameraForward.Normalize();

        for(int i = 0; i < Width; i++) {
            for(int j=0; j < Height; j++) {
                Vector3 dir = cameraForward + cameraRight * ((float)i / (float)Width - 0.5) * 2 * aspectRatio - cameraUp * ((float)j / (float)Height - 0.5) * 2;
                Ray ray(cameraPosition, dir);
                Color pixelColor = RenderPixel(ray);
                std::printf("pixel %d %d : color (%f, %f, %f)\n", i, j, pixelColor.R, pixelColor.G, pixelColor.B);
            }
        }
    }

private:
    Color RenderPixel(Ray ray) {
        float minT = 100000;
        Material resultMaterial(Color(0, 0, 0));
        Vector3 resultNormal;
        IntersectResult intersectResult(false);
        for(Object& obj : objects) {
            intersectResult = obj.Intersect(ray);
            if (!intersectResult.intersect) {
                continue;
            } else {
                if (intersectResult.T <= minT) {
                    minT = intersectResult.T;
                    Vector3 resultNormal = intersectResult.normal;
                    resultMaterial = obj.material;
                }
            }
        }

        return resultMaterial.diffuseColor;
    }
};