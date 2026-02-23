#include <fstream>
#include <memory>
#include <stdexcept>
#include "CComplexVector.h"

CComplexVector::CComplexVector(size_t size) {
    data_.resize(size);
}

CComplexVector::CComplexVector(size_t size, double fill) {
    data_ = std::vector<ComplexNumber>(size, ComplexNumber(fill, fill));
}

CComplexVector::CComplexVector() = default;

CComplexVector::CComplexVector(const std::vector<double>& data) {
    if (data.size() % 2 != 0) {
        throw std::runtime_error("wrong size");
    }
    data_.resize(data.size() / 2);
    for (size_t i = 0; i < data.size() / 2; i++) {
        data_[i] = ComplexNumber(data[2 * i], data[2 * i + 1]);
    }
}

CComplexVector::CComplexVector(const std::vector<double>& data, const std::string filename) : filename_(filename) {
    if (data.size() % 2 != 0) {
        throw std::runtime_error("wrong size");
    }
    data_.resize(data.size() / 2);
    for (size_t i = 0; i < data.size() / 2; i++) {
        data_[i] = ComplexNumber(data[2 * i], data[2 * i + 1]);
    }
}

CComplexVector::CComplexVector(const CComplexVector& other) : data_(other.data_), filename_(other.filename_) {}

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
    for(size_t i = 0; i < data_.size(); i++) {
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
    ComplexNumber result(0.0, 0.0);
    
    for (size_t i = 0; i < data_.size(); i++) {
        result.Re += (data_[i].Re * other.data_[i].Re) + (data_[i].Im * other.data_[i].Im);
        result.Im += (data_[i].Im * other.data_[i].Re) - (data_[i].Re * other.data_[i].Im);
    }

    return result;
}
#include <iostream>

void CComplexVector::AddManyWithOpenMP(const std::vector<std::unique_ptr<CComplexVector>>& vectors) {
    if(vectors.size() == 0) {
        return;
    }

    size_t m = data_.size();
    for(const auto& v : vectors) {
        if(!v || v->data_.size() != m) {
            throw std::runtime_error("vectors must be equal size.");
        }
    }

    #pragma omp parallel for simd
    for (size_t i = 0; i < m; ++i) {
        double re = 0.0;
        double im = 0.0;
    
        for (size_t k = 0; k < vectors.size(); ++k) {
            re += vectors[k]->data_[i].Re;
            im += vectors[k]->data_[i].Im;
        }
    
        data_[i].Re += re;
        data_[i].Im += im;
    }
}

void CComplexVector::AddMany(const std::vector<std::unique_ptr<CComplexVector>>& vectors) {
    if(vectors.size() == 0) {
        return;
    }

    size_t m = data_.size();
    for(const auto& v : vectors) {
        if(!v || v->data_.size() != m) {
            throw std::runtime_error("vectors must be equal size.");
        }
    }

    for (size_t i = 0; i < m; ++i) {
        double re = 0.0;
        double im = 0.0;
    
        for (size_t k = 0; k < vectors.size(); ++k) {
            re += vectors[k]->data_[i].Re;
            im += vectors[k]->data_[i].Im;
        }
    
        data_[i].Re += re;
        data_[i].Im += im;
    }
}