#include <iostream>
#include "Scene.h"

int main() {
    std::unique_ptr<Sphere> sphere = std::make_unique<Sphere>(Vector3(4,2,0), 1, Material(Color(1, 0, 0)));

    Scene scene = Scene();
    scene.AddObject(std::move(sphere));
    scene.Render();
    return 0;
}