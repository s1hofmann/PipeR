//
// Created by Simon Hofmann on 28.12.15.
//


#pragma once

#include "../pipeline/PipelineStep.h"
#include "metrics.h"

#include <opencv2/core/core.hpp>


namespace pl {


class MLStep : public PseudoPipelineStep {
public:
    // PipelineStep interface
    virtual cv::Mat predictImpl(const bool debugMode,
                                const cv::Mat &input) const = 0;

    virtual cv::Mat trainImpl(const bool debugMode,
                              const cv::Mat &input,
                              const cv::Mat &labels) const = 0;

    virtual cv::Mat optimizeImpl(const bool debugMode,
                                 const std::pair<std::vector<std::vector<unsigned int>>, std::vector<std::vector<unsigned int>>> &indices,
                                 const std::vector<std::pair<cv::Mat, int>> &data) const = 0;

    virtual cv::Mat predict(const cv::Mat &input) const {
        return this->predictImpl(false, input);
    }
    virtual cv::Mat debugPredict(const cv::Mat &input) const {
        return this->predictImpl(true, input);
    }

    virtual cv::Mat train(const cv::Mat &input,
                          const cv::Mat &param) const {
        return this->trainImpl(false, input, param);
    }
    virtual cv::Mat debugTrain(const cv::Mat &input,
                               const cv::Mat &param) const {
        return this->trainImpl(true, input, param);
    }

    virtual cv::Mat optimize(const std::pair<std::vector<std::vector<unsigned int>>, std::vector<std::vector<unsigned int>>> &indices,
                             const std::vector<std::pair<cv::Mat, int>> &data) const {
        return this->optimizeImpl(false, indices, data);
    }
    virtual cv::Mat debugOptimize(const std::pair<std::vector<std::vector<unsigned int>>, std::vector<std::vector<unsigned int>>> &indices,
                                  const std::vector<std::pair<cv::Mat, int>> &data) const {
        return this->optimizeImpl(true, indices, data);
    }

protected:
    MLStep(const cv::Ptr<ConfigContainer> config);

    cv::Mat1d calculateWeights(const cv::Mat1d &labels) const;

    virtual ~MLStep();
};


}
