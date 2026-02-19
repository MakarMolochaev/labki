#include <string>
#include <fstream>
#include <vector>

class CComplexVector {
protected:
    std::vector<std::pair<double, double>> data_;
public:
    CComplexVector(size_t size) {
        data_ = std::vector<std::pair<double, double>>(size);
    }

    CComplexVector() = default;

    CComplexVector(const std::vector<double>& data) {
        if (data.size() % 2 != 0) {
            throw std::runtime_error("wrong size");
        }
        for (int i = 0; i < data.size(); i += 2) {
            data_.push_back(std::pair<double,double>(data[i], data[i+1]));
        }
    }

    CComplexVector(const CComplexVector& other) {
        for (auto p : other.data_) {
            data_.push_back(std::pair<double,double>(p.first, p.second));
        }
    }

    CComplexVector(const CComplexVector&& other) noexcept : data_(std::move(other.data_)) {}

    CComplexVector& operator=(const CComplexVector& other) {
        if (this != &other) {
            data_ = other.data_;
        }
        return *this;
    }

    CComplexVector& operator=(CComplexVector&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
        }
        return *this;
    }

    virtual ~CComplexVector() = default;

    const virtual void Output(std::string filename) = 0;
};

// row output
class CComplexVector0 : public CComplexVector {
public:
    using CComplexVector::CComplexVector;

    CComplexVector0(const CComplexVector& other) : CComplexVector(other){}
    CComplexVector0(const CComplexVector&& other) noexcept : CComplexVector(other){}
    
    ~CComplexVector0() override = default;

    CComplexVector0 operator+(CComplexVector0& other) const {
        if (data_.size() != other.data_.size()) {
            throw std::runtime_error("vectors must have same size");
        }

        CComplexVector0 result(data_.size());

        for (int i = 0; i < data_.size(); i++) {
            result.data_[i].first = data_[i].first + other.data_[i].first; 
            result.data_[i].second = data_[i].second + other.data_[i].second; 
        }

        return result;
    }

    CComplexVector0 operator-(CComplexVector0& other) const {
        if (data_.size() != other.data_.size()) {
            throw std::runtime_error("vectors must have same size");
        }

        CComplexVector0 result(data_.size());

        for (int i = 0; i < data_.size(); i++) {
            result.data_[i].first = data_[i].first - other.data_[i].first; 
            result.data_[i].second = data_[i].second - other.data_[i].second; 
        }

        return result;
    }

    double Dot(const CComplexVector0& other) const {
        double result = 0;
        
        for (int i = 0; i < data_.size(); i++) {
            result += (data_[i].first * other.data_[i].first);
            result -= (data_[i].second * other.data_[i].second); 
        }

        return result;
    }
    
    const void Output(std::string filename) override {
        std::ofstream file(filename, std::ios::out);
        for (int i = 0; i < data_.size(); i++) {
            file << "(" << data_[i].first << " + " << data_[i].second << "i)";
            if (i < data_.size() - 1) {
                file << ", ";
            }
        }
        file.close();
    }
};

// column output
class CComplexVector1 : public CComplexVector {
public:
    using CComplexVector::CComplexVector;

    CComplexVector1(const CComplexVector& other) : CComplexVector(other){}
    CComplexVector1(const CComplexVector&& other) noexcept : CComplexVector(other){}

    ~CComplexVector1() override = default;

    CComplexVector1 operator+(CComplexVector1& other) const {
        if (data_.size() != other.data_.size()) {
            throw std::runtime_error("vectors must have same size");
        }

        CComplexVector1 result(data_.size());

        for (int i = 0; i < data_.size(); i++) {
            result.data_[i].first = data_[i].first + other.data_[i].first; 
            result.data_[i].second = data_[i].second + other.data_[i].second; 
        }

        return result;
    }

    CComplexVector1 operator-(CComplexVector1& other) const {
        if (data_.size() != other.data_.size()) {
            throw std::runtime_error("vectors must have same size");
        }

        CComplexVector1 result(data_.size());

        for (int i = 0; i < data_.size(); i++) {
            result.data_[i].first = data_[i].first - other.data_[i].first; 
            result.data_[i].second = data_[i].second - other.data_[i].second; 
        }

        return result;
    }

    double Dot(const CComplexVector1& other) const {
        double result = 0;
        
        for (int i = 0; i < data_.size(); i++) {
            result += (data_[i].first * other.data_[i].first);
            result -= (data_[i].second * other.data_[i].second); 
        }

        return result;
    }

    const void Output(std::string filename) override {
        std::ofstream file(filename, std::ios::out);
        for (auto p : data_) {
            file << "(" << p.first << " + " << p.second << "i)\n";
        }
        file.close();
    }
};