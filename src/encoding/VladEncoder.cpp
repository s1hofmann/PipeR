//
// Created by Simon Hofmann on 18.11.15.
//

#include "VladEncoder.h"

namespace pl {


VladEncodingStep::VladEncodingStep(const cv::Ptr<VladConfig> config,
                         const std::string &info)
    :
        EncodingStep(config,
                     info)
{

}


VladEncodingStep::~VladEncodingStep()
{

}


cv::Mat VladEncodingStep::train(const cv::Mat &input,
                                const cv::Mat &mask) const
{
    int clusters = this->mConfig.dynamicCast<VladConfig>()->getClusters();
    int maxIterations = this->mConfig.dynamicCast<VladConfig>()->getIterations();
    double epsilon = this->mConfig.dynamicCast<VladConfig>()->getEpsilon();
    std::string path = this->mConfig.dynamicCast<VladConfig>()->getPath();

    KMeansCluster kmeans;
    kmeans.cluster(input,
                   clusters,
                   maxIterations,
                   epsilon);

    kmeans.dump(path);

    std::vector<normStrategy> normalization = this->mConfig.dynamicCast<VladConfig>()->getNormStrategies();

    VladEncoder vlad;
    vlad.setNormStrategy(normalization);
    vlad.loadData(path);

    return vlad.encode(input);
}


cv::Mat VladEncodingStep::run(const cv::Mat &input,
                              const cv::Mat &mask) const
{

}


cv::Mat VladEncodingStep::debugTrain(const cv::Mat &input,
                                     const cv::Mat &mask) const
{
    std::cout << "Debug mode" << std::endl;
    return this->train(input,
                       mask);
}


cv::Mat VladEncodingStep::debugRun(const cv::Mat &input,
                                   const cv::Mat &mask) const
{

}


}
