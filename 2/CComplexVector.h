#pragma once

#include <string>
#include <vector>
#include <memory>

class CComplexVector0;
class CComplexVector1;

struct ComplexNumber {
public:
    double Re = 0, Im = 0;
    ComplexNumber(double re, double im) : Re(re), Im(im) {}
    ComplexNumber() : Re(0), Im(0) {}
};

class CComplexVector {
protected:
    std::vector<ComplexNumber> data_;
    std::string filename_;

public:
    CComplexVector(size_t size);
    CComplexVector(size_t size, double fill);
    CComplexVector();
    CComplexVector(const std::vector<double>& data);
    CComplexVector(const std::vector<double>& data, const std::string filename);
    CComplexVector(const CComplexVector& other);
    CComplexVector(CComplexVector&& other) noexcept;
    
    CComplexVector& operator=(const CComplexVector& other);
    CComplexVector& operator=(CComplexVector&& other) noexcept;
    
    std::vector<double> GetRaw() const;

    virtual ~CComplexVector() = default;

    friend CComplexVector0 operator+(const CComplexVector& left, const CComplexVector& right);
    friend CComplexVector0 operator-(const CComplexVector& left, const CComplexVector& right);
    
    virtual void Output(std::string filename = "") const = 0;
    ComplexNumber Dot(const CComplexVector& other) const;

    void AddMany(const std::vector<std::unique_ptr<CComplexVector>>& vectors);
    void AddManyWithOpenMP(const std::vector<std::unique_ptr<CComplexVector>>& vectors);
};

// row output
class CComplexVector0 : public CComplexVector {
public:
    using CComplexVector::CComplexVector;
    
    CComplexVector0(const CComplexVector& other);
    CComplexVector0(const CComplexVector&& other) noexcept;

    void Output(std::string filename = "") const override;
};

// column output
class CComplexVector1 : public CComplexVector {
public:
    using CComplexVector::CComplexVector;
    
    CComplexVector1(const CComplexVector& other);
    CComplexVector1(const CComplexVector&& other) noexcept;
    
    void Output(std::string filename = "") const override;
};