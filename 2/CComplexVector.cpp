#include <fstream>
#include <stdexcept>
#include "CComplexVector.h"

CComplexVector::CComplexVector(size_t size) {
    data_ = std::vector<ComplexNumber>(size);
}

CComplexVector::CComplexVector() = default;

CComplexVector::CComplexVector(const std::vector<double>& data) {
    if (data.size() % 2 != 0) {
        throw std::runtime_error("wrong size");
    }
    for (size_t i = 0; i < data.size(); i += 2) {
        data_.push_back(ComplexNumber(data[i], data[i+1]));
    }
}

CComplexVector::CComplexVector(const std::vector<double>& data, const std::string filename) : filename_(filename) {
    if (data.size() % 2 != 0) {
        throw std::runtime_error("wrong size");
    }
    for (size_t i = 0; i < data.size(); i += 2) {
        data_.push_back(ComplexNumber(data[i], data[i+1]));
    }
}

CComplexVector::CComplexVector(const CComplexVector& other) {
    for (auto p : other.data_) {
        data_.push_back(ComplexNumber(p.Re, p.Im));
    }
}

CComplexVector::CComplexVector(CComplexVector&& other) noexcept 
    : data_(std::move(other.data_)), filename_(std::move(other.filename_)) {}

CComplexVector& CComplexVector::operator=(const CComplexVector& other) {
    if (this != &other) {
        data_ = other.data_;
        filename_ = other.filename_;
    }
    return *this;
}

CComplexVector& CComplexVector::operator=(CComplexVector&& other) noexcept {
    if (this != &other) {
        data_ = std::move(other.data_);
        filename_ = std::move(other.filename_);
    }
    return *this;
}

std::vector<double> CComplexVector::GetRaw() const {
    std::vector<double> raw(data_.size() * 2);
    for(int i = 0; i < data_.size(); i++) {
        raw[2 * i] = data_[i].Re;
        raw[2 * i + 1] = data_[i].Im;
    }
    return raw;
}

CComplexVector0 operator+(const CComplexVector& left, const CComplexVector& right) {
    if (left.data_.size() != right.data_.size()) {
        throw std::runtime_error("vectors must have same size");
    }

    CComplexVector0 result(left.data_.size());

    for (size_t i = 0; i < left.data_.size(); i++) {
        result.data_[i].Re = left.data_[i].Re + right.data_[i].Re; 
        result.data_[i].Im = left.data_[i].Im + right.data_[i].Im; 
    }

    return result;
}

CComplexVector0 operator-(const CComplexVector& left, const CComplexVector& right) {
    if (left.data_.size() != right.data_.size()) {
        throw std::runtime_error("vectors must have same size");
    }

    CComplexVector0 result(left.data_.size());

    for (size_t i = 0; i < left.data_.size(); i++) {
        result.data_[i].Re = left.data_[i].Re - right.data_[i].Re; 
        result.data_[i].Im = left.data_[i].Im - right.data_[i].Im; 
    }

    return result;
}

ComplexNumber CComplexVector::Dot(const CComplexVector& other) const {
    ComplexNumber result;
    
    for (size_t i = 0; i < data_.size(); i++) {
        result.Re += (data_[i].Re * other.data_[i].Re) + (data_[i].Im * other.data_[i].Im);
        result.Im += (data_[i].Im * other.data_[i].Re) - (data_[i].Re * other.data_[i].Im);
    }

    return result;
}