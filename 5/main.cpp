#include <iostream>
#include <memory>
#include "Scene.h"

int main(int argc, char** argv) {
    Scene scene = Scene();
    scene.LoadScene("scene2.txt");
    scene.Render();
    return 0;
}