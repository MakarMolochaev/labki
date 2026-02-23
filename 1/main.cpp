#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <cstring>
#include "CComplexVector.h"
#include "CCVTests.h"
#include "EasyCCVFactory.h"

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

        double* arr = new double[4];
        size_t cap = 4;
        size_t count = 0;
        double a, b;
        while(iss >> a >> b) {
            if(count == cap) {
                double* new_arr = new double[cap * 2];
                for(int i = 0; i < count; i++) {
                    new_arr[i] = arr[i];
                }
                cap *= 2;
                delete [] arr;
                arr = new_arr;
            }
            arr[count] = a;
            arr[count + 1] = b;
            count += 2;
        }
        CComplexVector* vec = factory.Create(std::to_string(index).c_str(), arr, count, fn);
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
    
    return 0;
}