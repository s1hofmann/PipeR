#include "NCStep.h"


namespace pl {


NCStep::NCStep(const cv::Ptr<ConfigContainer> config)
    :
        MLStep(config)
{
}


NCStep::~NCStep()
{
}


cv::Mat NCStep::trainImpl(const bool debugMode,
                          const cv::Mat &input,
                          const cv::Mat &labels) const
{
    cv::Ptr<NCConfig> config;
    try {
        config = config_cast<NCConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw MLError(s.str(), currentMethod, currentLine);
    }

    if(input.empty()) {
        throw MLError("Missing parameters, input empty.", currentMethod, currentLine);
    } else if(labels.empty()) {
        throw MLError("Missing parameters, labels empty.", currentMethod, currentLine);
    }

    cv::Mat1d dInput;
    cv::Mat1d dParam;
    if(!(input.type() == CV_64FC1)) {
        if(debugMode) { debug("Incompatible type of input data, converting."); }
        input.convertTo(dInput, CV_64FC1);
    } else {
        dInput = input;
    }

    if(!(labels.type() == CV_64FC1)) {
        if(debugMode) { debug("Incompatible type of parameter data, converting."); }
        labels.convertTo(dParam, CV_64FC1);
    } else {
        dParam = labels;
    }

    cv::Mat1d mean;
    cv::reduce(dInput, mean, 0, CV_REDUCE_AVG, CV_64FC1);
    this->save(mean);

    return cv::Mat();
}

cv::Mat NCStep::optimizeImpl(const bool debugMode,
                             const std::pair<std::vector<std::vector<uint32_t>>, std::vector<std::vector<uint32_t>>> &indices,
                             const std::vector<std::pair<cv::Mat, int32_t>> &data) const
{
    inform("No optimization required / implemented.");
    return cv::Mat();
}


cv::Mat NCStep::predictImpl(const bool debugMode,
                            const cv::Mat &input) const
{
    cv::Ptr<NCConfig> config;
    try {
        config = config_cast<NCConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw MLError(s.str(), currentMethod, currentLine);
    }

    std::vector<std::string> classifiers = config->classifierFiles();
    if(debugMode) { debug(classifiers.size(), "classifier(s)"); }

    cv::Mat1d classifierData;
    for(size_t idx = 0; idx < classifiers.size(); ++idx) {
        std::string classifierFile = classifiers[idx];
        if(debugMode) { debug("Loading classifier", classifierFile); }
        if(classifierData.empty()) {
            classifierData = this->load(classifierFile);
        } else {
            cv::Mat1d tmp = this->load(classifierFile);
            if(tmp.cols != classifierData.cols) {
                std::stringstream s;
                s << "Model data missmatch." << std::endl;
                throw MLError(s.str(), currentMethod, currentLine);
            }
            classifierData.push_back(tmp);
        }
    }

    if(input.cols != classifierData.cols) {
        std::stringstream s;
        s << "Data doesn't fit trained model." << std::endl;
        throw MLError(s.str(), currentMethod, currentLine);
    }

    cv::Mat1b results = cv::Mat1b::zeros(input.rows, classifierData.rows);
    std::vector<cv::DMatch> matches;
    cv::BFMatcher matcher;

    cv::Mat cl;
    if(classifierData.type() != CV_32F) {
        classifierData.convertTo(cl, CV_32F);
    } else {
        cl = classifierData;
    }

    if(input.type() != CV_32F) {
        cv::Mat tmp;
        input.convertTo(tmp, CV_32F);
        matcher.match(tmp, cl, matches);
    } else {
        matcher.match(input, cl, matches);
    }
    for(size_t i = 0; i < matches.size(); ++i) {
        results.at<uchar>(matches[i].queryIdx, matches[i].trainIdx) = 1;
    }

    return results;
}


void NCStep::save(const std::string &fileName,
                  const cv::Mat1d &model) const
{
    cv::FileStorage fs(fileName, cv::FileStorage::WRITE);

    fs << "means" << model;

    fs.release();
}


cv::Mat1d NCStep::load(const std::string &fileName) const
{
    cv::FileStorage fs(fileName, cv::FileStorage::READ);

    if ((fs["means"].isNone() || fs["means"].empty())) {
        std::stringstream s;
        s << "Error. Unable to load classifier data from file: " << fileName << ". Aborting." << std::endl;
        throw MLError(s.str(), currentMethod, currentLine);
    }
    cv::Mat1d model;

    fs["means"] >> model;

    fs.release();

    return model;
}


cv::Mat1d NCStep::load() const
{
    cv::Ptr<NCConfig> config;
    try {
        config = config_cast<NCConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw MLError(s.str(), currentMethod, currentLine);
    }

    return this->load(config->classifierFiles()[0]);
}


void NCStep::save(const cv::Mat1d &model) const
{
    cv::Ptr<NCConfig> config;
    try {
        config = config_cast<NCConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw MLError(s.str(), currentMethod, currentLine);
    }

    this->save(config->classifierFiles()[0],
               model);
}


}
