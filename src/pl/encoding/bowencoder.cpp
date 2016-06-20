#include "bowencoder.h"

namespace pl {


BOWEncodeingStep::BOWEncodeingStep(const cv::Ptr<BOWConfig> config)
    :
        EncodingStep(config)
{

}

cv::Mat BOWEncodeingStep::train(const cv::Mat &input, const cv::Mat &param) const
{
    int clusters = this->mConfig.dynamicCast<BOWConfig>()->getClusters();
    int maxIterations = this->mConfig.dynamicCast<BOWConfig>()->getIterations();
    std::vector<std::string> vocabs = this->mConfig.dynamicCast<BOWConfig>()->getVocabs();
    double epsilon = this->mConfig.dynamicCast<BOWConfig>()->getEpsilon();

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

cv::Mat BOWEncodeingStep::run(const cv::Mat &input, const cv::Mat &param) const
{
    cv::Mat encoded;
    std::vector<std::string> vocabs = this->mConfig.dynamicCast<BOWConfig>()->getVocabs();
    int levels = this->mConfig.dynamicCast<BOWConfig>()->getPyramidLevels();
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

cv::Mat BOWEncodeingStep::debugTrain(const cv::Mat &input, const cv::Mat &param) const
{
    return this->train(input, param);
}

cv::Mat BOWEncodeingStep::debugRun(const cv::Mat &input, const cv::Mat &param) const
{
    return this->run(input, param);
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
    BOWEncoder bow;
    try {
        bow.loadData(encoder);
    } catch(EncodingError &e) {
        throw EncodingError(e.what(), currentMethod, currentLine);
    }

    DescriptorPyramid dp(this->mConfig.dynamicCast<BOWConfig>()->getPyramidLevels());
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
