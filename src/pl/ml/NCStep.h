#pragma once

#include "MLStep.h"

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>

#include "../core/vlfeat/wrapper/sgdsolver.h"
#include "NCConfig.h"

#ifdef USE_TBB
#include <tbb/parallel_for.h>
#endif

#include <iostream>
#include <utility>

namespace pl {


class NCStep : public MLStep
{
public:
    NCStep(const cv::Ptr<ConfigContainer> config);

    virtual ~NCStep();

    // PipelineStep interface
    virtual cv::Mat predictImpl(const bool debugMode,
                                const cv::Mat &input) const;

    virtual cv::Mat trainImpl(const bool debugMode,
                              const cv::Mat &input,
                              const cv::Mat &labels) const;

    virtual cv::Mat optimizeImpl(const bool debugMode,
                                 const cv::Mat &input, const cv::Mat &labels) const;
private:
    /**
     * @brief load Loads classifier data from a given file
     * @param fileName Filename to load data from
     * @return \link{std::pair} of \link{cv::Mat1d} and double, the first storing model parameters, the latter holds the bias term
     */
    cv::Mat1d load(const std::string &fileName) const;

    /**
     * @brief load
     * @return
     */
    cv::Mat1d load() const;

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
        cv::Ptr<NCConfig> config;
        try {
            config = config_cast<NCConfig>(this->mConfig);
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
              const cv::Mat1d &model) const;

    /**
     * @brief save
     * @param model
     * @param bias
     */
    void save(const cv::Mat1d &model) const;

    void save(const cv::Mat1d &model,
              const double bias,
              const double iterations,
              const double plattA,
              const double plattB) const;

    template<typename T>
    void save(const std::string &fileName, const std::string &identifier, const T &value) {
        cv::FileStorage fs(fileName, cv::FileStorage::WRITE);

        fs << identifier << value;

        fs.release();
    }

    template<typename T>
    void save(const std::string &identifier, const T &value) {
        cv::Ptr<NCConfig> config;
        try {
            config = config_cast<NCConfig>(this->mConfig);
        } catch(std::bad_cast) {
            std::stringstream s;
            s << "Wrong config type: " << this->mConfig->identifier();
            throw MLError(s.str(), currentMethod, currentLine);
        }

        this->save<T>(config->classifierFiles()[0], identifier, value);
    }
};


}
