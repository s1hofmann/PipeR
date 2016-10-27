#include "crossvalidation.h"

namespace pl {


CrossValidation::CrossValidation()
{

}

std::vector<std::pair<std::vector<unsigned int>, std::vector<unsigned int>>> CrossValidation::createFolds(const unsigned long &length,
                                                                                                          const unsigned int folds)
{
    std::vector<std::pair<std::vector<unsigned int>, std::vector<unsigned int>>> foldData;
    foldData.reserve(folds);
    std::vector<unsigned int> indices = Range<unsigned int>::random(0, length);

    unsigned int foldSize = length / folds;

    for(unsigned int idx = 0; idx < folds; ++idx) {
        std::vector<unsigned int> training;
        std::vector<unsigned int> test;
        std::copy(indices.begin() + idx * foldSize, indices.begin() + (idx + 1) * foldSize, std::back_inserter(test));
        std::copy(indices.begin(), indices.begin() + idx * foldSize, std::back_inserter(training));
        std::copy(indices.begin() + (idx + 1) * foldSize, indices.end(), std::back_inserter(training));

        foldData.push_back(std::make_pair(training, test));
    }

    return foldData;
}


}
