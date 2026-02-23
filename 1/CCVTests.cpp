#include <iostream>
#include <limits>
#include <cmath>
#include "CComplexVector.h"
#include "CCVTests.h"

bool CCVTests::isEqual(double a, double b) {
    return std::abs(a - b) < 1e-12;
}

void CCVTests::TestSum() {
    double v1[] = {1,2,3,4,5,6,7,8};
    double v2[] = {3,2,3,4,5,1,7,8};
    CComplexVector0 vec0(v1, 8);
    CComplexVector0 vec1(v2, 8);

    CComplexVector0 result = vec0 + vec1;
    std::vector<std::pair<double, double>> raw = result.GetRaw();

    for(int i = 0; i < 4; i++) {
        if (!isEqual(raw[i].first, v1[2*i] + v2[2*i]) || !isEqual(raw[i].second, v1[2*i+1] + v2[2*i+1])) {
            std::cout << "Sum test not passed! : Need: " << v1[2*i] + v2[2*i] << " + " << v1[2*i+1] + v2[2*i+1] << "i, have: " << raw[2*i].first << " + " << raw[2*i].second << "i.\n";
            return;
        }
    }
    std::cout << "Sum test OK!\n";
}

void CCVTests::TestDif() {
    double v1[] = {1,2,3,4,5,6,7,8};
    double v2[] = {3,2,3,4,5,1,7,8};
    CComplexVector0 vec0(v1, 8);
    CComplexVector0 vec1(v2, 8);

    CComplexVector0 result = vec0 - vec1;
    std::vector<std::pair<double, double>> raw = result.GetRaw();
    
    for(int i = 0; i < 4; i++) {
        if (!isEqual(raw[i].first, v1[2*i] - v2[2*i]) || !isEqual(raw[i].second, v1[2*i+1] - v2[2*i+1])) {
            std::cout << "Dif test not passed! : Need: " << v1[2*i] - v2[2*i] << " + " << v1[2*i+1] - v2[2*i+1] << "i, have: " << raw[2*i].first << " + " << raw[2*i].second << "i.\n";
            return;
        }
    }
    std::cout << "Dif test OK!\n";
}

void CCVTests::TestDot() {
    double v1[] = {1,2,3,4,5,6,7,8};
    double v2[] = {3,2,3,4,5,1,7,8};
    CComplexVector0 vec0(v1, 8);
    CComplexVector0 vec1(v2, 8);

    ComplexNumber result = vec0.Dot(vec1);
    if(!isEqual(result.Re, 176.0) || !isEqual(result.Im, 29.0)) {
        std::cout << "Dot test not passed!: " << "have: " << "(" << result.Re << " + " << result.Im << "i)" << "\n";
        return;
    }
    std::cout << "Dot test OK!\n";
}

void CCVTests::RunTests() {
    TestSum();
    TestDif();
    TestDot();
}