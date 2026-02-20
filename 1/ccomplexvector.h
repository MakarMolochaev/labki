#pragma once

#include <string>
#include <vector>

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
    
    virtual void Output(std::string filename) const = 0;
};

// row output
class CComplexVector0 : public CComplexVector {
public:
    using CComplexVector::CComplexVector;
    
    CComplexVector0(const CComplexVector& other);
    CComplexVector0(const CComplexVector&& other) noexcept;
    
    ~CComplexVector0() override;
    
    CComplexVector0 operator+(CComplexVector0& other) const;
    CComplexVector0 operator-(CComplexVector0& other) const;
    double Dot(const CComplexVector0& other) const;
    void Output(std::string filename) const override;
};

// column output
class CComplexVector1 : public CComplexVector {
public:
    using CComplexVector::CComplexVector;
    
    CComplexVector1(const CComplexVector& other);
    CComplexVector1(const CComplexVector&& other) noexcept;
    
    ~CComplexVector1() override;
    
    CComplexVector1 operator+(CComplexVector1& other) const;
    CComplexVector1 operator-(CComplexVector1& other) const;
    double Dot(const CComplexVector1& other) const;
    void Output(std::string filename) const override;
};