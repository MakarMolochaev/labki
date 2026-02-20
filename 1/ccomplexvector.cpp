#include "CComplexVector.h"
#include <fstream>
#include <stdexcept>

// CComplexVector implementation
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

// CComplexVector0 implementation
CComplexVector0::CComplexVector0(const CComplexVector& other) 
    : CComplexVector(other) {}

CComplexVector0::CComplexVector0(const CComplexVector&& other) noexcept 
    : CComplexVector(other) {}

CComplexVector0::~CComplexVector0() = default;

CComplexVector0 CComplexVector0::operator+(CComplexVector0& other) const {
    if (data_.size() != other.data_.size()) {
        throw std::runtime_error("vectors must have same size");
    }

    CComplexVector0 result(data_.size());

    for (size_t i = 0; i < data_.size(); i++) {
        result.data_[i].first = data_[i].first + other.data_[i].first; 
        result.data_[i].second = data_[i].second + other.data_[i].second; 
    }

    return result;
}

CComplexVector0 CComplexVector0::operator-(CComplexVector0& other) const {
    if (data_.size() != other.data_.size()) {
        throw std::runtime_error("vectors must have same size");
    }

    CComplexVector0 result(data_.size());

    for (size_t i = 0; i < data_.size(); i++) {
        result.data_[i].first = data_[i].first - other.data_[i].first; 
        result.data_[i].second = data_[i].second - other.data_[i].second; 
    }

    return result;
}

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

// CComplexVector1 implementation
CComplexVector1::CComplexVector1(const CComplexVector& other) 
    : CComplexVector(other) {}

CComplexVector1::CComplexVector1(const CComplexVector&& other) noexcept 
    : CComplexVector(other) {}

CComplexVector1::~CComplexVector1() = default;

CComplexVector1 CComplexVector1::operator+(CComplexVector1& other) const {
    if (data_.size() != other.data_.size()) {
        throw std::runtime_error("vectors must have same size");
    }

    CComplexVector1 result(data_.size());

    for (size_t i = 0; i < data_.size(); i++) {
        result.data_[i].first = data_[i].first + other.data_[i].first; 
        result.data_[i].second = data_[i].second + other.data_[i].second; 
    }

    return result;
}

CComplexVector1 CComplexVector1::operator-(CComplexVector1& other) const {
    if (data_.size() != other.data_.size()) {
        throw std::runtime_error("vectors must have same size");
    }

    CComplexVector1 result(data_.size());

    for (size_t i = 0; i < data_.size(); i++) {
        result.data_[i].first = data_[i].first - other.data_[i].first; 
        result.data_[i].second = data_[i].second - other.data_[i].second; 
    }

    return result;
}

double CComplexVector1::Dot(const CComplexVector1& other) const {
    double result = 0;
    
    for (size_t i = 0; i < data_.size(); i++) {
        result += (data_[i].first * other.data_[i].first);
        result -= (data_[i].second * other.data_[i].second); 
    }

    return result;
}

void CComplexVector1::Output(std::string filename) const {
    std::ofstream file(filename, std::ios::out);
    for (auto p : data_) {
        file << "(" << p.first << " + " << p.second << "i)\n";
    }
    file.close();
}