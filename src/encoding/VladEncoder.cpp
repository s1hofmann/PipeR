//
// Created by Simon Hofmann on 18.11.15.
//

#include "VladEncoder.h"

namespace pl {


VladEncodingStep::VladEncodingStep(const cv::Ptr<VladConfig> config)
    :
        EncodingStep(config)
{

}


VladEncodingStep::~VladEncodingStep()
{

}


cv::Mat VladEncodingStep::train(const cv::Mat &input,
                                const cv::Mat &param) const
{
    int clusters = this->mConfig.dynamicCast<VladConfig>()->getClusters();
    int maxIterations = this->mConfig.dynamicCast<VladConfig>()->getIterations();
    std::vector<std::string> vocabs = this->mConfig.dynamicCast<VladConfig>()->getVocabs();
    double epsilon = this->mConfig.dynamicCast<VladConfig>()->getEpsilon();
    std::string path = this->mConfig.dynamicCast<VladConfig>()->getPath();

    for(size_t runs = 0; runs < vocabs.size(); ++runs) {
        KMeansCluster kmeans;
        kmeans.cluster(input,
                       clusters,
                       maxIterations,
                       epsilon);

        kmeans.dump(vocabs[runs]);
    }

    return cv::Mat();
}


cv::Mat VladEncodingStep::run(const cv::Mat &input,
                              const cv::Mat &param) const
{
    std::vector<normStrategy> normalization = this->mConfig.dynamicCast<VladConfig>()->getNormStrategies();

    cv::Mat encoded;
    std::vector<std::string> vocabs = this->mConfig.dynamicCast<VladConfig>()->getVocabs();
    for(size_t runs = 0; runs < vocabs.size(); ++runs) {
        std::string inputFile = vocabs[runs];

        VladEncoder vlad;
        vlad.setNormStrategy(normalization);
        try {
            vlad.loadData(inputFile);
        } catch(std::runtime_error &e) {
            error("Unable to load cluster center data.");
            exit(-1);
        }

        if(encoded.empty()) {
            encoded = vlad.encode(input);
        } else {
            cv::Mat enc = vlad.encode(input);
            cv::hconcat(encoded, enc, encoded);
        }
    }

    return encoded;
}


cv::Mat VladEncodingStep::debugTrain(const cv::Mat &input,
                                     const cv::Mat &param) const
{
    std::cout << "Debug mode" << std::endl;
    return this->train(input,
                       param);
}


cv::Mat VladEncodingStep::debugRun(const cv::Mat &input,
                                   const cv::Mat &param) const
{
    std::cout << "Debug mode" << std::endl;
    this->run(input,
              param);
}


}
