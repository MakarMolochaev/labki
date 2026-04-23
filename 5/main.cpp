#include <iostream>
#include <memory>
#include "Scene.h"

int main() {
    Scene scene = Scene();
    scene.LoadScene("scene1.txt");
    scene.Render();
    return 0;
}