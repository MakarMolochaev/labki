#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <cstring>
#include "CComplexVector.h"
#include "CCVTests.h"
#include "CCVFactory.h"

void LoadFromFile(std::string filename, std::vector<std::unique_ptr<CComplexVector>>& objects) {
    CComplexVectorFactory factory;
    factory.RegisterType<CComplexVector0>("0");
    factory.RegisterType<CComplexVector1>("1");

    std::ifstream file(filename);
    std::string line;

    int index;
    std::string fn;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        iss >> index >> fn;

        std::vector<double> arr;
        double a, b;
        while(iss >> a >> b) {
            arr.push_back(a);
            arr.push_back(b);
        }
        auto vec = factory.Create(std::to_string(index), arr, fn);
        if (!vec) {
            std::cerr << "Unknown vector type: " << index << "\n";
            continue;
        }
        objects.push_back(std::move(vec));
    }
}

int main(int argc, char** argv) {
    std::cout << "\n";
    if(argc > 1 && strcmp(argv[1], "--test") == 0) {
        CCVTests tests;
        tests.RunTests();
        return 0;
    }

    std::vector<std::unique_ptr<CComplexVector>> objects;

    LoadFromFile("classes.txt", objects);

    for(int i = 0; i < objects.size(); i++) {
        objects[i]->Output();
    }
    
    return 0;
}