#include <fstream>
#include <stdexcept>
#include "CComplexVector.h"

CComplexVector1::CComplexVector1(const CComplexVector& other) 
    : CComplexVector(other) {}

CComplexVector1::CComplexVector1(const CComplexVector&& other) noexcept 
    : CComplexVector(other) {}

void CComplexVector1::Output(const char* filename) const {
    const char* out_name = filename && filename[0] != '\0' ? filename  : filename_;
    std::ofstream file(out_name, std::ios::out);
    for (size_t i = 0; i < size_; i++) {
        file << "(" << data_[i].Re << " + " << data_[i].Im << "i)\n";
    }
    file.close();
}