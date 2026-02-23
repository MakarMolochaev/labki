#pragma once


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
    size_t size_ = 0;
    ComplexNumber* data_ = nullptr;
    char* filename_ = nullptr;

public:
    CComplexVector(size_t size);
    CComplexVector();
    CComplexVector(const double* data, const size_t count);
    CComplexVector(const double* data, const size_t count, const char* filename);
    CComplexVector(const CComplexVector& other);
    CComplexVector(CComplexVector&& other) noexcept;
    
    CComplexVector& operator=(const CComplexVector& other);
    CComplexVector& operator=(CComplexVector&& other) noexcept;
    
    double* GetRaw() const;

    virtual ~CComplexVector();

    friend CComplexVector0 operator+(const CComplexVector& left, const CComplexVector& right);
    friend CComplexVector0 operator-(const CComplexVector& left, const CComplexVector& right);
    
    virtual void Output(const char* filename = "") const = 0;
    ComplexNumber Dot(const CComplexVector& other) const;
};

// row output
class CComplexVector0 : public CComplexVector {
public:
    using CComplexVector::CComplexVector;
    
    CComplexVector0(const CComplexVector& other);
    CComplexVector0(const CComplexVector&& other) noexcept;

    void Output(const char* filename = "") const override;
};

// column output
class CComplexVector1 : public CComplexVector {
public:
    using CComplexVector::CComplexVector;
    
    CComplexVector1(const CComplexVector& other);
    CComplexVector1(const CComplexVector&& other) noexcept;
    
    void Output(const char* filename = "") const override;
};