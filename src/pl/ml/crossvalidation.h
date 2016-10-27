#pragma once

#include <vector>
#include "../core/utils/Range.h"

namespace pl{


class CrossValidation
{
public:
    CrossValidation();

    static std::vector<std::pair<std::vector<unsigned int>, std::vector<unsigned int>>> createFolds(const unsigned long &length,
                                                                                                    const unsigned int folds);
};


class CrossValidationContainer
{
public:
    CrossValidationContainer();

    std::vector<std::pair<std::vector<unsigned int>, std::vector<unsigned int>>> trainingData();
    std::vector<std::pair<std::vector<unsigned int>, std::vector<unsigned int>>> testData();
};

}
