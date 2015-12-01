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
    /**
     * @brief PipeLine
     * @param debug
     */
    PipeLine(bool debug = false);

    /**
     * @brief ~PipeLine
     */
    virtual ~PipeLine();

    /**
     * @brief train
     * @param mask
     */
    void train(const std::vector<cv::Mat &input>, const cv::Mat &mask) const;

    /**
     * @brief run
     * @param input
     * @param mask
     * @return
     */
    T run(const cv::Mat &input, const cv::Mat &mask) const;

    /**
     * @brief addPreprocessingStep
     * @param step
     * @return
     */
    unsigned long addPreprocessingStep(const cv::Ptr<ImageProcessingStep> step);

    /**
     * @brief removePreprocessingStep
     * @param name
     * @return
     */
    bool removePreprocessingStep(const std::string name);

    /**
     * @brief removePreprocessingStep
     * @param index
     * @return
     */
    bool removePreprocessingStep(const unsigned long index);

    /**
     * @brief addFeatureExtractionStep
     * @param step
     * @return
     */
    bool addFeatureExtractionStep(const cv::Ptr<FeatureExtractionStep> step);

    /**
     * @brief removeFeatureExtractionStep
     * @return
     */
    bool removeFeatureExtractionStep();

    /**
     * @brief addPostprocessingStep
     * @param step
     * @return
     */
    unsigned long addPostprocessingStep(const cv::Ptr<PipelineStep> step);

    /**
     * @brief removePostprocessingStep
     * @param name
     * @return
     */
    bool removePostprocessingStep(const std::string name);

    /**
     * @brief removePostprocessingStep
     * @param index
     * @return
     */
    bool removePostprocessingStep(const unsigned long index);

    /**
     * @brief addDimensionalityReductionStep
     * @param step
     * @return
     */
    bool addDimensionalityReductionStep(const cv::Ptr<PipelineStep> step);

    /**
     * @brief removeDimensionalityReductionStep
     * @return
     */
    bool removeDimensionalityReductionStep();

    /**
     * @brief addEncodingStep
     * @param step
     * @return
     */
    bool addEncodingStep(const cv::Ptr<EncodingStep> step);

    /**
     * @brief removeEncodingStep
     * @return
     */
    bool removeEncodingStep();

    /**
     * @brief addTrainingStep
     * @param step
     * @return
     */
    bool addTrainingStep(const cv::Ptr<PipelineStep> step);

    /**
     * @brief removeTrainingStep
     * @return
     */
    bool removeTrainingStep();

    /**
     * @brief addClassificationStep
     * @param step
     * @return
     */
    bool addClassificationStep(const cv::Ptr<PipelineStep> step);

    /**
     * @brief removeClassificationStep
     * @return
     */
    bool removeClassificationStep();

    /**
     * @brief showPipeline
     */
    void showPipeline();

private:
    /**
     * @brief mPreprocessing
     */
    std::vector<cv::Ptr<PreprocessingStep>> mPreprocessing;

    /**
     * @brief mFeatureExtraction
     */
    cv::Ptr<PipelineStep> mFeatureExtraction;

    /**
     * @brief mPostprocessing
     */
    std::vector<cv::Ptr<PipelineStep>> mPostprocessing;

    /**
     * @brief mDimensionalityReduction
     */
    cv::Ptr<PipelineStep> mDimensionalityReduction;

    /**
     * @brief mEncoding
     */
    cv::Ptr<PipelineStep> mEncoding;

    /**
     * @brief mTraining
     */
    cv::Ptr<PipelineStep> mTraining;

    /**
     * @brief mClassification
     */
    cv::Ptr<PipelineStep> mClassification;

    /**
     * @brief mDebugMode
     */
    bool mDebugMode;
};

//Includes template implementation for successful compilation
#include "PipeLine.tpp"

}

