#include <memory>
#include <functional>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <string>
#include "CComplexVector.h"
#include "CCVFactory.h"

std::unique_ptr<CComplexVector> CComplexVectorFactory::Create(std::string const& key, const std::vector<double>& raw_data) const
{
    auto it = creators_.find(key);
    if (it == creators_.end()) {
        throw std::invalid_argument("Unknown CComplexVector type: " + key);
    }
    return it->second(raw_data);
}