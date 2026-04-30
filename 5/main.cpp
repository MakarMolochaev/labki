#include <iostream>
#include <memory>
#include <string>
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
    

    /*
    Scene scene = Scene();
    scene.LoadScene("scene3.txt");

    for(int i=0; i<50; i++) {
        float time = 1.0 / 24.0 * (float)i;
        scene.objects[0]->position.X = cos(time * 6.0);
        scene.objects[0]->position.Z = 0.7;
        scene.objects[0]->position.Y = sin(time * 6.0);

        char buffer[100];
        std::snprintf(buffer, sizeof(buffer), "frames/frame_%04d.bmp", i);
        scene.Render(std::string(buffer));
    }
    */
}