#pragma once

#include <memory>
#include <functional>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <string>
#include "CComplexVector.h"


class CComplexVectorFactory {
public:
    using Creator = std::function<std::unique_ptr<CComplexVector>(const std::vector<double>&)>;

    template <class Derived>
    void RegisterType(std::string key) {
        static_assert(std::is_base_of_v<CComplexVector, Derived>, "Derived must inherit from CComplexVector");
        creators_[std::move(key)] = [](const std::vector<double>& d) {
            return std::make_unique<Derived>(d);
        };
    }

    std::unique_ptr<CComplexVector> Create( std::string const& key, const std::vector<double>& raw_data) const;

private:
        std::unordered_map<std::string, Creator> creators_;
};