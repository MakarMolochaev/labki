#pragma once

#include <string>
#include <vector>

class CComplexVector0;
class CComplexVector1;

class CComplexVector {
protected:
    std::vector<std::pair<double, double>> data_;

public:
    CComplexVector(size_t size);
    CComplexVector();
    CComplexVector(const std::vector<double>& data);
    CComplexVector(const CComplexVector& other);
    CComplexVector(const CComplexVector&& other) noexcept;
    
    CComplexVector& operator=(const CComplexVector& other);
    CComplexVector& operator=(CComplexVector&& other) noexcept;
    
    std::vector<std::pair<double, double>> GetRaw() const;

    virtual ~CComplexVector() = default;

    friend CComplexVector0 operator+(const CComplexVector& left, const CComplexVector& right);
    friend CComplexVector0 operator-(const CComplexVector& left, const CComplexVector& right);
    
    virtual void Output(std::string filename) const = 0;
    double Dot(const CComplexVector& other) const;
};

// row output
class CComplexVector0 : public CComplexVector {
public:
    using CComplexVector::CComplexVector;
    
    CComplexVector0(const CComplexVector& other);
    CComplexVector0(const CComplexVector&& other) noexcept;

    void Output(std::string filename) const override;
};

// column output
class CComplexVector1 : public CComplexVector {
public:
    using CComplexVector::CComplexVector;
    
    CComplexVector1(const CComplexVector& other);
    CComplexVector1(const CComplexVector&& other) noexcept;
    
    void Output(std::string filename) const override;
};