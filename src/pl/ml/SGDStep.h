#pragma once

#include "MLStep.h"

#include <opencv2/core/core.hpp>
#include "../core/vlfeat/wrapper/sgdsolver.h"
#include "SGDConfig.h"

#include <iostream>
#include <utility>

namespace pl {


class SGDStep : public MLStep
{
public:
    SGDStep(const cv::Ptr<ConfigContainer> config);

    virtual ~SGDStep();

    // PipelineStep interface
    virtual cv::Mat runImpl(const bool debugMode,
                            const cv::Mat &input,
                            const cv::Mat &param) const override;

    virtual cv::Mat trainImpl(const bool debugMode,
                              const cv::Mat &input,
                              const cv::Mat &param) const override;

private:
    /**
     * @brief load Loads classifier data from a given file
     * @param fileName Filename to load data from
     * @return \link{std::pair} of \link{cv::Mat1d} and double, the first storing model parameters, the latter holds the bias term
     */
    std::tuple<cv::Mat1d, double, vl_size> load(const std::string &fileName) const;

    /**
     * @brief load
     * @return
     */
    std::tuple<cv::Mat1d, double, vl_size> load() const;

    template<typename T>
    T load(const std::string &fileName, const std::string &identifier) {
        cv::FileStorage fs(fileName, cv::FileStorage::READ);
        if(fs[identifier].isNone() || fs[identifier].empty()) {
            std::stringstream s;
            s << "Error. Unable to load data from file: " << fileName << ". Aborting." << std::endl;
            throw MLError(s.str(), currentMethod, currentLine);
        }

        T value;
        fs[identifier] >> value;

        fs.release();

        return value;
    }

    template<typename T>
    T load(const std::string &identifier) {
        cv::Ptr<SGDConfig> config;
        try {
            config = config_cast<SGDConfig>(this->mConfig);
        } catch(std::bad_cast) {
            std::stringstream s;
            s << "Wrong config type: " << this->mConfig->identifier();
            throw MLError(s.str(), currentMethod, currentLine);
        }

        return this->load<T>(config->classifierFiles()[0], identifier);
    }

    /**
     * @brief save Saves classifier data to given file
     * @param fileName Output file
     * @param model \link{cv::Mat1d} containing the classifier parameters
     * @param bias Bias value
     */
    void save(const std::string &fileName,
              const cv::Mat1d &model,
              const double bias,
              const double iterations) const;

    /**
     * @brief save
     * @param model
     * @param bias
     */
    void save(const cv::Mat1d &model,
              const double bias,
              const double iterations) const;

    template<typename T>
    void save(const std::string &fileName, const std::string &identifier, const T &value) {
        cv::FileStorage fs(fileName, cv::FileStorage::WRITE);

        fs << identifier << value;

        fs.release();
    }

    template<typename T>
    void save(const std::string &identifier, const T &value) {
        cv::Ptr<SGDConfig> config;
        try {
            config = config_cast<SGDConfig>(this->mConfig);
        } catch(std::bad_cast) {
            std::stringstream s;
            s << "Wrong config type: " << this->mConfig->identifier();
            throw MLError(s.str(), currentMethod, currentLine);
        }

        this->save<T>(config->classifierFiles()[0], identifier, value);
    }
};


}
