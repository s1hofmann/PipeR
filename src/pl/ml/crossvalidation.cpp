#include "crossvalidation.h"

namespace pl {


CrossValidation::CrossValidation()
{

}

std::pair<std::vector<std::vector<unsigned int>>, std::vector<std::vector<unsigned int>>> CrossValidation::createFolds(const unsigned long &length,
                                                                                                                       const unsigned int folds)
{
    std::pair<std::vector<std::vector<unsigned int>>, std::vector<std::vector<unsigned int>>> foldData;
    foldData.first.reserve(folds);
    foldData.second.reserve(folds);
    std::vector<unsigned int> indices = Range<unsigned int>::random(0, length);

    unsigned int foldSize = length / folds;

    for(unsigned int idx = 0; idx < folds; ++idx) {
        std::copy(indices.begin() + idx * foldSize, indices.begin() + (idx + 1) * foldSize, std::back_inserter(foldData.second[idx]));
        std::copy(indices.begin(), indices.begin() + idx * foldSize, std::back_inserter(foldData.first[idx]));
        std::copy(indices.begin() + (idx + 1) * foldSize, indices.end(), std::back_inserter(foldData.first[idx]));
    }

    return foldData;
}


}
