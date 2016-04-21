#include "PipeLine.h"

namespace pl {


PipeLine::PipeLine(cv::Ptr<PipelineConfig> config) {
    this->mPipelineConfig = config;
}


PipeLine::~PipeLine() {

}


unsigned long PipeLine::addPreprocessingStep(const cv::Ptr<PreprocessingStep> step,
                                             const cv::Ptr<MaskGenerator> mask) {
    if(isValidConfigName(step->identifier())) {
        if(isValidConfigName(mask->identifier())) {
            std::pair<cv::Ptr<PreprocessingStep>, cv::Ptr<MaskGenerator>> p = std::make_pair(step, mask);
            this->mPreprocessing.push_back(p);
            this->mConfigNames.insert(step->identifier());
            this->mConfigNames.insert(mask->identifier());
            return this->mPreprocessing.size();
        } else {
            return this->mPreprocessing.size();
        }
    } else {
        return this->mPreprocessing.size();
    }
}


bool PipeLine::removePreprocessingStep(const std::string name) {
    if(this->mPreprocessing.empty()) {
        return true;
    }

    for(size_t i = 0; i < this->mPreprocessing.size(); ++i) {
        if(!name.compare(this->mPreprocessing[i].first->info())) {
            // TODO erase config names from config name set
            this->mPreprocessing.erase(this->mPreprocessing.begin() + i);
            return true;
        }
    }
    return false;
}


bool PipeLine::removePreprocessingStep(const unsigned long index) {
    if(this->mPreprocessing.empty()) {
        return true;
    }

    if(index < this->mPreprocessing.size()) {
        this->mPreprocessing.erase(this->mPreprocessing.begin() + index);
        return true;
    }
    return false;
}


unsigned long PipeLine::addPostprocessingStep(const cv::Ptr<PipelineStep> step) {
    this->mPostprocessing.push_back(step);
    return this->mPostprocessing.size();
}


bool PipeLine::removePostprocessingStep(const std::string name) {
    if(this->mPostprocessing.empty()) {
        return true;
    }

    for(size_t i = 0; i < this->mPostprocessing.size(); ++i) {
        if(!name.compare(this->mPostprocessing[i]->info())) {
            this->mPostprocessing.erase(this->mPostprocessing.begin() + i);
            return true;
        }
    }
    return false;
}


bool PipeLine::removePostprocessingStep(const unsigned long index) {
    if(this->mPostprocessing.empty()) {
        return true;
    }

    if(index < this->mPostprocessing.size()) {
        this->mPostprocessing.erase(this->mPostprocessing.begin() + index);
        return true;
    }
    return false;
}


bool PipeLine::addFeatureExtractionStep(const cv::Ptr<FeatureExtractionStep> step,
                                        const cv::Ptr<MaskGenerator> mask) {
    std::pair<cv::Ptr<FeatureExtractionStep>, cv::Ptr<MaskGenerator>> p = std::make_pair(step, mask);
    this->mFeatureExtraction = p;
    return this->mFeatureExtraction.first.empty() && this->mFeatureExtraction.second.empty();
}


bool PipeLine::addFeatureExtractionStep(const cv::Ptr<FeatureExtractionStep> step,
                                        const cv::Mat &featureMask) {
    std::pair<cv::Ptr<FeatureExtractionStep>, cv::Ptr<MaskGenerator>> p = std::make_pair(step, cv::Ptr<MaskGenerator>());
    this->mFeatureExtraction = p;
    this->mFeatureMask = featureMask;

    return this->mFeatureExtraction.first.empty() && this->mFeatureMask.empty();
}


bool PipeLine::removeFeatureExtractionStep() {
    if(!this->mFeatureExtraction.first.empty()) {
        this->mFeatureExtraction.first.release();
    }
    if(!this->mFeatureExtraction.second.empty()) {
        this->mFeatureExtraction.second.release();
    }
    if(!this->mFeatureMask.empty()) {
        this->mFeatureMask.release();
    }
    return this->mFeatureExtraction.first.empty() && this->mFeatureExtraction.second.empty() && this->mFeatureMask.empty();
}


bool PipeLine::isValidConfigName(const std::string &name) const {
    auto n = std::find(mConfigNames.begin(), mConfigNames.end(), name);
    if(n == mConfigNames.end()) {
        return true;
    } else {
        return false;
    }
}


void PipeLine::showPipeline() {
    std::cout << "Global:";
    std::cout << this->mPipelineConfig->toString() << std::endl;

    std::cout << std::endl;

    std::cout << "Preprocessing:" << std::endl;

    if(this->mPreprocessing.empty()) {
        std::cout << "Skip." << std::endl << std::endl;
    } else {
        for(size_t i = 0; i < this->mPreprocessing.size(); ++i) {
            std::cout << "Method " << i << ": " << std::endl << this->mPreprocessing[i].first->info() << std::endl << std::endl;
            if(!this->mPreprocessing[i].second.empty()) {
                std::cout << "Mask " << i << ": " << std::endl;
                if(this->mDebugMode) {
                    std::cout << this->mPreprocessing[i].second->toString() << std::endl;
                } else {
                    std::cout << this->mPreprocessing[i].second->identifier() << std::endl;
                }
            }
        }
    }

    if(!this->mPreprocessing.empty()) {
        std::cout << std::endl;
    }

    std::cout << "Feature extraction:" << std::endl;

    if(!this->mFeatureExtraction.first.empty()) {
        std::cout << "Method: " << this->mFeatureExtraction.first->info() << std::endl;
        if(this->mDebugMode) {
            std::cout << this->mFeatureExtraction.first->config() << std::endl;
        }
    }

    if(!this->mFeatureExtraction.second.empty()) {
        if(this->mDebugMode) {
            std::cout << this->mFeatureExtraction.second->toString() << std::endl;
        } else {
            std::cout << this->mFeatureExtraction.second->identifier() << std::endl;
        }
    }

    for(size_t i = 0; i < this->mPostprocessing.size(); ++i) {
        std::cout << "Postprocessing: " << i << ": " << this->mPostprocessing[i]->info() << std::endl;
    }

    if(!this->mDimensionalityReduction.empty()) {
        std::cout << "Dimensionaltiy reduction: " << this->mDimensionalityReduction->info() << std::endl;
        if(this->mDebugMode) {
            std::cout << this->mDimensionalityReduction->config() << std::endl;
        }
    }

    if(!this->mEncoding.empty()) {
        std::cout << "Encoding step: " << this->mEncoding->info() << std::endl;
        if(this->mDebugMode) {
            std::cout << this->mEncoding->config() << std::endl;
        }
    }

    if(!this->mClassification.empty()) {
        std::cout << "Classification step: " << this->mClassification->info() << std::endl;
        if(this->mDebugMode) {
            std::cout << this->mClassification->config() << std::endl;
        }
    }
}


bool PipeLine::addDimensionalityReductionStep(const cv::Ptr<DimensionalityReductionStep> step) {
    this->mDimensionalityReduction = step;
    return this->mDimensionalityReduction.empty();
}


bool PipeLine::removeDimensionalityReductionStep() {
    this->mDimensionalityReduction.release();
    return this->mDimensionalityReduction.empty();
}


bool PipeLine::addEncodingStep(const cv::Ptr<EncodingStep> step) {
    this->mEncoding = step;
    return this->mEncoding.empty();
}


bool PipeLine::removeEncodingStep() {
    this->mEncoding.release();
    return this->mEncoding.empty();
}


bool PipeLine::addClassificationStep(const cv::Ptr<MLStep> step) {
    this->mClassification = step;
    return this->mClassification.empty();
}


bool PipeLine::removeClassificationStep() {
    this->mClassification.release();
    return this->mClassification.empty();
}


void PipeLine::train(const std::vector<std::string> &input,
                     const std::vector<int> &labels) const {
    if(input.size() != labels.size()) {
        std::stringstream s;
        s << "Data and labels missmatch. Aborting." << std::endl;
        throw BaseError(s.str(), currentMethod, currentLine);
    }

    if(mPipelineConfig->rebuildDescriptors()) {
        for(size_t idx = 0; idx < input.size(); ++idx) {
            //Load image file
            cv::Mat inputMat = FileUtil::loadImage(input[idx]);

            //Skip empty images
            if(inputMat.empty()) {
                continue;
            }

            info("Processing file:", input[idx]);

            cv::Mat prep;
            cv::Mat prepMask;

            // Apply possible preprocessing steps
            if(!this->mPreprocessing.empty()) {
                if(mDebugMode) {
                    info("Starting preprocessing...");
                }
                // First preprocessing step
                // Generate mask
                if(!this->mPreprocessing[0].second.empty()) {
                    prepMask = this->mPreprocessing[0].second->create(inputMat);
                } else {
                    prepMask = cv::Mat::ones(inputMat.size(), inputMat.type());
                }
                if(!this->mDebugMode) {
                    prep = this->mPreprocessing[0].first->train(inputMat, prepMask);
                } else {
                    prep = this->mPreprocessing[0].first->debugTrain(inputMat, prepMask);
                }
                inputMat.release();
                // Process additional steps
                for(size_t idx = 1; idx < this->mPreprocessing.size(); ++idx) {
                    if(!this->mPreprocessing[idx].second.empty()) {
                        prepMask = this->mPreprocessing[idx].second->create(prep);
                    } else {
                        prepMask = cv::Mat::ones(prep.size(), prep.type());
                    }
                    if(!this->mDebugMode) {
                        prep = this->mPreprocessing[idx].first->train(prep, prepMask);
                    } else {
                        prep = this->mPreprocessing[idx].first->debugTrain(prep, prepMask);
                    }
                }
            } else {
                prep = inputMat;
            }
            // Mask is no longer needed
            prepMask.release();

            cv::Mat features;
            cv::Mat featureMask;

            if(!this->mFeatureExtraction.first.empty()) {
                if(mDebugMode) {
                    info("Starting feature extraction...");
                }
                if(!this->mFeatureExtraction.second.empty()) {
                    featureMask = this->mFeatureExtraction.second->create(prep);
                    // Check if an all zero mask was generated, in that case, neglect it
                    if(cv::countNonZero(featureMask) == 0) {
                        featureMask = cv::Mat::ones(prep.size(), prep.type());
                    }
                } else {
                    featureMask = cv::Mat::ones(prep.size(), prep.type());
                }
                if(!this->mDebugMode) {
                    features = this->mFeatureExtraction.first->train(prep, featureMask);
                } else {
                    features = this->mFeatureExtraction.first->debugTrain(prep, featureMask);
                }
                prep.release();
                if(!features.empty()) {
                    QFileInfo info(QString::fromStdString(input[idx]));
                    std::string descriptorFile = info.baseName().toStdString() + ".ocvmb";
                    if(!FileUtil::saveDescriptorWithLabel(features,
                                                          labels[idx],
                                                          mPipelineConfig->descriptorDir(),
                                                          descriptorFile,
                                                          mPipelineConfig->descriptorLabelFile())) {
                        error("Unable to save descriptor. Skipping!");
                        continue;
                    } else {
                        // Free no longer needed stuff
                        features.release();
                        featureMask.release();
                        continue;
                    }
                } else {
                    error("Features don't match, skipping.");
                }
            } else {
                std::stringstream s;
                s << "No feature extraction method given. Aborting." << std::endl;
                throw FeatureExError(s.str(), currentMethod, currentLine);
            }
        }
    }

    // Load all generated descriptors
    if(mDebugMode) {
        info("Loading generated descriptors...");
    }
    cv::Mat allFeatures = FileUtil::loadDescriptors(mPipelineConfig->descriptorDir(),
                                                    mPipelineConfig->descriptorLabelFile(),
                                                    mPipelineConfig->maxDescriptors(),
                                                    true);


    cv::Mat reduced;
    // Apply dimensionality reduction
    if(!this->mDimensionalityReduction.empty() && mPipelineConfig->rebuildPca()) {
        if(mDebugMode) {
            info("Perfom dimensionality reduction...");
        }
        if(!this->mDebugMode) {
            reduced = this->mDimensionalityReduction->train(allFeatures);
        } else {
            reduced = this->mDimensionalityReduction->debugTrain(allFeatures);
        }
        allFeatures.release();
    } else {
        reduced = allFeatures;
    }

    // Result will be neglected here.
    // Should be an empty Mat anyways since cluster means are written to disk
    if(!this->mEncoding.empty() && mPipelineConfig->rebuildClusters()) {
        if(mDebugMode) {
            info("Encoding...");
        }
        if(!this->mDebugMode) {
            this->mEncoding->train(reduced);
        } else {
            this->mEncoding->debugTrain(reduced);
        }
    }

    // Load descriptors with corresponding labels
    std::pair<std::vector<std::string>, std::vector<int>> filesWithLabels = FileUtil::getFilesFromLabelFile(mPipelineConfig->descriptorLabelFile());

    if(mDebugMode) {
        info("Starting training.", "Data size:", filesWithLabels.first.size());
    }

    cv::Mat1d trainingData;
    trainingData.reserve(filesWithLabels.first.size());
    cv::Mat1i trainingLabels;
    trainingLabels.reserve(filesWithLabels.second.size());

    // Concatenate descriptors as input to the SVM
    for(size_t idx = 0; idx < filesWithLabels.first.size(); ++idx) {
        cv::Mat desc = FileUtil::loadBinary(filesWithLabels.first[idx]);
        int label = filesWithLabels.second[idx];

        trainingLabels.push_back(label);
        trainingData.push_back(this->mEncoding->run(this->mDimensionalityReduction->run(desc)));
    }

    // Permute data
    Shuffler shuffler;
    shuffler.shuffle(trainingData, trainingLabels);

    this->mClassification->train(trainingData,
                                 trainingLabels);

    info("Training done!");
}

cv::Mat PipeLine::run(const std::string &input) const {
    //Load image file
    cv::Mat inputMat = FileUtil::loadImage(input);

    //Skip empty images
    if(inputMat.empty()) {
        std::stringstream s;
        s << "Unable to open input file: '" << input << "' Aborting." << std::endl;
        error(s.str());
        return cv::Mat();
    }

    cv::Mat prep;
    cv::Mat prepMask;

    /*********************************
     * PREPROCESSING
     *********************************/
    if(!this->mPreprocessing.empty()) {
        // First preprocessing step
        // Generate mask
        if(!this->mPreprocessing[0].second.empty()) {
            prepMask = this->mPreprocessing[0].second->create(inputMat);
        } else {
            prepMask = cv::Mat::ones(inputMat.size(), inputMat.type());
        }
        if(!this->mDebugMode) {
            prep = this->mPreprocessing[0].first->train(inputMat, prepMask);
            inputMat.release();
        } else {
            prep = this->mPreprocessing[0].first->debugTrain(inputMat, prepMask);
            inputMat.release();
        }
        // Process additional steps
        for(size_t idx = 1; idx < this->mPreprocessing.size(); ++idx) {
            if(!this->mPreprocessing[idx].second.empty()) {
                prepMask = this->mPreprocessing[idx].second->create(prep);
            } else {
                prepMask = cv::Mat::ones(prep.size(), prep.type());
            }
            if(!this->mDebugMode) {
                prep = this->mPreprocessing[idx].first->train(prep, prepMask);
            } else {
                prep = this->mPreprocessing[idx].first->debugTrain(prep, prepMask);
            }
        }
    } else {
        prep = inputMat;
    }
    // Mask is no longer needed
    prepMask.release();

    /*********************************
     * FEATURE EXTRACTION
     *********************************/
    cv::Mat features;
    cv::Mat featureMask;

    if(!this->mFeatureExtraction.first.empty()) {
        if(!this->mFeatureExtraction.second.empty()) {
            featureMask = this->mFeatureExtraction.second->create(prep);
            // Check if an all zero mask was generated, in that case, neglect it
            if(cv::countNonZero(featureMask) == 0) {
                featureMask = cv::Mat::ones(prep.size(), prep.type());
            }
        } else {
            featureMask = cv::Mat::ones(prep.size(), prep.type());
        }
        if(!this->mDebugMode) {
            features = this->mFeatureExtraction.first->train(prep, featureMask);
            prep.release();
        } else {
            features = this->mFeatureExtraction.first->debugTrain(prep, featureMask);
            prep.release();
        }
    }

    /*********************************
     * DIMENSIONALITY REDUCTION
     *********************************/
    cv::Mat reduced;
    // Apply dimensionality reduction
    if(!this->mDimensionalityReduction.empty()) {
        if(!this->mDebugMode) {
            reduced = this->mDimensionalityReduction->train(features);
            features.release();
        } else {
            reduced = this->mDimensionalityReduction->debugTrain(features);
            features.release();
        }
    } else {
        reduced = features;
    }


    /*********************************
     * ENCODING
     *********************************/
    cv::Mat encoded;
    if(!this->mEncoding.empty() && mPipelineConfig->rebuildClusters()) {
        if(!this->mDebugMode) {
            encoded = this->mEncoding->run(reduced);
        } else {
            encoded = this->mEncoding->debugRun(reduced);
        }
    } else {
        encoded = reduced;
    }

    cv::Mat result;
    if(!this->mClassification.empty()) {
        if(!this->mDebugMode) {
            result = this->mClassification->run(encoded);
        } else {
            result = this->mClassification->debugRun(encoded);
        }
    }

    return result;
}

bool PipeLine::debugMode() const
{
    return mDebugMode;
}

void PipeLine::setDebugMode(bool debugMode)
{
    mDebugMode = debugMode;
}


}
