#include <fstream>
#include <stdexcept>
#include "CComplexVector.h"

CComplexVector1::CComplexVector1(const CComplexVector& other) 
    : CComplexVector(other) {}

CComplexVector1::CComplexVector1(const CComplexVector&& other) noexcept 
    : CComplexVector(other) {}

void CComplexVector1::Output(std::string filename) const {
    if(filename == "") {
        filename = filename_;
    }
    std::ofstream file(filename, std::ios::out);
    for (auto p : data_) {
        file << "(" << p.first << " + " << p.second << "i)\n";
    }
    file.close();
}