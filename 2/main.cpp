#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <cstring>
#include <chrono>
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
    } else if(argc > 1 && strcmp(argv[1], "--OMPtest") == 0) {
        size_t COUNT = 1000;
        for(size_t N = 10; N < 10000000; N*=10) {
            CComplexVector0 vec0(N);
            std::vector<std::unique_ptr<CComplexVector>> vecs;
            for(int i = 0; i < COUNT; i++) {
                auto v = std::make_unique<CComplexVector0>(N, 1);
                vecs.push_back(std::move(v));
            }
            auto t0 = std::chrono::steady_clock::now();
            vec0.AddManyWithOpenMP(vecs);
            auto t1 = std::chrono::steady_clock::now();

            double time1 = std::chrono::duration<double, std::milli>(t1-t0).count();

            CComplexVector0 vec1(N);

            t0 = std::chrono::steady_clock::now();
            vec1.AddMany(vecs);
            t1 = std::chrono::steady_clock::now();

            double time2 = std::chrono::duration<double, std::milli>(t1-t0).count();

            std::printf("%dx%d with OMP: %.3fms, without OMP: %.3fms\n", COUNT, N, time1, time2);
        }
        return 0;
    }
    
    
    std::vector<std::unique_ptr<CComplexVector>> objects;

    LoadFromFile("classes.txt", objects);

    for(int i = 0; i < objects.size(); i++) {
        objects[i]->Output();
    }
}