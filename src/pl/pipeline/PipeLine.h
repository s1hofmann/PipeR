//
// Created by Simon Hofmann on 16.11.15.
//


#pragma once

#include <vector>
#include <set>
#include <utility>
#include <iostream>

#include <opencv2/core/core.hpp>

#include "PipelineStep.h"
#include "PipelineConfig.h"
#include "globals.h"
#include "argumentprocessor.h"
#include "CommandLineArgument.h"

#include "../dimensionality_reduction/PCAStep.h"
#include "../dimensionality_reduction/PCAConfig.h"
#include "../encoding/VladEncoder.h"
#include "../encoding/VladConfig.h"
#include "../feature_detection/siftdetector.h"
#include "../feature_detection/SiftDetectorConfig.h"
#include "../feature_extraction/SiftExtractor.h"
#include "../feature_extraction/SiftExtractorConfig.h"
#include "../io/FileUtil.h"
#include "../masks/VesselMask.h"
#include "../preprocessing/BinarizationStep.h"
#include "../postprocessing/postprocessingstep.h"
#include "../ml/SGDConfig.h"
#include "../ml/SGDStep.h"
#include "../core/utils/Shuffler.h"
#include "../exception/error.h"
#include "../logging/logging.h"


namespace pl {


class PipeLine {
public:
    /**
     * @brief PipeLine
     * @param debug
     */
    PipeLine(cv::Ptr<PipelineConfig> config);

    /**
     * @brief ~PipeLine
     */
    virtual ~PipeLine();

    /**
     * @brief train
     * @param mask
     */
    void train(const std::vector<std::string> &input,
               const std::vector<int> &labels) const;

    /**
     * @brief run
     * @param input
     * @return
     */
    cv::Mat run(const std::string &input);

    /**
     * @brief run
     * @param input
     * @return
     */
    cv::Mat run(const cv::Mat &inputMat);

    /**
     * @brief execute
     * @param args
     * @return
     */
    cv::Mat execute(const std::unordered_map<std::string, std::string> &args) const;


    /**
     * @brief addPreprocessingStep
     * @param step
     * @return
     */
    unsigned long addPreprocessingStep(const cv::Ptr<PreprocessingStep> step,
                                       const cv::Ptr<MaskGenerator> mask = cv::Ptr<MaskGenerator>());

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
    bool removePreprocessingStep(const size_t index);

    /**
     * @brief addFeatureDetectionStep
     * @param step
     * @param mask
     * @return
     */
    bool addFeatureDetectionStep(const cv::Ptr<FeatureDetectionStep> step,
                                 const cv::Ptr<MaskGenerator> mask);

    /**
     * @brief addFeatureDetectionStep
     * @param step
     * @param mask
     * @return
     */
    bool addFeatureDetectionStep(const cv::Ptr<FeatureDetectionStep> step,
                                 const cv::Mat &mask);

    /**
     * @brief setFeatureDetectionMask
     * @param mask
     * @return
     */
    bool setFeatureDetectionMask(const cv::Mat &mask);

    /**
     * @brief removeFeatureDetectionStep
     * @return
     */
    bool removeFeatureDetectionStep();

    /**
     * @brief addFeatureExtractionStep
     * @param step
     * @return
     */
    bool addFeatureExtractionStep(const cv::Ptr<FeatureExtractionStep> step,
                                  const cv::Ptr<MaskGenerator> mask);

    /**
     * @brief addFeatureExtractionStep
     * @param step
     * @param mask
     * @return
     */
    bool addFeatureExtractionStep(const cv::Ptr<FeatureExtractionStep> step,
                                  const cv::Mat &mask);

    /**
     * @brief addFeatureExtraction
     * @param step
     * @param mask
     * @return
     */
    bool addFeatureExtraction(const cv::Ptr<FeatureExtractionStep> step, const cv::Mat &mask);

    /**
     * @brief setFeatureExtractionMask
     * @param mask
     * @return
     */
    bool setFeatureExtractionMask(const cv::Mat &mask);

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
    unsigned long addPostprocessingStep(const cv::Ptr<PostProcessingStep> step);

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
    bool addDimensionalityReductionStep(const cv::Ptr<DimensionalityReductionStep> step);

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
    bool addTrainingStep(const cv::Ptr<MLStep> step);

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
    bool addClassificationStep(const cv::Ptr<MLStep> step);

    /**
     * @brief removeClassificationStep
     * @return
     */
    bool removeClassificationStep();

    /**
     * @brief showPipeline
     */
    void showPipeline();

    cv::Mat currentInput() const;
    void setCurrentInput(const cv::Mat &currentInput);

private:
    /**
     * @brief mCurrentInput
     */
    cv::Mat mCurrentInput;

    /**
     * @brief mPreprocessing
     */
    std::vector<std::pair<cv::Ptr<PreprocessingStep>, cv::Ptr<MaskGenerator>>> mPreprocessing;

    /**
     * @brief mFeatureDetection
     */
    std::pair<cv::Ptr<FeatureDetectionStep>, cv::Ptr<MaskGenerator>> mFeatureDetection;

    /**
     * @brief mFeatureExtraction
     */
    std::pair<cv::Ptr<FeatureExtractionStep>, cv::Ptr<MaskGenerator>> mFeatureExtraction;

    /**
     * @brief mPreprocessMask
     */
    std::vector<cv::Mat> mPreprocessMasks;

    /**
     * @brief mFeatureMask
     */
    cv::Mat mFeatureDetectMask;

    /**
     * @brief mFeatureExtractMask
     */
    cv::Mat mFeatureExtractMask;

    /**
     * @brief mPostprocessing
     */
    std::vector<cv::Ptr<PostProcessingStep>> mPostprocessing;

    /**
     * @brief mDimensionalityReduction
     */
    cv::Ptr<DimensionalityReductionStep> mDimensionalityReduction;

    /**
     * @brief mEncoding
     */
    cv::Ptr<EncodingStep> mEncoding;

    /**
     * @brief mClassification
     */
    cv::Ptr<MLStep> mClassification;

    /**
     * @brief mPipelineConfig
     */
    cv::Ptr<PipelineConfig> mPipelineConfig;

    /**
     * @brief mDebugMode
     */
    bool mDebugMode;

    /**
     * @brief mConfigNames
     */
    std::set<std::string> mConfigNames;

    /**
     * @brief isValidConfigName
     * @param name
     * @return
     */
    bool isValidConfigName(const std::string &name) const;
};


}
