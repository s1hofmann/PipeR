#pragma once

#include <vector>
#include "../core/utils/Range.h"
#include "../pipeline/globals.h"

namespace pl{


class CrossValidation
{
public:
    CrossValidation();

    static std::pair<std::vector<std::vector<uint32_t>>, std::vector<std::vector<uint32_t>>> createFolds(const unsigned long &length,
                                                                                                                 const uint32_t folds);
};


class CrossValidationContainer
{
public:
    CrossValidationContainer();

    std::vector<std::pair<std::vector<uint32_t>, std::vector<uint32_t>>> trainingData();
    std::vector<std::pair<std::vector<uint32_t>, std::vector<uint32_t>>> testData();
};

}
