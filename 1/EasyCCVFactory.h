#pragma once

#include <memory>
#include <functional>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <string>
#include "CComplexVector.h"


class EasyCCVFactory {
public:
    CComplexVector* Create(const char* key, const std::vector<double>& data, const std::string filename) {
        if(strcmp(key, "0") == 0) {
            return new CComplexVector0(data, filename);
        } else if(strcmp(key,"1") == 0) {
            return new CComplexVector1(data, filename);
        }
        return nullptr;
    }
};
