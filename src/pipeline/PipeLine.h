//
// Created by Simon Hofmann on 16.11.15.
//


#pragma once

#include <vector>
#include <iostream>
#include <opencv2/core/core.hpp>
#include "PipelineStep.h"
#include "../preprocessing/VesselMask.h"
#include "../preprocessing/VesselMaskConfig.h"
#include "../encoding/VladEncoder.h"
#include "../feature_extraction/SiftDetector.h"
#include "../feature_extraction/SiftConfigContainer.h"

namespace pipe {

template <class T>
class PipeLine {
public:
    PipeLine(bool debug = false);
    virtual ~PipeLine();

    void train(const cv::Mat &input, const cv::Mat &mask) const;

    T run(const cv::Mat &input, const cv::Mat &mask) const;

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
    std::vector<cv::Ptr<PreprocessingStep>> mPreprocessing;
    cv::Ptr<PipelineStep> mFeatureExtraction;
    std::vector<cv::Ptr<PipelineStep>> mPostprocessing;
    cv::Ptr<PipelineStep> mDimensionalityReduction;
    cv::Ptr<PipelineStep> mEncoding;
    cv::Ptr<PipelineStep> mTraining;
    cv::Ptr<PipelineStep> mClassification;

    cv::Mat1b feMask;

    bool mDebugMode;
};

//Includes template implementation for successful compilation
#include "PipeLine.tpp"

}

