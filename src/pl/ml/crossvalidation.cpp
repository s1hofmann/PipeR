#include "crossvalidation.h"

namespace pl {


CrossValidation::CrossValidation()
{

}

std::pair<std::vector<std::vector<uint32_t>>, std::vector<std::vector<uint32_t>>> CrossValidation::createFolds(const unsigned long &length,
                                                                                                                       const uint32_t folds)
{
    std::pair<std::vector<std::vector<uint32_t>>, std::vector<std::vector<uint32_t>>> foldData;
    foldData.first.resize(folds);
    foldData.second.resize(folds);
    std::vector<uint32_t> indices = Range<uint32_t>::random(0, length);

    uint32_t foldSize = length / folds;

    for(uint32_t idx = 0; idx < folds; ++idx) {
        std::copy(indices.begin() + idx * foldSize, indices.begin() + (idx + 1) * foldSize, std::back_inserter(foldData.second[idx]));
        std::copy(indices.begin(), indices.begin() + idx * foldSize, std::back_inserter(foldData.first[idx]));
        std::copy(indices.begin() + (idx + 1) * foldSize, indices.end(), std::back_inserter(foldData.first[idx]));
    }

    return foldData;
}


}
