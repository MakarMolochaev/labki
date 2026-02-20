#include <memory>
#include <functional>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <string>
#include "CComplexVector.h"

class Creator;

class CComplexVectorFactory {
private:
        std::unordered_map<std::string, Creator> creators_;
public:
    using Creator = std::function<std::unique_ptr<CComplexVector>(const std::vector<double>&)>;

    template <class Derived>
    void registerType(std::string key) {
        static_assert(std::is_base_of_v<CComplexVector, Derived>, "Derived must inherit from CComplexVector");

        creators_[std::move(key)] = [](const std::vector<double>& d) {
            return std::make_unique<Derived>(d);
        };
    }

    std::unique_ptr<CComplexVector> create( std::string const& key, const std::vector<double>& raw_data) const
    {
        auto it = creators_.find(key);
        if (it == creators_.end()) {
            throw std::invalid_argument("Unknown CComplexVector type: " + key);
        }
        return it->second(raw_data);
    }

};