#pragma once

#include <memory>
#include <functional>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <string>
#include "Object.h"


class ObjectFactory {
public:
    using Creator = std::function<std::unique_ptr<Object>()>;

    template <class Derived>
    void RegisterType(std::string key) {
        static_assert(std::is_base_of_v<Object, Derived>, "Derived must inherit from CComplexVector");
        creators_[std::move(key)] = []() {
            return std::make_unique<Derived>();
        };
    }

    std::unique_ptr<Object> Create(std::string const& key, std::ifstream& inputStream) const;

private:
    std::unordered_map<std::string, Creator> creators_;
};