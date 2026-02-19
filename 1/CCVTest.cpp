#include "CComplexVector.h"
#include <iostream>

void TestSum() {
    std::vector<double> v1 = {1,2,3,4,5,6,7,8};
    std::vector<double> v2 = {3,2,3,4,5,1,7,8};
    CComplexVector0 vec0(v1);
    CComplexVector0 vec1(v2);

    CComplexVector0 result = vec0 + vec1;
    std::vector<std::pair<double, double>> raw = result.GetRaw();

    for(int i = 0; i < 4; i++) {
        if (raw[i].first != v1[2*i] + v2[2*i] || raw[i].second != v1[2*i+1] + v2[2*i+1]) {
            std::cout << "Sum test not passed! : Need: " << v1[2*i] + v2[2*i] << " + " << v1[2*i+1] + v2[2*i+1] << "i, have: " << raw[2*i].first << " + " << raw[2*i].second << "i.\n";
            return;
        }
    }
    std::cout << "Sum test OK!\n";
}

void TestDif() {
    std::vector<double> v1 = {1,2,3,4,5,6,7,8};
    std::vector<double> v2 = {3,2,3,4,5,1,7,8};
    CComplexVector0 vec0(v1);
    CComplexVector0 vec1(v2);

    CComplexVector0 result = vec0 - vec1;
    std::vector<std::pair<double, double>> raw = result.GetRaw();

    for(int i = 0; i < 4; i++) {
        if (raw[i].first != v1[2*i] - v2[2*i] || raw[i].second != v1[2*i+1] - v2[2*i+1]) {
            std::cout << "Dif test not passed! : Need: " << v1[2*i] + v2[2*i] << " + " << v1[2*i+1] + v2[2*i+1] << "i, have: " << raw[2*i].first << " + " << raw[2*i].second << "i.\n";
            return;
        }
    }
    std::cout << "Dif test OK!\n";
}

void TestDot() {
    std::vector<double> v1 = {1,2,3,4,5,6,7,8};
    std::vector<double> v2 = {3,2,3,4,5,1,7,8};
    CComplexVector0 vec0(v1);
    CComplexVector0 vec1(v2);

    double result = vec0.Dot(vec1);
    if(result != -4) {
        std::cout << "Dot test not passed!\n";
    }
    std::cout << "Dot test OK!\n";
}

void RunTests() {
    TestSum();
    TestDot();
    TestDif();
}