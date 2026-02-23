#include <iostream>
#include <limits>
#include <cmath>
#include "CComplexVector.h"
#include "CCVTests.h"

bool CCVTests::isEqual(double a, double b) {
    return std::abs(a - b) < 1e-12;
}

void CCVTests::TestSum() {
    std::vector<double> v1 = {1,2,3,4,5,6,7,8};
    std::vector<double> v2 = {3,2,3,4,5,1,7,8};
    CComplexVector0 vec0(v1);
    CComplexVector0 vec1(v2);

    CComplexVector0 result = vec0 + vec1;
    std::vector<double> raw = result.GetRaw();

    for(int i = 0; i < 8; i++) {
        if (!isEqual(raw[i], v1[i] + v2[i])) {
            std::cout << "Sum test not passed! : Need: " << v1[i] + v2[i] << ((i % 2 == 0) ? "" : "i") << ", have: " << raw[i] << ((i % 2 == 0) ? "" : "i") << ".\n";
            return;
        }
    }
    std::cout << "Sum test OK!\n";
}

void CCVTests::TestDif() {
    std::vector<double> v1 = {1,2,3,4,5,6,7,8};
    std::vector<double> v2 = {3,2,3,4,5,1,7,8};
    CComplexVector0 vec0(v1);
    CComplexVector0 vec1(v2);

    CComplexVector0 result = vec0 - vec1;
    std::vector<double> raw = result.GetRaw();

    for(int i = 0; i < 8; i++) {
        if (!isEqual(raw[i], v1[i] - v2[i])) {
            std::cout << "Dif test not passed! : Need: " << v1[i] - v2[i] << ((i % 2 == 0) ? "" : "i") << ", have: " << raw[i] << ((i % 2 == 0) ? "" : "i") << ".\n";
            return;
        }
    }
    std::cout << "Dif test OK!\n";
}

void CCVTests::TestDot() {
    std::vector<double> v1 = {1,2,3,4,5,6,7,8};
    std::vector<double> v2 = {3,2,3,4,5,1,7,8};
    CComplexVector0 vec0(v1);
    CComplexVector0 vec1(v2);

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