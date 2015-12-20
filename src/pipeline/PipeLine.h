//
// Created by Simon Hofmann on 16.11.15.
//


#pragma once

#include <vector>
#include <utility>
#include <iostream>
#include <opencv2/core/core.hpp>
#include "PipelineStep.h"
#include "../masks/VesselMask.h"
#include "../preprocessing/BinarizationStep.h"
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
    void train(const cv::Mat &input) const;

    /**
     * @brief run
     * @param input
     * @param mask
     * @return
     */
    T run(const cv::Mat &input) const;

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
    std::vector<std::pair<cv::Ptr<PreprocessingStep>, cv::Ptr<MaskGenerator>>> mPreprocessing;

    /**
     * @brief mFeatureExtraction
     */
    std::pair<cv::Ptr<FeatureExtractionStep>, cv::Ptr<MaskGenerator>> mFeatureExtraction;

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


template <typename T>
PipeLine<T>::PipeLine(const bool debug) {
    this->mDebugMode = debug;
}


template <typename T>
PipeLine<T>::~PipeLine() {

}


template <typename T>
unsigned long PipeLine<T>::addPreprocessingStep(const cv::Ptr<PreprocessingStep> step,
                                                const cv::Ptr<MaskGenerator> mask) {
    std::pair<cv::Ptr<PreprocessingStep>, cv::Ptr<MaskGenerator>> p = std::make_pair(step, mask);
    this->mPreprocessing.push_back(p);

    return this->mPreprocessing.size() - 1;
}


template <typename T>
bool PipeLine<T>::removePreprocessingStep(const std::string name) {
    if(this->mPreprocessing.empty()) {
        return false;
    }

    for(size_t i = 0; i < this->mPreprocessing.size(); ++i) {
        if(!name.compare(this->mPreprocessing[i].first->info())) {
            this->mPreprocessing.erase(this->mPreprocessing.begin() + i);
            return true;
        }
    }
    return false;
}


template <typename T>
bool PipeLine<T>::removePreprocessingStep(const unsigned long index) {
    if(this->mPreprocessing.empty()) {
        return false;
    }

    if(index < this->mPreprocessing.size()) {
        this->mPreprocessing.erase(this->mPreprocessing.begin() + index);
        return true;
    }
    return false;
}


template <typename T>
unsigned long PipeLine<T>::addPostprocessingStep(const cv::Ptr<PipelineStep> step) {
    this->mPostprocessing.push_back(step);
    return this->mPostprocessing.size() - 1;
}


template <typename T>
bool PipeLine<T>::removePostprocessingStep(const std::string name) {
    if(this->mPostprocessing.empty()) {
        return false;
    }

    for(size_t i = 0; i < this->mPostprocessing.size(); ++i) {
        if(!name.compare(this->mPostprocessing[i]->info())) {
            this->mPostprocessing.erase(this->mPostprocessing.begin() + i);
            return true;
        }
    }
    return false;
}


template <typename T>
bool PipeLine<T>::removePostprocessingStep(const unsigned long index) {
    if(this->mPostprocessing.empty()) {
        return false;
    }

    if(index < this->mPostprocessing.size()) {
        this->mPostprocessing.erase(this->mPostprocessing.begin() + index);
        return true;
    }
    return false;
}


template <typename T>
bool PipeLine<T>::addFeatureExtractionStep(const cv::Ptr<FeatureExtractionStep> step,
                                           const cv::Ptr<MaskGenerator> mask) {
    std::pair<cv::Ptr<FeatureExtractionStep>, cv::Ptr<MaskGenerator>> p = std::make_pair(step, mask);
    this->mFeatureExtraction = p;
    return this->mFeatureExtraction.first.empty();
}


template <typename T>
bool PipeLine<T>::removeFeatureExtractionStep() {
    if(!this->mFeatureExtraction.empty()) {
        this->mFeatureExtraction.release();
    }
    if(!this->mFeatureExtractionMask.empty()) {
        this->mFeatureExtractionMask.release();
    }
    return this->mFeatureExtraction.empty();
}


