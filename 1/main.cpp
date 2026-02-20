#include <iostream>
#include <fstream>
#include <sstream>
#include "CComplexVector.h"
#include "CCVTests.h"
#include "CComplexVectorFactory.cpp"

void LoadFromFile(std::string filename) {
    CComplexVectorFactory factory;
    factory.registerType<CComplexVector0>("0");
    factory.registerType<CComplexVector1>("1");


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
        auto vec = factory.create("0", arr);
        if (!vec) {
            std::cerr << "Unknown vector type: " << index << "\n";
            continue;
        }
        vec->Output(fn);
    }
}

int main() {
    CCVTests tests;
    tests.RunTests();

    LoadFromFile("classes.txt");

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