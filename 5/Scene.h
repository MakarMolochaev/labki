#pragma once
#include <vector>
#include <limits>
#include <memory>
#include <omp.h>
#include "Object.h"
#include "Material.h"
#include "IntersectResult.h"
#include "BMPWriter.h"
#include "PointLight.h"

//38400x21600 - 55s
class Scene {
public:
    std::vector<std::unique_ptr<Object>> objects;
    std::vector<std::unique_ptr<PointLight>> lights;

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

    void AddLight(std::unique_ptr<PointLight> light) {
        lights.push_back(std::move(light));
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
                + cameraUp * ((float)j / (float)Height - 0.5) * 2;

            dir.Normalize();
            Ray ray(cameraPosition, dir);

            float minT = 100000.0f;
            Material resultMaterial(Color(0, 0, 0));
            Vector3 resultNormal;
            Vector3 impactPoint;
            bool hitAnything = false;

            for (const auto& obj : objects) {
                IntersectResult intersectResult = obj->Intersect(ray);
                if (intersectResult.hit) {
                    if (intersectResult.t < minT) {
                        minT = intersectResult.t;
                        resultNormal = intersectResult.normal;
                        impactPoint = intersectResult.point;
                        resultMaterial = obj->material;
                        hitAnything = true;
                    }
                }
            }

            if (!hitAnything) {
                colorBuffer[index] = ambientColor;
            } else {

                Color resultColor(0.0f, 0.0f, 0.0f);

                for (const auto& light : lights) {
                    Vector3 lightDir = (light->position - impactPoint).Normalized();

                    float normalCos = Vector3::Dot(resultNormal, lightDir);
                    float diffuseFactor = std::max(0.0f, normalCos);

                    Vector3 viewDir = (cameraPosition - impactPoint).Normalized();
                    Vector3 idealReflect = resultNormal * 2 * normalCos - lightDir;
                    float specCos = Vector3::Cos(idealReflect, viewDir);
                    float specularFactor = std::pow(std::max(0.0f, specCos), resultMaterial.glossy) * diffuseFactor;

                    resultColor = resultColor +
                        resultMaterial.diffuseColor * light->color * light->intensity * diffuseFactor +
                        resultMaterial.specularColor * light->color * light->intensity * specularFactor;
                }

                resultColor = resultColor + ambientColor * resultMaterial.diffuseColor * 1.0f;

                colorBuffer[index] = Color(
                    std::min(resultColor.R, 1.0f),
                    std::min(resultColor.G, 1.0f),
                    std::min(resultColor.B, 1.0f)
                );
            }
        }

        WriteBMP(Width, Height, colorBuffer);
    }
};