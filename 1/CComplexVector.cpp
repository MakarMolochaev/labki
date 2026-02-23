#include <fstream>
#include <stdexcept>
#include <cstring>
#include <iostream>
#include "CComplexVector.h"

CComplexVector::CComplexVector(size_t size) {
    size_ = size;
    data_ = new ComplexNumber[size];
}

CComplexVector::CComplexVector() = default;

CComplexVector::CComplexVector(const double* data, const size_t count) {
    if (count % 2 != 0) {
        throw std::runtime_error("wrong size");
    }
    size_ = count / 2;
    data_ = new ComplexNumber[size_];
    for (size_t i = 0; i < count; i += 2) {
        data_[i / 2].Re = data[i];
        data_[i / 2].Im = data[i+1];
    }
}

char* Strdup(const char* s) {
    if (!s) return nullptr;
    char* p = new char[std::strlen(s) + 1];
    std::strcpy(p, s);
    return p;
}

CComplexVector::CComplexVector(const double* data, size_t count, const char* filename) {
    if (count % 2 != 0) {
        throw std::runtime_error("wrong size");
    }
    filename_ = Strdup(filename);
    size_ = count / 2;
    data_ = new ComplexNumber[size_];
    for (size_t i = 0; i < size_; i++) {
        data_[i].Re = data[2 * i];
        data_[i].Im = data[2 * i + 1];
    }
}

CComplexVector::CComplexVector(const CComplexVector& other) {
    size_ = other.size_;
    filename_ = Strdup(other.filename_);
    data_ = new ComplexNumber[size_];
    for (size_t i = 0; i < size_; i++) {
        data_[i].Re = other.data_[i].Re;
        data_[i].Im = other.data_[i].Im;
    }
}

CComplexVector::CComplexVector(CComplexVector&& other) noexcept : size_(other.size_) , data_(other.data_), filename_(other.filename_) {
    other.size_ = 0;
    other.data_ = nullptr;
    other.filename_ = nullptr;
}

CComplexVector& CComplexVector::operator=(const CComplexVector& other) {
    if (this == &other) {
        return *this;
    }
    delete [] data_;
    delete [] filename_;
    size_ = other.size_;
    filename_ = Strdup(other.filename_);
    data_ = new ComplexNumber[size_];
    for (size_t i = 0; i < size_; i++) {
        data_[i].Re = other.data_[i].Re;
        data_[i].Im = other.data_[i].Im;
    }
    return *this;
}

CComplexVector& CComplexVector::operator=(CComplexVector&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    delete [] data_;
    delete [] filename_;
    size_ = other.size_;
    data_ = other.data_;
    filename_ = other.filename_;

    other.size_ = 0;
    other.data_ = nullptr;
    other.filename_ = nullptr;

    return *this;
}

CComplexVector::~CComplexVector() {
    delete [] data_;
    delete [] filename_;
}

double* CComplexVector::GetRaw() const {
    double* result = new double[size_ * 2];
    for(int i = 0; i < size_; i++) {
        result[2 * i] = data_[i].Re;
        result[2 * i + 1] = data_[i].Im;
    }
    return result;
}

CComplexVector0 operator+(const CComplexVector& left, const CComplexVector& right) {
    if (left.size_ != right.size_) {
        throw std::runtime_error("vectors must have same size");
    }

    CComplexVector0 result(left.size_);

    for (size_t i = 0; i < left.size_; i++) {
        result.data_[i].Re = left.data_[i].Re + right.data_[i].Re; 
        result.data_[i].Im = left.data_[i].Im + right.data_[i].Im; 
    }

    return result;
}

CComplexVector0 operator-(const CComplexVector& left, const CComplexVector& right) {
    if (left.size_ != right.size_) {
        throw std::runtime_error("vectors must have same size");
    }

    CComplexVector0 result(left.size_);

    for (size_t i = 0; i < left.size_; i++) {
        result.data_[i].Re = left.data_[i].Re - right.data_[i].Re; 
        result.data_[i].Im = left.data_[i].Im - right.data_[i].Im; 
    }

    return result;
}

ComplexNumber CComplexVector::Dot(const CComplexVector& other) const {
    ComplexNumber result(0, 0);
    
    for (size_t i = 0; i < size_; i++) {
        result.Re += (data_[i].Re * other.data_[i].Re) + (data_[i].Im * other.data_[i].Im);
        result.Im += (data_[i].Im * other.data_[i].Re) - (data_[i].Re * other.data_[i].Im);
    }

    return result;
}