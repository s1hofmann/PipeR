//
// Created by Simon Hofmann on 16.11.15.
//


template <typename T>
PipeLine<T>::PipeLine() {

}


template <typename T>
PipeLine<T>::~PipeLine() {

}


template <typename T>
unsigned long PipeLine<T>::addPreprocessingStep(const cv::Ptr<PreprocessingStep> step) {
    this->preprocessing.push_back(step);
    return this->preprocessing.size() - 1;
}


template <typename T>
bool PipeLine<T>::removePreprocessingStep(const std::string name) {
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


template <typename T>
bool PipeLine<T>::removePreprocessingStep(const unsigned long index) {
    if(this->preprocessing.empty()) {
        return false;
    }

    if(index < this->preprocessing.size()) {
        this->preprocessing.erase(this->preprocessing.begin() + index);
        return true;
    }
    return false;
}


template <typename T>
unsigned long PipeLine<T>::addPostprocessingStep(const cv::Ptr<PipelineStep> step) {
    this->postprocessing.push_back(step);
    return this->postprocessing.size() - 1;
}


template <typename T>
bool PipeLine<T>::removePostprocessingStep(const std::string name) {
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


template <typename T>
bool PipeLine<T>::removePostprocessingStep(const unsigned long index) {
    if(this->postprocessing.empty()) {
        return false;
    }

    if(index < this->postprocessing.size()) {
        this->postprocessing.erase(this->postprocessing.begin() + index);
        return true;
    }
    return false;
}


template <typename T>
bool PipeLine<T>::addFeatureExtractionStep(const cv::Ptr<PipelineStep> step) {
    this->featureExtraction = step;
    return this->featureExtraction != nullptr;
}


template <typename T>
bool PipeLine<T>::removeFeatureExtractionStep() {
    this->featureExtraction = nullptr;
    return this->featureExtraction == nullptr;
}


template <typename T>
void PipeLine<T>::showPipeline() {
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


template <typename T>
bool PipeLine<T>::addDimensionalityReductionStep(const cv::Ptr<PipelineStep> step) {
    this->dimensionalityReduction = step;
    return this->dimensionalityReduction != nullptr;
}


template <typename T>
bool PipeLine<T>::removeDimensionalityReductionStep() {
    this->dimensionalityReduction = nullptr;
    return this->dimensionalityReduction == nullptr;
}


template <typename T>
bool PipeLine<T>::addEncodingStep(const cv::Ptr<PipelineStep> step) {
    this->encoding = step;
    return this->encoding != nullptr;
}


template <typename T>
bool PipeLine<T>::removeEncodingStep() {
    this->encoding = nullptr;
    return this->encoding == nullptr;
}


template <typename T>
bool PipeLine<T>::addTrainingStep(const cv::Ptr<PipelineStep> step) {
    this->training = step;
    return this->training != nullptr;
}


template <typename T>
bool PipeLine<T>::removeTrainingStep() {
    this->training = nullptr;
    return this->training == nullptr;
}


template <typename T>
bool PipeLine<T>::addClassificationStep(const cv::Ptr<PipelineStep> step) {
    this->classification = step;
    return this->classification != nullptr;
}


template <typename T>
bool PipeLine<T>::removeClassificationStep() {
    this->classification = nullptr;
    return this->classification == nullptr;
}


template <typename T>
void PipeLine<T>::train() {

}

template <typename T>
T PipeLine<T>::classify() {
    return nullptr;
}

