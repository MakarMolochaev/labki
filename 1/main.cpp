#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <cstring>
#include "CComplexVector.h"
#include "CCVTests.h"
#include "CCVFactory.h"
#include "EasyCCVFactory.h"

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

size_t EasyLoadFromFile(std::string filename, CComplexVector**& objects) {
    size_t cap = 8;
    size_t I = 0;
    objects = new CComplexVector*[cap];

    EasyCCVFactory factory;

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
        CComplexVector* vec = factory.Create(std::to_string(index).c_str(), arr, fn);
        if (!vec) {
            std::cerr << "Unknown vector type: " << index << "\n";
            continue;
        }
        if(I >= cap) {
            cap *= 2;
            CComplexVector** new_objects = new CComplexVector*[cap];
            for(size_t i = 0; i < I; i++) {
                new_objects[i] = objects[i];
            }
            delete [] objects;
            objects = new_objects;
        }
        objects[I] = vec;
        I++;
    }
    return I;
}

int main(int argc, char** argv) {
    if(argc > 1 && strcmp(argv[1], "--test") == 0) {
        CCVTests tests;
        tests.RunTests();
    }

    std::cout << "\n";

    // with easy factory

    CComplexVector** objects;

    size_t count = EasyLoadFromFile("classes.txt", objects);

    for(int i = 0; i < count; i++) {
        objects[i]->Output();
    }

    for (int i = 0; i < count; i++) {
        delete objects[i];
        objects[i] = nullptr;
    }

    /*
    std::vector<std::unique_ptr<CComplexVector>> objects;

    LoadFromFile("classes.txt", objects);

    for(int i = 0; i < objects.size(); i++) {
        objects[i]->Output();
    }
    */
    CComplexVector0 vec0({1,2,3,4,5,6});
    CComplexVector0 vec22({1,1,1,1,1,1});
    CComplexVector0 vec67({6,7,6,7,6,7});
    CComplexVector1 vec1({5,2,7,6,7,1});

    //vec0.Output("test0.txt");
    //vec1.Output("test1.txt");

    //CComplexVector0 vec30(vec0);
    //CComplexVector1 vec31(vec0);
    //vec30.Output("a0.txt");
    //vec31.Output("a1.txt");
    //vec3.Output("test3.txt");
    //(vec0 + vec67).Output("test67.txt");
    //std::cout << vec0.Dot(vec22);
    return 0;
}