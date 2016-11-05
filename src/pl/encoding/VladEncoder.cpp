//
// Created by Simon Hofmann on 18.11.15.
//

#include "VladEncoder.h"

namespace pl {


VladEncodingStep::VladEncodingStep(const cv::Ptr<ConfigContainer> config)
    :
        EncodingStep(config)
{

}


VladEncodingStep::~VladEncodingStep()
{

}

cv::Mat VladEncodingStep::runImpl(const bool debugMode, const cv::Mat &input, const cv::Mat &param) const
{
    cv::Ptr<VladConfig> config;
    try {
        config = config_cast<VladConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw EncodingError(s.str(), currentMethod, currentLine);
    }

    cv::Mat encoded;
    std::vector<std::string> vocabs = config->vocabs();
    int32_t levels = config->pyramidLevels();
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

cv::Mat VladEncodingStep::trainImpl(const bool debugMode, const cv::Mat &input, const cv::Mat &param) const
{
    cv::Ptr<VladConfig> config;
    try {
        config = config_cast<VladConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw EncodingError(s.str(), currentMethod, currentLine);
    }

    int32_t clusters = config->clusters();
    int32_t maxIterations = config->iterations();
    std::vector<std::string> vocabs = config->vocabs();
    double epsilon = config->epsilon();

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


cv::Mat VladEncodingStep::encode(const std::string &encoder, const cv::Mat &data) const
{
    cv::Ptr<VladConfig> config;
    try {
        config = config_cast<VladConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw EncodingError(s.str(), currentMethod, currentLine);
    }

    std::vector<normStrategy> normalization = config->normStrategies();

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
    cv::Ptr<VladConfig> config;
    try {
        config = config_cast<VladConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw EncodingError(s.str(), currentMethod, currentLine);
    }

    std::vector<normStrategy> normalization = config->normStrategies();

    VladEncoder vlad;
    vlad.setNormStrategy(normalization);
    try {
        vlad.loadData(encoder);
    } catch(EncodingError &e) {
        throw EncodingError(e.what(), currentMethod, currentLine);
    }

    DescriptorPyramid dp(config->pyramidLevels());
    std::vector<cv::Mat> pyramid = dp.build(data);
    cv::Mat ret;

    for(int32_t i = 0; i < pyramid.size(); ++i) {
        if(ret.empty()) {
            ret = vlad.encode(pyramid[i]);
        } else {
            cv::hconcat(ret, vlad.encode(pyramid[i]), ret);
        }
    }

    return ret;
}


}
