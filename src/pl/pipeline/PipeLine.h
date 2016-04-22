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
#include "return_codes.h"

#include "../dimensionality_reduction/PCAStep.h"
#include "../dimensionality_reduction/PCAConfig.h"
#include "../encoding/VladEncoder.h"
#include "../encoding/VladConfig.h"
#include "../feature_extraction/SiftDetector.h"
#include "../feature_extraction/SiftConfigContainer.h"
#include "../io/FileUtil.h"
#include "../masks/VesselMask.h"
#include "../preprocessing/BinarizationStep.h"
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
     * @param mask
     * @return
     */
    cv::Mat run(const std::string &input) const;

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
    bool removePreprocessingStep(const unsigned long index);

    /**
     * @brief addFeatureExtractionStep
     * @param step
     * @return
     */
    bool addFeatureExtractionStep(const cv::Ptr<FeatureExtractionStep> step,
                                  const cv::Ptr<MaskGenerator> mask = cv::Ptr<MaskGenerator>());

    /**
     * @brief addFeatureExtractionStep
     * @param step
     * @param mask
     * @return
     */
    bool addFeatureExtractionStep(const cv::Ptr<FeatureExtractionStep> step,
                                  const cv::Mat &mask=cv::Mat());

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

    bool debugMode() const;

    void setDebugMode(bool debugMode);

private:
    /**
     * @brief mPreprocessing
     */
    std::vector<std::pair<cv::Ptr<PreprocessingStep>, cv::Ptr<MaskGenerator>>> mPreprocessing;

    /**
     * @brief mFeatureExtraction
     */
    std::pair<cv::Ptr<FeatureExtractionStep>, cv::Ptr<MaskGenerator>> mFeatureExtraction;

    /**
     * @brief mFeatureMask
     */
    cv::Mat mFeatureMask;

    /**
     * @brief mPostprocessing
     */
    std::vector<cv::Ptr<PipelineStep>> mPostprocessing;

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

    /**
     * @brief readArguments
     * @param argc
     * @param argv
     * @return
     */
    int readArguments(int argc, char *argv[]);
};


}
