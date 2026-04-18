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
    float PlaneDistance = 1;
    Vector3 CameraPosition = Vector3(-7, 0, 3);
    Vector3 CameraForward = Vector3(1, 0, 0).Normalized();
    Vector3 CameraUp = Vector3(0, 0, 1).Normalized();
    Vector3 CameraRight = Vector3(0, 1, 0).Normalized();
    
    Color ambientColor = Color(1, 1, 1);
    unsigned int SS = 4;
    float AOSize = 0.1f;
    bool AOEnabled = true;
    bool ShadowsEnabled = true;


    void AddObject(std::unique_ptr<Object> obj) {
        objects.push_back(std::move(obj));
    }

    void AddLight(std::unique_ptr<PointLight> light) {
        lights.push_back(std::move(light));
    }

    void Render() {
        omp_set_num_threads(16);
        float aspectRatio = (float)Width / (float)Height;
        CameraForward.Normalize();

        int totalPixels = Width * Height * SS * SS;
        std::vector<Color> colorBuffer(totalPixels);

        #pragma omp parallel for schedule(dynamic)
        for (int index = 0; index < totalPixels; index++) {
            int i = index % (Width * SS);
            int j = index / (Width * SS);

            Ray ray = Perspective(i, j, aspectRatio);

            float minT = 100000.0f;
            Material resultMaterial;
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
                    Vector3 toLight = light->position - impactPoint;
                    Vector3 lightDir = toLight.Normalized();
                    
                    //shadow
                    bool isShadowed = false;
                    if (ShadowsEnabled) {
                        Ray toLightRay = Ray(impactPoint + lightDir * 0.0001, lightDir);
                        for (const auto& obj : objects) {
                            IntersectResult intersectRes = obj->Intersect(toLightRay);
                            if (intersectRes.hit) {
                                if (0 <= intersectRes.t && intersectRes.t <= toLight.Length()) {
                                    isShadowed = true;
                                    break;
                                }
                            }
                        }
                    }
                    
                    if (!isShadowed) {
                        float normalCos = Vector3::Dot(resultNormal, lightDir);
                        Vector3 idealReflect = (resultNormal * 2 * normalCos - lightDir).Normalized();
                        float diffuseFactor = std::max(0.0f, normalCos);
                        
                        Vector3 viewDir = (CameraPosition - impactPoint).Normalized();
                        float specCos = Vector3::Cos(idealReflect, viewDir);
                        float specularFactor = std::pow(std::max(0.0f, specCos), resultMaterial.glossy) * diffuseFactor;
    
                        resultColor = resultColor +
                            resultMaterial.diffuseColor * light->color * light->intensity * diffuseFactor +
                            resultMaterial.specularColor * light->color * light->intensity * specularFactor;

                    }
                }

                //AO
                float AOFactor = 1.0f;
                if (AOEnabled) {
                    Ray AORay = Ray(impactPoint + resultNormal * 0.0001, resultNormal);
                    for (const auto& obj : objects) {
                        IntersectResult intersectRes = obj->Intersect(AORay);
                        if (intersectRes.hit) {
                            if (0 <= intersectRes.t && intersectRes.t <= AOSize) {
                                AOFactor = (intersectRes.t + 0.02f) / (AOSize + 0.02f);
                                break;
                            }
                        }
                    }
                }

                resultColor = resultColor + ambientColor * resultMaterial.diffuseColor * 0.97f;
                
                resultColor = resultColor * std::pow(AOFactor, 0.8f);
                
                colorBuffer[index] = Color(
                    std::min(resultColor.R, 1.0f),
                    std::min(resultColor.G, 1.0f),
                    std::min(resultColor.B, 1.0f)
                );
            }
        }

        std::vector<Color> resultColorBuffer(Width * Height);

        #pragma omp parallel for collapse(2) schedule(dynamic)
        for(int y = 0;y<Height;y++) {
            for(int x = 0; x< Width;x++) {
                Color sum(0.0f, 0.0f, 0.0f);

                for (int sy = 0; sy < SS; sy++) {
                    for (int sx = 0; sx < SS; sx++) {
                        int bigX = x * SS + sx;
                        int bigY = y * SS + sy;

                        int indexInBigBuffer = bigY * (Width * SS) + bigX;

                        sum = sum + colorBuffer[indexInBigBuffer];
                    }
                }

                float avg = 1.0f / (SS * SS);
                resultColorBuffer[y * Width + x] = Color(
                    pow(sum.R * avg, 1.0f/2.2f),
                    pow(sum.G * avg, 1.0f/2.2f),
                    pow(sum.B * avg, 1.0f/2.2f)
                );
            }
        }

        WriteBMP(Width, Height, resultColorBuffer);
    }


private:

    Ray Perspective(int x, int y, float aspectRatio) {
        Vector3 dir = CameraForward * PlaneDistance
                    + CameraRight * ((float)x / (float)(Width*SS) - 0.5) * 2 * aspectRatio
                    + CameraUp * ((float)y / (float)(Height*SS) - 0.5) * 2;
        
        return Ray(CameraPosition, dir.Normalized());
    }

    Ray Ortogonal(int x, int y, float aspectRatio, float size = 1) {
        Vector3 start = CameraRight * ((float)x / (float)(Width*SS) - 0.5) * 2 * aspectRatio * size
            + CameraUp * ((float)y / (float)(Height*SS) - 0.5) * 2 * size;
        
        return Ray(CameraPosition, CameraForward);
    }
};