#include <iostream>
#include <memory>
#include "Scene.h"

int main(int argc, char** argv) {
    std::string sceneName = "scene1.txt";
    if(argc > 1) {
        sceneName = argv[1];
    }
    Scene scene = Scene();
    scene.LoadScene(sceneName);
    scene.Render("output.bmp");
    return 0;
}