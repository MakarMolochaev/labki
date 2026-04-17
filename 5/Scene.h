#pragma once
#include <vector>
#include <limits>
#include <memory>
#include <omp.h>
#include "Object.h"
#include "Material.h"
#include "IntersectResult.h"
#include "BMPWriter.h"

class Scene {
public:
    std::vector<std::unique_ptr<Object>> objects;
    unsigned int Width = 19200;
    unsigned int Height = 10800;
    float planeDistance = 1;
    Vector3 cameraPosition = Vector3(0, 0, 0);
    Vector3 cameraForward = Vector3(1, 0, 0);
    Vector3 cameraUp = Vector3(0, 0, 1);
    Vector3 cameraRight = Vector3(0, 1, 0);

    Color ambientColor = Color(0.05, 0.05, 0.05);

    void AddObject(std::unique_ptr<Object> obj) {
        objects.push_back(std::move(obj));
    }

    void Render() {
        float aspectRatio = (float)Width / (float)Height;
        cameraForward.Normalize();

        std::vector<Color> colorBuffer(Width * Height);

        int totalPixels = Width * Height;

        #pragma omp parallel for schedule(dynamic)
        for (int index = 0; index < totalPixels; index++) {
            int i = index % Width;
            int j = index / Width;

            Vector3 dir = cameraForward * planeDistance
                + cameraRight * ((float)i / (float)Width - 0.5) * 2 * aspectRatio
                - cameraUp * ((float)j / (float)Height - 0.5) * 2;

            dir.Normalize();
            Ray ray(cameraPosition, dir);

            float minT = 100000.0f;
            Material resultMaterial(Color(0, 0, 0));
            Vector3 resultNormal;
            bool hitAnything = false;

            for (const auto& obj : objects) {
                IntersectResult intersectResult = obj->Intersect(ray);
                if (intersectResult.hit) {
                    if (intersectResult.t < minT) {
                        minT = intersectResult.t;
                        resultMaterial = obj->material;
                        hitAnything = true;
                    }
                }
            }

            if (!hitAnything) {
                colorBuffer[index] = ambientColor;
            } else {
                colorBuffer[index] = resultMaterial.diffuseColor;
            }
        }

        WriteBMP(Width, Height, colorBuffer);
    }
};