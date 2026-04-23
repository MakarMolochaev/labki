#include <iostream>
#include <memory>
#include "Scene.h"
#include "ObjReader.h"

int main() {
    Scene scene = Scene();
    scene.LoadScene("scene1.txt");
    std::vector<std::unique_ptr<Triangle>> triangles = loadOBJ("hand.obj");
    for(auto& t : triangles) {
        scene.AddObject(std::move(t));
    }
    std::cout << "Added model with " << triangles.size() << " triangles.\n";
    scene.Render();
    return 0;
}