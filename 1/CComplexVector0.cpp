#include <fstream>
#include <stdexcept>
#include <iostream>
#include "CComplexVector.h"

CComplexVector0::CComplexVector0(const CComplexVector& other) 
    : CComplexVector(other) {}

CComplexVector0::CComplexVector0(const CComplexVector&& other) noexcept 
    : CComplexVector(other) {}

void CComplexVector0::Output(const char* filename) const {
    const char* out_name = filename && filename[0] != '\0' ? filename  : filename_;
    std::ofstream file(out_name, std::ios::out);
    for (size_t i = 0; i < size_; i++) {
        file << "(" << data_[i].Re << " + " << data_[i].Im << "i)";
        if (i < size_ - 1) {
            file << ", ";
        }
    }
    file.close();
}