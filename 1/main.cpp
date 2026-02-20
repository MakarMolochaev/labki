#include <iostream>
#include <fstream>
#include <sstream>
#include "CComplexVector.h"
#include "CCVTests.h"

void LoadFromFile(std::string filename) {
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
        if (index == 0) {
            CComplexVector0 vec(arr);
            vec.Output(fn);
        } else if (index == 1) {
            CComplexVector1 vec(arr);
            vec.Output(fn);
        }
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

    CComplexVector1 vec3(vec0);
    //vec3.Output("test3.txt");
    //(vec0 + vec67).Output("test67.txt");
    //std::cout << vec0.Dot(vec22);
    return 0;
}