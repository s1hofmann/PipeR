//
// Created by Simon Hofmann on 16.11.15.
//


template <typename T>
PipeLine<T>::PipeLine(const bool debug) {
    this->mDebugMode = debug;
}


template <typename T>
PipeLine<T>::~PipeLine() {

}


template <typename T>
unsigned long PipeLine<T>::addPreprocessingStep(const cv::Ptr<PreprocessingStep> step) {
    this->mPreprocessing.push_back(step);
    return this->mPreprocessing.size() - 1;
}


template <typename T>
bool PipeLine<T>::removePreprocessingStep(const std::string name) {
    if(this->mPreprocessing.empty()) {
        return false;
    }

    for(size_t i = 0; i < this->mPreprocessing.size(); ++i) {
        if(!name.compare(this->mPreprocessing[i]->info())) {
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
bool PipeLine<T>::addFeatureExtractionStep(const cv::Ptr<FeatureExtractionStep> step) {
    this->mFeatureExtraction = step;
    return this->mFeatureExtraction.empty();
}


template <typename T>
bool PipeLine<T>::removeFeatureExtractionStep() {
    this->mFeatureExtraction->release();
    return this->mFeatureExtraction.empty();
}


template <typename T>
void PipeLine<T>::showPipeline() {
    for(size_t i = 0; i < this->mPreprocessing.size(); ++i) {
        std::cout << "Preprocessing step " << i << ": " << this->mPreprocessing[i]->info() << std::endl;
    }

    if(!this->mFeatureExtraction.empty()) {
        std::cout << "Feature extraction step: " << this->mFeatureExtraction->info() << std::endl;
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
void PipeLine<T>::train(const cv::Mat &input, const cv::Mat &mask) const {
    cv::Mat tmp;
    if(!this->mPreprocessing.empty()) {

        if(this->mDebugMode) {
            tmp = this->mPreprocessing[0]->debugTrain(input, mask);
        } else {
            tmp = this->mPreprocessing[0]->train(input, mask);
        }
    }

    for(cv::Ptr<PreprocessingStep> pre : this->mPreprocessing) {
    }
}

template <typename T>
T PipeLine<T>::run(const cv::Mat &input, const cv::Mat &mask) const {
    return nullptr;
}

