#include "bowencoder.h"

namespace pl {


BOWEncodeingStep::BOWEncodeingStep(const cv::Ptr<ConfigContainer> config)
    :
        EncodingStep(config)
{

}

cv::Mat BOWEncodeingStep::runImpl(const bool debugMode, const cv::Mat &input, const cv::Mat &param) const
{
    cv::Ptr<BOWConfig> config;
    try {
        config = config_cast<BOWConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw EncodingError(s.str(), currentMethod, currentLine);
    }

    cv::Mat encoded;
    std::vector<std::string> vocabs = config->vocabs();
    int levels = config->pyramidLevels();
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

cv::Mat BOWEncodeingStep::trainImpl(const bool debugMode, const cv::Mat &input, const cv::Mat &param) const
{
    cv::Ptr<BOWConfig> config;
    try {
        config = config_cast<BOWConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw EncodingError(s.str(), currentMethod, currentLine);
    }

    int clusters = config->clusters();
    int maxIterations = config->iterations();
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

cv::Mat BOWEncodeingStep::encode(const std::string &encoder, const cv::Mat &data) const
{
    BOWEncoder bow;
    try {
        bow.loadData(encoder);
    } catch(EncodingError &e) {
        throw EncodingError(e.what(), currentMethod, currentLine);
    }

    return bow.encode(data);
}

cv::Mat BOWEncodeingStep::encodePyramid(const std::string &encoder, const cv::Mat &data) const
{
    cv::Ptr<BOWConfig> config;
    try {
        config = config_cast<BOWConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw EncodingError(s.str(), currentMethod, currentLine);
    }

    BOWEncoder bow;
    try {
        bow.loadData(encoder);
    } catch(EncodingError &e) {
        throw EncodingError(e.what(), currentMethod, currentLine);
    }

    DescriptorPyramid dp(config->pyramidLevels());
    std::vector<cv::Mat> pyramid = dp.build(data);
    cv::Mat ret;

    for(size_t i = 0; i < pyramid.size(); ++i) {
        if(ret.empty()) {
            ret = bow.encode(pyramid[i]);
        } else {
            cv::hconcat(ret, bow.encode(pyramid[i]), ret);
        }
    }

    return ret;
}


}
