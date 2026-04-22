#include <fstream>
#include <iostream>
#include "PointLight.h"

void PointLight::FillWithValues(std::ifstream& inputStream) {
    std::string cmd = "";

    while(cmd != "}") {
        if (cmd == "position:") {
            inputStream >> cmd;
            this->position.X = std::stod(cmd);
            inputStream >> cmd;
            this->position.Y = std::stod(cmd);
            inputStream >> cmd;
            this->position.Z = std::stod(cmd);
            continue;
        } else if (cmd == "color:") {
            inputStream >> cmd;
            this->color.R = std::stod(cmd) / 255.0;
            inputStream >> cmd;
            this->color.G = std::stod(cmd) / 255.0;
            inputStream >> cmd;
            this->color.B = std::stod(cmd) / 255.0;
            continue;
        } else if (cmd == "intensity:") {
            inputStream >> cmd;
            this->intensity = std::stod(cmd);
            continue;
        }
        inputStream >> cmd;
    }
}