#include <fstream>
#include <stdexcept>
#include "CComplexVector.h"

CComplexVector0::CComplexVector0(const CComplexVector& other) 
    : CComplexVector(other) {}

CComplexVector0::CComplexVector0(const CComplexVector&& other) noexcept 
    : CComplexVector(other) {}

CComplexVector0::~CComplexVector0() = default;

double CComplexVector0::Dot(const CComplexVector0& other) const {
    double result = 0;
    
    for (size_t i = 0; i < data_.size(); i++) {
        result += (data_[i].first * other.data_[i].first);
        result -= (data_[i].second * other.data_[i].second); 
    }

    return result;
}

void CComplexVector0::Output(std::string filename) const {
    std::ofstream file(filename, std::ios::out);
    for (size_t i = 0; i < data_.size(); i++) {
        file << "(" << data_[i].first << " + " << data_[i].second << "i)";
        if (i < data_.size() - 1) {
            file << ", ";
        }
    }
    file.close();
}