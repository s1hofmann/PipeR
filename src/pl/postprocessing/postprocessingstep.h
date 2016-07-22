#pragma once

#include "../pipeline/PipelineStep.h"
#include "../pipeline/PipelineConfig.h"

namespace pl {


class PostProcessingStep : public PipelineStep
{
public:
    // PipelineStep interface
    virtual cv::Mat train(const cv::Mat &input,
                          const cv::Mat &param = cv::Mat()) const = 0;
    virtual cv::Mat run(const cv::Mat &input,
                        const cv::Mat &param = cv::Mat()) const = 0;
    virtual cv::Mat debugTrain(const cv::Mat &input,
                               const cv::Mat &param = cv::Mat()) const = 0;
    virtual cv::Mat debugRun(const cv::Mat &input,
                             const cv::Mat &param = cv::Mat()) const = 0;

protected:
    PostProcessingStep(const cv::Ptr<ConfigContainer> config);

    virtual ~PostProcessingStep();

};


}