template <typename T>
void PipeLine<T>::showPipeline() {
    for(size_t i = 0; i < this->mPreprocessing.size(); ++i) {
        std::cout << "Preprocessing step " << i << ": " << this->mPreprocessing[i].first->info() << std::endl;
    }

    if(!this->mFeatureExtraction.first.empty()) {
        std::cout << "Feature extraction step: " << this->mFeatureExtraction.first->info() << std::endl;
    }

    for(size_t i = 0; i < this->mPostprocessing.size(); ++i) {
        std::cout << "Postprocessing step " << i << ": " << this->mPostprocessing[i]->info() << std::endl;
    }

    if(!this->mDimensionalityReduction.empty()) {
        std::cout << "Dimensionaltiy reduction: " << this->mDimensionalityReduction->info() << std::endl;
    }

    if(!this->mEncoding.empty()) {
        std::cout << "Encoding step: " << this->mEncoding->info() << std::endl;
    }

    if(!this->mTraining.empty()) {
        std::cout << "Training step: " << this->mTraining->info() << std::endl;
    }

    if(!this->mClassification.empty()) {
        std::cout << "Classification step: " << this->mClassification->info() << std::endl;
    }
}


template <typename T>
bool PipeLine<T>::addDimensionalityReductionStep(const cv::Ptr<PipelineStep> step) {
    this->mDimensionalityReduction = step;
    return this->mDimensionalityReduction.empty();
}


template <typename T>
bool PipeLine<T>::removeDimensionalityReductionStep() {
    this->mDimensionalityReduction.release();
    return this->mDimensionalityReduction.empty();
}


template <typename T>
bool PipeLine<T>::addEncodingStep(const cv::Ptr<EncodingStep> step) {
    this->mEncoding = step;
    return this->mEncoding.empty();
}


template <typename T>
bool PipeLine<T>::removeEncodingStep() {
    this->mEncoding.release();
    return this->mEncoding.empty();
}


template <typename T>
bool PipeLine<T>::addTrainingStep(const cv::Ptr<PipelineStep> step) {
    this->mTraining = step;
    return this->mTraining.empty();
}


template <typename T>
bool PipeLine<T>::removeTrainingStep() {
    this->mTraining.release();
    return this->mTraining.empty();
}


template <typename T>
bool PipeLine<T>::addClassificationStep(const cv::Ptr<PipelineStep> step) {
    this->mClassification = step;
    return this->mClassification.empty();
}


template <typename T>
bool PipeLine<T>::removeClassificationStep() {
    this->mClassification.release();
    return this->mClassification.empty();
}


template <typename T>
void PipeLine<T>::train(const cv::Mat &input) const {
    cv::Mat prep;
    cv::Mat prepMask;

    if(!this->mPreprocessing.empty()) {
        if(!this->mPreprocessing[0].second.empty()) {
            prepMask = this->mPreprocessing[0].second->create(input);
        } else {
            prepMask = cv::Mat::ones(input.size(), input.type());
        }
        prep = this->mPreprocessing[0].first->train(input, prepMask);
        for(size_t idx = 0; idx < this->mPreprocessing.size(); ++idx) {
            if(!this->mPreprocessing[idx].second.empty()) {
                prepMask = this->mPreprocessing[idx].second->create(prep);
            } else {
                prepMask = cv::Mat::ones(prep.size(), prep.type());
            }
            prep = this->mPreprocessing[idx].first->train(prep, prepMask);
        }
    }

    cv::Mat features;
    cv::Mat featureMask;

    if(!this->mFeatureExtraction.first.empty()) {
        if(!this->mFeatureExtraction.second.empty()) {
            featureMask = this->mFeatureExtraction.second->create(prep);
        } else {
            featureMask = cv::Mat::ones(prep.size(), prep.type());
        }
        cv::Ptr<FeatureExtractionStep> fe;
        features = this->mFeatureExtraction.first->train(prep, featureMask);
    } else {
        std::cerr << "No features generated, aborting." << std::endl;
        exit(-1);
    }
}

template <typename T>
T PipeLine<T>::run(const cv::Mat &input) const {
    return nullptr;
}

}

