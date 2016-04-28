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
    cv::Mat encoded;
    std::vector<std::string> vocabs = this->mConfig.dynamicCast<VladConfig>()->getVocabs();
    int levels = this->mConfig.dynamicCast<VladConfig>()->getPyramidLevels();
    for(size_t runs = 0; runs < vocabs.size(); ++runs) {
        std::string inputFile = vocabs[runs];

        if(encoded.empty()) {
            if(levels >= 1) {
                encoded = encodePyramid(inputFile, input);
            } else {
                encoded = encode(inputFile, input);
            }
        } else {
            if(levels >= 1) {
                cv::Mat enc = encodePyramid(inputFile, input);
                cv::hconcat(encoded, enc, encoded);
            } else {
                cv::Mat enc = encode(inputFile, input);
                cv::hconcat(encoded, enc, encoded);
            }
        }
    }

    return encoded;
}


cv::Mat VladEncodingStep::debugTrain(const cv::Mat &input,
                                     const cv::Mat &param) const
{
    int clusters = this->mConfig.dynamicCast<VladConfig>()->getClusters();
    int maxIterations = this->mConfig.dynamicCast<VladConfig>()->getIterations();
    std::vector<std::string> vocabs = this->mConfig.dynamicCast<VladConfig>()->getVocabs();
    double epsilon = this->mConfig.dynamicCast<VladConfig>()->getEpsilon();

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


cv::Mat VladEncodingStep::debugRun(const cv::Mat &input,
                                   const cv::Mat &param) const
{
    cv::Mat encoded;
    std::vector<std::string> vocabs = this->mConfig.dynamicCast<VladConfig>()->getVocabs();
    int levels = this->mConfig.dynamicCast<VladConfig>()->getPyramidLevels();
    for(size_t runs = 0; runs < vocabs.size(); ++runs) {
        std::string inputFile = vocabs[runs];

        if(encoded.empty()) {
            if(levels >= 1) {
                encoded = encodePyramid(inputFile, input);
            } else {
                encoded = encode(inputFile, input);
            }
        } else {
            if(levels >= 1) {
                cv::Mat enc = encodePyramid(inputFile, input);
                cv::hconcat(encoded, enc, encoded);
            } else {
                cv::Mat enc = encode(inputFile, input);
                cv::hconcat(encoded, enc, encoded);
            }
        }
    }

    return encoded;
}

cv::Mat VladEncodingStep::encode(const std::string &encoder, const cv::Mat &data) const
{
    std::vector<normStrategy> normalization = this->mConfig.dynamicCast<VladConfig>()->getNormStrategies();

    VladEncoder vlad;
    vlad.setNormStrategy(normalization);
    try {
        vlad.loadData(encoder);
    } catch(EncodingError &e) {
        throw EncodingError(e.what(), currentMethod, currentLine);
    }

    return vlad.encode(data);
}

cv::Mat VladEncodingStep::encodePyramid(const std::string &encoder, const cv::Mat &data) const
{
    std::vector<normStrategy> normalization = this->mConfig.dynamicCast<VladConfig>()->getNormStrategies();

    VladEncoder vlad;
    vlad.setNormStrategy(normalization);
    try {
        vlad.loadData(encoder);
    } catch(EncodingError &e) {
        throw EncodingError(e.what(), currentMethod, currentLine);
    }

    DescriptorPyramid dp(this->mConfig.dynamicCast<VladConfig>()->getPyramidLevels());
    std::vector<cv::Mat> pyramid = dp.build(data);
    cv::Mat ret;

    for(int i = 0; i < pyramid.size(); ++i) {
        if(ret.empty()) {
            ret = vlad.encode(pyramid[i]);
        } else {
            cv::hconcat(ret, vlad.encode(pyramid[i]), ret);
        }
    }

    return ret;
}


}
