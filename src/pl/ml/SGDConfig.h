#pragma once

#include "MLConfig.h"
#include "../core/vlfeat/wrapper/sgdsolver.h"
#include <opencv2/core/core.hpp>

namespace pl {


class SGDConfig : public MLConfig
{
public:
    SGDConfig(const std::string &identifier,
              const std::vector<std::string> &outputFiles = std::vector<std::string>(),
              const double lambda = 0.01,
              const double learningRate = 0.1,
              const double multiplier = 1,
              const double epsilon = 1e10-5,
              vl_size maxIterations = 10000,
              vl_size iterations = 0,
              const double bias = 0,
              const int folds = 5,
              const bool binary = false);

    virtual ~SGDConfig();

    double lambda() const;
    void setLambda(double lambda);

    double learningRate() const;
    void setLearningRate(double learningRate);

    double multiplier() const;
    void setMultiplier(double multiplier);

    double epsilon() const;
    void setEpsilon(double epsilon);

    cv::Mat1d model() const;
    void setModel(const cv::Mat1d &model);

    double bias() const;
    void setBias(double bias);

    vl_size iterations() const;
    void setIterations(const vl_size &iterations);

    vl_size maxIterations() const;
    void setMaxIterations(const vl_size &maxIterations);

    std::vector<std::string> classifierFiles() const;
    void setClassifierFiles(const std::vector<std::string> &classifierFile);

    // ConfigContainer interface
    virtual std::string toString() const;

    virtual bool fromJSON(std::string &file);

    bool binary() const;
    void setBinary(bool binary);

private:
    double mLambda;
    double mLearningRate;
    double mMultiplier;
    double mEpsilon;
    double mBias;
    bool mBinary;

    cv::Mat1d mModel;

    vl_size mIterations;
    vl_size mMaxIterations;

    std::vector<std::string> mClassifierFiles;
};


}
