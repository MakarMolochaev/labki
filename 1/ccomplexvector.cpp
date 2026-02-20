#include <fstream>
#include <stdexcept>
#include "CComplexVector.h"

CComplexVector::CComplexVector(size_t size) {
    data_ = std::vector<std::pair<double, double>>(size);
}

CComplexVector::CComplexVector() = default;

CComplexVector::CComplexVector(const std::vector<double>& data) {
    if (data.size() % 2 != 0) {
        throw std::runtime_error("wrong size");
    }
    for (size_t i = 0; i < data.size(); i += 2) {
        data_.push_back(std::pair<double,double>(data[i], data[i+1]));
    }
}

CComplexVector::CComplexVector(const CComplexVector& other) {
    for (auto p : other.data_) {
        data_.push_back(std::pair<double,double>(p.first, p.second));
    }
}

CComplexVector::CComplexVector(const CComplexVector&& other) noexcept 
    : data_(std::move(other.data_)) {}

CComplexVector& CComplexVector::operator=(const CComplexVector& other) {
    if (this != &other) {
        data_ = other.data_;
    }
    return *this;
}

CComplexVector& CComplexVector::operator=(CComplexVector&& other) noexcept {
    if (this != &other) {
        data_ = std::move(other.data_);
    }
    return *this;
}

std::vector<std::pair<double, double>> CComplexVector::GetRaw() const {
    return data_;
}

CComplexVector0 operator+(const CComplexVector& left, const CComplexVector& right) {
    if (left.data_.size() != right.data_.size()) {
        throw std::runtime_error("vectors must have same size");
    }

    CComplexVector0 result(left.data_.size());

    for (size_t i = 0; i < left.data_.size(); i++) {
        result.data_[i].first = left.data_[i].first + right.data_[i].first; 
        result.data_[i].second = left.data_[i].second + right.data_[i].second; 
    }

    return result;
}

CComplexVector0 operator-(const CComplexVector& left, const CComplexVector& right) {
    if (left.data_.size() != right.data_.size()) {
        throw std::runtime_error("vectors must have same size");
    }

    CComplexVector0 result(left.data_.size());

    for (size_t i = 0; i < left.data_.size(); i++) {
        result.data_[i].first = left.data_[i].first - right.data_[i].first; 
        result.data_[i].second = left.data_[i].second - right.data_[i].second; 
    }

    return result;
}