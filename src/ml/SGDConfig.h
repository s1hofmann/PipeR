#pragma once

#include "../pipeline/ConfigContainer.h"
#include "../core/vlfeat/wrapper/sgdsolver.h"
#include <opencv2/core/core.hpp>

namespace pl {


class SGDConfig : public ConfigContainer
{
public:
    SGDConfig(const std::string &identifier,
              const std::string &classifierFile = "./trainedClassifier.yml",
              const double lambda = 0.01,
              const double bias = 0.0,
              const double learningRate = 0.001,
              const double multiplier = 1,
              const double epsilon = 1e10-5,
              vl_size iterations = 1000,
              vl_size maxIterations = 10000);

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

    std::string classifierFile() const;
    void setClassifierFile(const std::string &classifierFile);

    // ConfigContainer interface
    virtual std::string toString() const;

private:
    double mLambda;
    double mLearningRate;
    double mMultiplier;
    double mEpsilon;
    double mBias;

    cv::Mat1d mModel;

    vl_size mIterations;
    vl_size mMaxIterations;

    std::string mClassifierFile;
};


}
