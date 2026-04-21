#include <fstream>
#include <iostream>
#include <random>
#include "Scene.h"
#include "ObjectFactory.h"
#include "BMPWriter.h"

Ray Scene::Perspective(int x, int y, float aspectRatio, float offsetX, float offsetY) {
    Vector3 dir = CameraForward * PlaneDistance
                + CameraRight * (((float)x + offsetX) / (float)(Width * SSAA) - 0.5) * 2 * aspectRatio
                + CameraUp * (((float)y + offsetY) / (float)(Height * SSAA) - 0.5) * 2;
    
    return Ray(CameraPosition, dir.Normalized());
}

Ray Scene::Orthogonal(int x, int y, float aspectRatio, float size) {
    Vector3 start = CameraRight * ((float)x / (float)(Width * SSAA) - 0.5) * 2 * aspectRatio * size
        + CameraUp * ((float)y / (float)(Height * SSAA) - 0.5) * 2 * size;
    
    return Ray(CameraPosition, CameraForward);
}

bool Scene::FindClosestIntersection(const Ray& ray, float& outMinT, Vector3& outNormal, Vector3& outPoint, Material& outMaterial) const
{
    float minT = std::numeric_limits<float>::infinity();
    bool hitAnything = false;

    for (const auto& obj : objects) {
        IntersectResult res = obj->Intersect(ray);
        if (res.hit && res.t < minT && res.t > 0.0f) {
            minT = res.t;
            outNormal = res.normal;
            outPoint = res.point;
            outMaterial = obj->material;
            hitAnything = true;
        }
    }

    if (hitAnything) {
        outMinT = minT;
    }
    return hitAnything;
}

bool Scene::RayCast(const Ray& ray, float maxDistance, float* outT) const
{
    for (const auto& obj : objects) {
        IntersectResult res = obj->Intersect(ray);
        
        if (res.hit && res.t > 0.0f && res.t < maxDistance) {
            if (outT) *outT = res.t;
            return true;
        }
    }
    return false;
}

void Scene::Render() {
    std::cout << "Render started\n";
    
    omp_set_num_threads(16);
    float aspectRatio = (float)Width / (float)Height;
    CameraForward.Normalize();

    int totalPixels = Width * Height * SSAA * SSAA;
    std::vector<Color> colorBuffer(totalPixels);

    std::default_random_engine rand;
    std::uniform_real_distribution<double> dist(-0.25f, 0.25f);
    std::vector<float> jitter(SSAA * SSAA * 2);
    if(SSAA != 1 && SSAAJitter) {
        for(int i = 0; i < SSAA * SSAA * 2; i++) {
            jitter[i] = dist(rand);
        }
    }

    #pragma omp parallel for schedule(dynamic)
    for (int index = 0; index < totalPixels; index++) {
        int i = index % (Width * SSAA);
        int j = index / (Width * SSAA);

        float offsetX = jitter[((i % SSAA) * SSAA + j % SSAA) * 2];
        float offsetY = jitter[((i % SSAA) * SSAA + j % SSAA) * 2 + 1];

        Ray ray = Perspective(i, j, aspectRatio, offsetX, offsetY);

        Trace(ray, colorBuffer, index);
    }

    std::vector<Color> resultColorBuffer(Width * Height);

    #pragma omp parallel for collapse(2) schedule(dynamic)
    for(int y = 0;y<Height;y++) {
        for(int x = 0; x< Width;x++) {
            Color sum(0.0f, 0.0f, 0.0f);

            for (int sy = 0; sy < SSAA; sy++) {
                for (int sx = 0; sx < SSAA; sx++) {
                    int bigX = x * SSAA + sx;
                    int bigY = y * SSAA + sy;

                    int indexInBigBuffer = bigY * (Width * SSAA) + bigX;

                    sum = sum + colorBuffer[indexInBigBuffer];
                }
            }

            float avg = 1.0f / (SSAA * SSAA);
            resultColorBuffer[y * Width + x] = Color(
                pow(sum.R * avg, 1.0f/2.2f),
                pow(sum.G * avg, 1.0f/2.2f),
                pow(sum.B * avg, 1.0f/2.2f)
            );
        }
    }

    WriteBMP(Width, Height, resultColorBuffer);
}

