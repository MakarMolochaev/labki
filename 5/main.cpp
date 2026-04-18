#include <iostream>
#include "Scene.h"

int main() {
    std::unique_ptr<Sphere> sphere = std::make_unique<Sphere>(Vector3(0, 0, 0.5), 1, Material(Color(1, 0, 0), Color(1, 1, 1), 4));
    std::unique_ptr<Plane> plane = std::make_unique<Plane>(Vector3(0, 0, 0), 15, Material(Color(0.25, 0.25, 0.25), Color(0,0,0), 4));

    Scene scene = Scene();
    scene.LoadScene("scene1.txt");

    scene.AddObject(std::move(sphere));
    scene.AddObject(std::move(plane));
    scene.AddLight(std::move(std::make_unique<PointLight>(Vector3(3, -4, 2), Color(0, 1, 1), 2)));
    scene.AddLight(std::move(std::make_unique<PointLight>(Vector3(3, 2, 2), Color(1, 0, 1), 4)));
    scene.AddLight(std::move(std::make_unique<PointLight>(Vector3(-3, -3, 4), Color(1, 1, 1), 0.5f)));
    scene.Render();
    return 0;
}