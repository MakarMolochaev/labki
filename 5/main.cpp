#include <iostream>
#include "Scene.h"

int main() {
    std::unique_ptr<Sphere> sphere = std::make_unique<Sphere>(Vector3(4,0,0), 1, Material(Color(1, 0, 0), Color(1,1,1), 4));

    Scene scene = Scene();
    scene.AddObject(std::move(sphere));
    scene.AddLight(std::move(std::make_unique<PointLight>(Vector3(3, 0, 2), Color(1,1,1), 2)));
    scene.Render();
    return 0;
}