void Scene::Trace(Ray &ray, std::vector<Color> &colorBuffer, int index)
{
    float minT = 100000.0f;
    Material resultMaterial;
    Vector3 resultNormal;
    Vector3 impactPoint;
    bool hitAnything = FindClosestIntersection(ray, minT, resultNormal, impactPoint, resultMaterial);

    if (!hitAnything)
    {
        colorBuffer[index] = worldColor;
    }
    else
    {
        Color resultColor(0.0f, 0.0f, 0.0f);

        for (const auto &light : lights)
        {
            Vector3 toLight = light->position - impactPoint;
            Vector3 lightDir = toLight.Normalized();

            // shadows
            bool isShadowed = false;
            if (ShadowsEnabled)
            {
                Ray toLightRay = Ray(impactPoint + lightDir * 0.0001f, lightDir);
                if (RayCast(toLightRay, toLight.Length() - 0.0001f))
                {
                    isShadowed = true;
                }
            }

            if (!isShadowed)
            {
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

        resultColor = resultColor + worldColor * resultMaterial.diffuseColor * 0.97f;

        // AO
        if (AOEnabled)
        {
            float AOFactor = 1.0f;
            Ray AORay = Ray(impactPoint + resultNormal * 0.0001, resultNormal);
            float AO_t;
            if (RayCast(AORay, AOSize, &AO_t))
            {
                AOFactor = (AO_t + 0.02f) / (AOSize + 0.02f);
            }
            resultColor = resultColor * std::pow(AOFactor, 0.8f);
        }

        colorBuffer[index] = Color(
            std::min(resultColor.R, 1.0f),
            std::min(resultColor.G, 1.0f),
            std::min(resultColor.B, 1.0f));
    }
}

void Scene::LoadScene(std::string filename) {

    ObjectFactory factory;
    factory.RegisterType<Sphere>("Sphere");
    factory.RegisterType<Plane>("Plane");

    std::ifstream input;
    input.open(filename);

    std::string tok;
    while(input >> tok) {
        if (tok == "Set") {
            std::string cmd;
            input >> cmd;
            if (cmd == "Width") {
                input >> cmd;
                this->Width = std::stoi(cmd);
            } else if (cmd == "Height") {
                input >> cmd;
                this->Height = std::stoi(cmd);
            } else if (cmd == "SSAA") {
                input >> cmd;
                this->SSAA = std::stoi(cmd);
            } else if (cmd == "SSAA_Jitter") {
                input >> cmd;
                this->SSAAJitter = (cmd == "Enabled");
            } else if (cmd == "AO") {
                input >> cmd;
                this -> AOEnabled = (cmd == "Enabled");
            } else if (cmd == "AOsize") {
                input >> cmd;
                this->AOSize = std::stod(cmd);
            } else if (cmd == "Shadows") {
                input >> cmd;
                this->ShadowsEnabled = (cmd == "Enabled");
            } else if (cmd == "WorldColor") {
                Color worldColor;
                input >> worldColor.R >> worldColor.G >> worldColor.B;
                worldColor = worldColor * (1.0 / 255.0);
                this->worldColor = worldColor;
            } else if (cmd == "CameraPos") {
                input >> this->CameraPosition.X >> this->CameraPosition.Y >> this->CameraPosition.Z;
            }
        } else if (tok == "AddObject") {
            std::string objectType;
            input >> objectType;
            std::unique_ptr<Object> obj = factory.Create(objectType, input);
            this->AddObject(std::move(obj));
            std::cout << "Object added: " << objectType << "\n";
        } else if (tok == "AddLight") {
            
        }
    }
}