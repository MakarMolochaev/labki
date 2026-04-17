#pragma once
#include <vector>
#include <limits>
#include <memory>
#include "Object.h"
#include "Material.h"
#include "IntersectResult.h"
#include "BMPWriter.h"

class Scene {
public:
    std::vector<std::unique_ptr<Object>> objects;
    unsigned int Width = 1920;
    unsigned int Height = 1080;
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

        for(unsigned i = 0; i < Width; i++) {
            for(unsigned j = 0; j < Height; j++) {
                Vector3 dir = cameraForward * planeDistance
                    + cameraRight * ((float)i / (float)Width - 0.5) * 2 * aspectRatio
                    - cameraUp * ((float)j / (float)Height - 0.5) * 2;

                dir.Normalize();

                Ray ray(cameraPosition, dir);
                Color pixelColor = RenderPixel(ray);

                colorBuffer[j * Width + i] = pixelColor;
               //std::printf("ray: (%f, %f, %f), pixel (%d %d), color (%f, %f, %f)\n", dir.X, dir.Y, dir.Z, i, j, pixelColor.R, pixelColor.G, pixelColor.B);
            }
        }

        WriteBMP(Width, Height, colorBuffer);
    }

private:
    Color RenderPixel(Ray ray) {
        float minT = 100000;
        Material resultMaterial(Color(0, 0, 0));
        Vector3 resultNormal;
        IntersectResult intersectResult(false);
        for(std::unique_ptr<Object>& obj : objects) {
            intersectResult = obj->Intersect(ray);
            if (!intersectResult.intersect) {
                continue;
            } else {
                if (intersectResult.t <= minT) {
                    minT = intersectResult.t;
                    Vector3 resultNormal = intersectResult.normal;
                    resultMaterial = obj->material;
                }
            }
        }

        if(!intersectResult.intersect) {
            return ambientColor;
        }

        return resultMaterial.diffuseColor;
    }
};