#include <fstream>
#include <iostream>
#include "Material.h"

void Material::FillWithValues(std::ifstream& inputStream) {
    std::string cmd = "";

    while(cmd != "}") {
        if (cmd == "diffuseColor:") {
            inputStream >> cmd;
            this->diffuseColor.R = std::stod(cmd) / 255.0;
            inputStream >> cmd;
            this->diffuseColor.G = std::stod(cmd) / 255.0;
            inputStream >> cmd;
            this->diffuseColor.B = std::stod(cmd) / 255.0;
            continue;
        } else if (cmd == "specularColor:") {
            inputStream >> cmd;
            this->specularColor.R = std::stod(cmd) / 255.0;
            inputStream >> cmd;
            this->specularColor.G = std::stod(cmd) / 255.0;
            inputStream >> cmd;
            this->specularColor.B = std::stod(cmd) / 255.0;
            continue;
        } else if (cmd == "glossy:") {
            inputStream >> cmd;
            this->glossy = std::stod(cmd);
            continue;
        } else if (cmd == "reflectFactor:") {
            inputStream >> cmd;
            this->reflectFactor = std::stod(cmd);
            continue;
        }
        inputStream >> cmd;
    }
}