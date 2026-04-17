#include <iostream>
#include "Scene.h"

int main(int argc, char** argv) {
    Sphere sphere = Sphere(Vector3(6,0,0), 1, Material(Color(1, 0, 0)));

    Scene scene = Scene();
    scene.AddObject(sphere);
    scene.Render();
    return 0;
}