#include <memory>
#include <functional>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <string>
#include "ObjectFactory.h"

std::unique_ptr<Object> ObjectFactory::Create(std::string const& key, std::ifstream& inputStream) const
{
    auto it = creators_.find(key);
    if (it == creators_.end()) {
        throw std::invalid_argument("Unknown Object type: " + key);
    }
    std::unique_ptr<Object> obj = it->second();
    return obj->Instantiate(inputStream);
}