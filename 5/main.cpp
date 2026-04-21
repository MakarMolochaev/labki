#include <iostream>
#include "Scene.h"

int main() {
    Scene scene = Scene();
    scene.LoadScene("scene1.txt");
    scene.AddLight(std::move(std::make_unique<PointLight>(Vector3(3, -4, 2), Color(0, 1, 1), 2)));
    scene.AddLight(std::move(std::make_unique<PointLight>(Vector3(3, 2, 2), Color(1, 0, 1), 4)));
    scene.AddLight(std::move(std::make_unique<PointLight>(Vector3(-3, -3, 4), Color(1, 1, 1), 0.5f)));
    scene.Render();
    return 0;
}