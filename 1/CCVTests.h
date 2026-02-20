#pragma once

#include <iostream>
#include <limits>
#include <cmath>
#include "CComplexVector.h"

class CCVTests {
private:
    bool isEqual(double a, double b);

public:
    void TestSum();

    void TestDif();

    void TestDot();

    void RunTests();
};