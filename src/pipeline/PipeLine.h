//
// Created by Simon Hofmann on 16.11.15.
//


#pragma once

#include <vector>
#include <iostream>
#include <opencv2/core/core.hpp>
#include "PipelineStep.h"
#include "../preprocessing/PreprocessingStep.h"
#include "../encoding/VladEncoder.h"
#include "../feature_extraction/SiftDetector.h"
#include "../feature_extraction/SiftConfigContainer.h"

namespace pipe {

template <class T>
class PipeLine {
public:
    PipeLine();
    virtual ~PipeLine();

    void train();

    T classify();

    unsigned long addPreprocessingStep(const cv::Ptr<PreprocessingStep> step);
    bool removePreprocessingStep(const std::string name);
    bool removePreprocessingStep(const unsigned long index);

    bool addFeatureExtractionStep(const cv::Ptr<FeatureExtractionStep> step);
    bool removeFeatureExtractionStep();

    unsigned long addPostprocessingStep(const cv::Ptr<PipelineStep> step);
    bool removePostprocessingStep(const std::string name);
    bool removePostprocessingStep(const unsigned long index);

    bool addDimensionalityReductionStep(const cv::Ptr<PipelineStep> step);
    bool removeDimensionalityReductionStep();

    bool addEncodingStep(const cv::Ptr<EncodingStep> step);
    bool removeEncodingStep();

    bool addTrainingStep(const cv::Ptr<PipelineStep> step);
    bool removeTrainingStep();

    bool addClassificationStep(const cv::Ptr<PipelineStep> step);
    bool removeClassificationStep();

    void showPipeline();

private:
    std::vector<cv::Ptr<PreprocessingStep>> preprocessing;
    cv::Ptr<PipelineStep> featureExtraction = nullptr;
    std::vector<cv::Ptr<PipelineStep>> postprocessing;
    cv::Ptr<PipelineStep> dimensionalityReduction = nullptr;
    cv::Ptr<PipelineStep> encoding = nullptr;
    cv::Ptr<PipelineStep> training = nullptr;
    cv::Ptr<PipelineStep> classification = nullptr;

    cv::Mat1b feMask;
};

//Includes template implementation for successful compilation
#include "PipeLine.tpp"

}

