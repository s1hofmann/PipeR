//
// Created by Simon Hofmann on 16.11.15.
//

#include "PipeLine.h"

namespace pipe {


PipeLine::PipeLine() {

}


PipeLine::~PipeLine() {

}


unsigned long PipeLine::addPreprocessingStep(const cv::Ptr<PipelineStep> step) {
    this->preprocessing.push_back(step);
    return this->preprocessing.size() - 1;
}


bool PipeLine::removePreprocessingStep(const std::string name) {
    if(this->preprocessing.empty()) {
        return false;
    }

    for(size_t i = 0; i < this->preprocessing.size(); ++i) {
        if(!name.compare(this->preprocessing[i]->info())) {
            this->preprocessing.erase(this->preprocessing.begin() + i);
            return true;
        }
    }
    return false;
}


bool PipeLine::removePreprocessingStep(const unsigned long index) {
    if(this->preprocessing.empty()) {
        return false;
    }

    if(index < this->preprocessing.size()) {
        this->preprocessing.erase(this->preprocessing.begin() + index);
        return true;
    }
    return false;
}


unsigned long PipeLine::addPostprocessingStep(const cv::Ptr<PipelineStep> step) {
    this->postprocessing.push_back(step);
    return this->postprocessing.size() - 1;
}


bool PipeLine::removePostprocessingStep(const std::string name) {
    if(this->postprocessing.empty()) {
        return false;
    }

    for(size_t i = 0; i < this->postprocessing.size(); ++i) {
        if(!name.compare(this->postprocessing[i]->info())) {
            this->postprocessing.erase(this->postprocessing.begin() + i);
            return true;
        }
    }
    return false;
}


bool PipeLine::removePostprocessingStep(const unsigned long index) {
    if(this->postprocessing.empty()) {
        return false;
    }

    if(index < this->postprocessing.size()) {
        this->postprocessing.erase(this->postprocessing.begin() + index);
        return true;
    }
    return false;
}


bool PipeLine::addFeatureExtractionStep(const cv::Ptr<PipelineStep> step) {
    this->featureExtraction = step;
    return this->featureExtraction != nullptr;
}


bool PipeLine::removeFeatureExtractionStep() {
    this->featureExtraction = nullptr;
    return this->featureExtraction == nullptr;
}


void PipeLine::showPipeline() {
    for(size_t i = 0; i < this->preprocessing.size(); ++i) {
        std::cout << "Preprocessing step " << i << ": " << this->preprocessing[i]->info() << std::endl;
    }

    if(this->featureExtraction != nullptr) {
        std::cout << "Feature extraction step: " << this->featureExtraction->info() << std::endl;
    }

    for(size_t i = 0; i < this->postprocessing.size(); ++i) {
        std::cout << "Postprocessing step " << i << ": " << this->postprocessing[i]->info() << std::endl;
    }

    if(this->dimensionalityReduction != nullptr) {
        std::cout << "Dimensionaltiy reduction: " << this->dimensionalityReduction->info() << std::endl;
    }

    if(this->encoding != nullptr) {
        std::cout << "Encoding step: " << this->encoding->info() << std::endl;
    }

    if(this->training != nullptr) {
        std::cout << "Training step: " << this->training->info() << std::endl;
    }

    if(this->classification != nullptr) {
        std::cout << "Classification step: " << this->classification->info() << std::endl;
    }
}


bool PipeLine::addDimensionalityReductionStep(const cv::Ptr<PipelineStep> step) {
    this->dimensionalityReduction = step;
    return this->dimensionalityReduction != nullptr;
}


bool PipeLine::removeDimensionalityReductionStep() {
    this->dimensionalityReduction = nullptr;
    return this->dimensionalityReduction == nullptr;
}


bool PipeLine::addEncodingStep(const cv::Ptr<PipelineStep> step) {
    this->encoding = step;
    return this->encoding != nullptr;
}


bool PipeLine::removeEncodingStep() {
    this->encoding = nullptr;
    return this->encoding == nullptr;
}


bool PipeLine::addTrainingStep(const cv::Ptr<PipelineStep> step) {
    this->training = step;
    return this->training != nullptr;
}


bool PipeLine::removeTrainingStep() {
    this->training = nullptr;
    return this->training == nullptr;
}


bool PipeLine::addClassificationStep(const cv::Ptr<PipelineStep> step) {
    this->classification = step;
    return this->classification != nullptr;
}


bool PipeLine::removeClassificationStep() {
    this->classification = nullptr;
    return this->classification == nullptr;
}


void PipeLine::train() {

}

void PipeLine::classify() {

}

}
