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
              const int32_t folds = 5,
              const bool platt = false,
              const bool binary = false);

    virtual ~SGDConfig();

    std::vector<double> lambdas() const;
    bool setLambdas(const std::vector<double> &lambdas);

    std::vector<double> learningRates() const;
    bool setLearningRates(const std::vector<double> &learningRates);

    std::vector<double> multipliers() const;
    bool setMultipliers(const std::vector<double> &multipliers);

    double epsilon() const;
    bool setEpsilon(double epsilon);

    cv::Mat1d model() const;
    void setModel(const cv::Mat1d &model);

    double bias() const;
    void setBias(double bias);

    vl_size iterations() const;
    bool setIterations(const vl_size &iterations);

    vl_size maxIterations() const;
    bool setMaxIterations(const vl_size &maxIterations);

    std::vector<std::string> classifierFiles() const;
    bool setClassifierFiles(const std::vector<std::string> &classifierFile);

    // ConfigContainer interface
    virtual std::string toString() const;

    virtual bool fromJSON(std::string &file);

    bool binary() const;
    bool setBinary(bool binary);

    bool plattScale() const;
    bool setPlattScale(bool plattScale);

private:
    std::vector<double> mLambdas;
    std::vector<double> mLearningRates;
    std::vector<double> mMultipliers;
    double mEpsilon;
    double mBias;
    bool mBinary;
    bool mPlattScale;

    cv::Mat1d mModel;

    vl_size mIterations;
    vl_size mMaxIterations;

    std::vector<std::string> mClassifierFiles;
};


}
