#include "NCConfig.h"


namespace pl {


NCConfig::NCConfig(const std::string &identifier,
                   const std::vector<std::string> &outputFiles)
    :
        MLConfig(identifier),
        mClassifierFiles(outputFiles)
{
}


NCConfig::~NCConfig()
{

}


cv::Mat1d NCConfig::means() const
{
    return mMeans;
}


void NCConfig::setMeans(const cv::Mat1d &means)
{
    mMeans = means;
}


std::vector<std::string> NCConfig::classifierFiles() const
{
    return mClassifierFiles;
}


bool NCConfig::setClassifierFiles(const std::vector<std::string> &classifierFiles)
{
    mClassifierFiles = classifierFiles;
    return setConfigParameter<std::string>(varName(mClassifierFiles), classifierFiles);
}


std::string NCConfig::toString() const
{
    std::stringstream configString;

    for(size_t idx = 0; idx < mClassifierFiles.size(); ++idx) {
        configString << "Classifier file: " << mClassifierFiles[idx] << std::endl;
    }

    return configString.str();
}

bool NCConfig::fromJSON(std::string &file)
{
    Json::Value root = readJSON(file);

    if(root.empty()) {
        return false;
    } else {
        const Json::Value params = root[identifier()];

        const Json::Value classifiers = params[varName(mClassifierFiles)];

        if(!classifiers.empty()) {
            mClassifierFiles.clear();
            for(uint32_t idx = 0; idx < classifiers.size(); ++idx) {
                mClassifierFiles.push_back(classifiers[idx].asString());
            }
        } else {
            mClassifierFiles.clear();
            warning("No classifier file specified, using fallback value.");
            mClassifierFiles.push_back("./trainedClassifier.yml");
        }

        return true;
    }
}


}
