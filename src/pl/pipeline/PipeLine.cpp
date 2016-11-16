#include "PipeLine.h"

namespace pl {


PipeLine::PipeLine(cv::Ptr<PipelineConfig> config) {
    this->mPipelineConfig = config;
    mDebugMode = mPipelineConfig->debugMode();
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


bool PipeLine::removePreprocessingStep(const size_t index) {
    if(this->mPreprocessing.empty()) {
        return true;
    }

    if(index < this->mPreprocessing.size()) {
        this->mPreprocessing.erase(this->mPreprocessing.begin() + index);
        return true;
    }
    return false;
}

bool PipeLine::addFeatureDetectionStep(const cv::Ptr<FeatureDetectionStep> step,
                                       const cv::Ptr<MaskGenerator> mask) {
    std::pair<cv::Ptr<FeatureDetectionStep>, cv::Ptr<MaskGenerator>> p = std::make_pair(step, mask);
    this->mFeatureDetection = p;
    this->mFeatureDetectMask = cv::Mat();

    return this->mFeatureDetection.first.empty() && this->mFeatureDetection.second.empty() && this->mFeatureDetectMask.empty();
}

bool PipeLine::addFeatureDetectionStep(const cv::Ptr<FeatureDetectionStep> step,
                                       const cv::Mat &mask) {
    std::pair<cv::Ptr<FeatureDetectionStep>, cv::Ptr<MaskGenerator>> p = std::make_pair(step, cv::Ptr<MaskGenerator>());
    this->mFeatureDetection = p;
    this->mFeatureDetectMask = mask;

    return this->mFeatureDetection.first.empty() && this->mFeatureDetection.second.empty() && this->mFeatureDetectMask.empty();
}

bool PipeLine::setFeatureDetectionMask(const cv::Mat &mask)
{
    this->mFeatureDetectMask = mask;
    return this->mFeatureDetectMask.empty();
}

bool PipeLine::removeFeatureDetectionStep()
{
    if(!this->mFeatureDetection.first.empty()) {
        this->mFeatureDetection.first.release();
    }
    if(!this->mFeatureDetection.second.empty()) {
        this->mFeatureDetection.second.release();
    }
    if(!this->mFeatureDetectMask.empty()) {
        this->mFeatureDetectMask.release();
    }

    return this->mFeatureDetection.first.empty() && this->mFeatureDetection.second.empty() && this->mFeatureDetectMask.empty();
}


unsigned long PipeLine::addPostprocessingStep(const cv::Ptr<PostProcessingStep> step) {
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


bool PipeLine::removePostprocessingStep(const size_t index) {
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
    this->mFeatureExtractMask = cv::Mat();

    return this->mFeatureExtraction.first.empty() && this->mFeatureExtraction.second.empty() && this->mFeatureExtractMask.empty();
}


bool PipeLine::addFeatureExtraction(const cv::Ptr<FeatureExtractionStep> step,
                                    const cv::Mat &mask) {
    std::pair<cv::Ptr<FeatureExtractionStep>, cv::Ptr<MaskGenerator>> p = std::make_pair(step, cv::Ptr<MaskGenerator>());
    this->mFeatureExtraction = p;
    this->mFeatureExtractMask = mask;

    return this->mFeatureDetection.first.empty() && this->mFeatureDetection.second.empty() && this->mFeatureDetectMask.empty();
}


bool PipeLine::removeFeatureExtractionStep() {
    if(!this->mFeatureExtraction.first.empty()) {
        this->mFeatureExtraction.first.release();
    }
    if(!this->mFeatureExtraction.second.empty()) {
        this->mFeatureExtraction.second.release();
    }
    if(!this->mFeatureExtractMask.empty()) {
        this->mFeatureExtractMask.release();
    }

    return this->mFeatureExtraction.first.empty() && this->mFeatureExtraction.second.empty() && this->mFeatureExtractMask.empty();
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

    if(!this->mPreprocessing.empty()) {
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

    std::cout << "Feature detection:" << std::endl;

    if(!this->mFeatureDetection.first.empty()) {
        std::cout << "Method: " << this->mFeatureDetection.first->info() << std::endl;
        if(this->mDebugMode) {
            std::cout << this->mFeatureDetection.first->config() << std::endl;
        }
    }

    if(!this->mFeatureDetection.second.empty()) {
        if(this->mDebugMode) {
            std::cout << "Mask: " << this->mFeatureDetection.second->toString() << std::endl;
        } else {
            std::cout << "Mask: " << this->mFeatureDetection.second->identifier() << std::endl;
        }
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
            std::cout << "Mask: " << this->mFeatureExtraction.second->toString() << std::endl;
        } else {
            std::cout << "Mask: " << this->mFeatureExtraction.second->identifier() << std::endl;
        }
    }

    for(size_t i = 0; i < this->mPostprocessing.size(); ++i) {
        std::cout << "Postprocessing: " << std::endl;
        std::cout << i << ": " << this->mPostprocessing[i]->info() << std::endl;
        std::cout << this->mPostprocessing[i]->config() << std::endl;
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

cv::Mat PipeLine::currentInput() const
{
    return mCurrentInput;
}

void PipeLine::setCurrentInput(const cv::Mat &currentInput)
{
    mCurrentInput = currentInput;
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


void PipeLine::generateDescriptors(const std::vector<std::pair<std::string, int32_t>> &input,
                                   FileLogger &fileLog,
                                   ConsoleLogger &consoleLog) const {
    if(mPipelineConfig->rebuildDescriptors()) {
        for(size_t idx = 0; idx < input.size() && idx < mPipelineConfig->maxDescriptors(); ++idx) {
            //Load image file
            cv::Mat inputMat = FileUtil::loadImage(input[idx].first);

            //Skip empty images
            if(inputMat.empty()) {
                continue;
            }

            fileLog.inform("Processing file:", input[idx].first);

            cv::Mat prep;
            cv::Mat prepMask;

            // Apply possible preprocessing steps
            if(!this->mPreprocessing.empty()) {
                if(mDebugMode) {
                    consoleLog.inform("Starting preprocessing...");
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

            std::vector<cv::KeyPoint> keypoints;
            cv::Mat features;
            cv::Mat featureMask;

            if(!this->mFeatureDetection.first.empty() && !this->mFeatureExtraction.first.empty()) {
                if(mDebugMode) {
                    consoleLog.inform("Starting feature extraction from keypoints...");
                }
                if(!this->mFeatureDetectMask.empty()) {
                    featureMask = this->mFeatureDetectMask.clone();
                } else if(!this->mFeatureDetection.second.empty()) {
                    featureMask = this->mFeatureDetection.second->create(prep);
                    // Check if an all zero mask was generated, in that case, neglect it
                    if(cv::countNonZero(featureMask) == 0) {
                        featureMask = cv::Mat::ones(prep.size(), CV_8UC1);
                    }
                } else {
                    featureMask = cv::Mat::ones(prep.size(), CV_8UC1);
                }
                if(!this->mDebugMode) {
                    keypoints = this->mFeatureDetection.first->detect(prep, featureMask);
                    features = this->mFeatureExtraction.first->compute(prep, keypoints);
                } else {
                    keypoints = this->mFeatureDetection.first->debugDetect(prep, featureMask);
                    features = this->mFeatureExtraction.first->debugCompute(prep, keypoints);
                }
            } else if(!this->mFeatureExtraction.first.empty()) {
                if(mDebugMode) {
                    consoleLog.inform("Starting global feature extraction...");
                }
                if(!this->mFeatureExtractMask.empty()) {
                    featureMask = this->mFeatureExtractMask.clone();
                } else if(!this->mFeatureExtraction.second.empty()) {
                    featureMask = this->mFeatureExtraction.second->create(prep);
                    // Check if an all zero mask was generated, in that case, neglect it
                    if(cv::countNonZero(featureMask) == 0) {
                        featureMask = cv::Mat::ones(prep.size(), CV_8UC1);
                    }
                } else {
                    featureMask = cv::Mat::ones(prep.size(), CV_8UC1);
                }
                if(!this->mDebugMode) {
                    features = this->mFeatureExtraction.first->compute(prep, featureMask);
                } else {
                    features = this->mFeatureExtraction.first->debugCompute(prep, featureMask);
                }
            } else {
                std::stringstream s;
                s << "No feature extraction method given. Aborting." << std::endl;
                throw FeatureExError(s.str(), currentMethod, currentLine);
            }

            if(!features.empty()) {
                cv::Mat postProcessed;
                if(!this->mPostprocessing.empty()) {
                    // First postprocessing step
                    if(!this->mDebugMode) {
                        postProcessed = this->mPostprocessing[0]->train(features);
                    } else {
                        postProcessed = this->mPostprocessing[0]->debugTrain(features);
                    }
                    // Process additional steps
                    for(size_t idx = 1; idx < this->mPreprocessing.size(); ++idx) {
                        if(!this->mDebugMode) {
                            postProcessed = this->mPostprocessing[idx]->train(postProcessed);
                        } else {
                            postProcessed = this->mPostprocessing[idx]->debugTrain(postProcessed);
                        }
                    }
                } else {
                    postProcessed = features;
                }

                cv::Ptr<FeatureConfig> config;
                try {
                    config = config_cast<FeatureConfig>(this->mFeatureExtraction.first->mConfig);
                } catch(std::bad_cast) {
                    std::stringstream s;
                    s << "Wrong config type: " << this->mFeatureExtraction.first->mConfig->identifier();
                    throw FeatureExError(s.str(), currentMethod, currentLine);
                }
                if(config->augment() && !postProcessed.empty()) {
                    fileLog.debug("Truncating augmentation data.");
                    consoleLog.debug("Truncating augmentation data.");
                    postProcessed = postProcessed.colRange(0, postProcessed.cols - 2);
                } else {
                    continue;
                }

                QFileInfo info(QString::fromStdString(input[idx].first));
                std::string descriptorFile = info.baseName().toStdString() + ".ocvmb";
                if(!FileUtil::saveDescriptorWithLabel(postProcessed,
                                                      input[idx].second,
                                                      mPipelineConfig->descriptorDir(),
                                                      descriptorFile,
                                                      mPipelineConfig->descriptorLabelFile())) {
                    fileLog.report("Unable to save descriptor", descriptorFile, ". Skipping!");
                    continue;
                } else {
                    fileLog.report("Wrote descriptor", descriptorFile, ".");
                    continue;
                }
            } else {
                fileLog.report("No features in file", input[idx].first, ". Skipping!");
            }
        }
    }

    // Load all generated descriptors
    if(mDebugMode) {
        consoleLog.inform("Loading generated descriptors...");
    }
    cv::Mat allFeatures = FileUtil::loadDescriptors(mPipelineConfig->descriptorDir(),
                                                    mPipelineConfig->descriptorLabelFile(),
                                                    mPipelineConfig->maxDescriptors(),
                                                    true);

    cv::Ptr<FeatureConfig> config;
    try {
        config = config_cast<FeatureConfig>(this->mFeatureExtraction.first->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mFeatureExtraction.first->mConfig->identifier();
        throw FeatureExError(s.str(), currentMethod, currentLine);
    }
    if(config->augment()) {
        fileLog.debug("Truncating augmentation data.");
        consoleLog.debug("Truncating augmentation data.");
        allFeatures = allFeatures.colRange(0, allFeatures.cols - 2);
    }

    cv::Mat reduced;
    // Apply dimensionality reduction
    if(!this->mDimensionalityReduction.empty() && mPipelineConfig->rebuildPca()) {
        if(mDebugMode) {
            consoleLog.inform("Perfom dimensionality reduction...");
        }
        if(!this->mDebugMode) {
            reduced = this->mDimensionalityReduction->train(allFeatures);
        } else {
            reduced = this->mDimensionalityReduction->debugTrain(allFeatures);
        }
    } else {
        reduced = allFeatures;
    }

    // Result will be neglected here.
    // Should be an empty Mat anyways since cluster means are written to disk
    if(!this->mEncoding.empty() && mPipelineConfig->rebuildClusters()) {
        if(mDebugMode) {
            consoleLog.inform("Encoding...");
        }
        if(!this->mDebugMode) {
            this->mEncoding->train(reduced);
        } else {
            this->mEncoding->debugTrain(reduced);
        }
    }
}


void PipeLine::train(const std::vector<std::pair<std::string, int32_t>> &input) const {
    FileLogger logger(mPipelineConfig.dynamicCast<PipelineConfig>()->logFile());
    ConsoleLogger debug;

    generateDescriptors(input,
                        logger,
                        debug);

    // Load descriptors with corresponding labels
    std::vector<std::pair<std::string, int32_t>> filesWithLabels = FileUtil::getFilesFromLabelFile(mPipelineConfig->descriptorLabelFile(),
                                                                                               mPipelineConfig->maxDescriptors());

    if(mDebugMode) {
        debug.inform("Data size:", filesWithLabels.size());
    }

    if(mDebugMode) {
        if(!this->mDimensionalityReduction.empty() && !this->mEncoding.empty()) {
            debug.inform("Performing dimensionality reduction and encoding.");
            logger.inform("Performing dimensionality reduction and encoding.");
        } else if(!this->mDimensionalityReduction.empty()) {
            debug.inform("Performing dimensionality reduction.");
            logger.inform("Performing dimensionality reduction.");
        } else if(!this->mEncoding.empty()) {
            debug.inform("Performing encoding.");
            logger.inform("Performing encoding.");
        }
    }

    cv::Mat1d trainingData;
    cv::Mat1i trainingLabels;

    // Concatenate descriptors as input to the SVM
    for(size_t idx = 0; idx < filesWithLabels.size(); ++idx) {
        cv::Mat desc = FileUtil::loadBinary(filesWithLabels[idx].first);
        int32_t label = filesWithLabels[idx].second;

        trainingLabels.push_back(label);
        if(!this->mDimensionalityReduction.empty() && !this->mEncoding.empty()) {
            if(!mDebugMode) {
                trainingData.push_back(this->mEncoding->run(this->mDimensionalityReduction->run(desc)));
            } else {
                trainingData.push_back(this->mEncoding->debugRun(this->mDimensionalityReduction->debugRun(desc)));
            }
        } else if(!this->mDimensionalityReduction.empty()) {
            if(!mDebugMode) {
                trainingData.push_back(this->mDimensionalityReduction->run(desc));
            } else {
                trainingData.push_back(this->mDimensionalityReduction->debugRun(desc));
            }
        } else if(!this->mEncoding.empty()) {
            if(!mDebugMode) {
                trainingData.push_back(this->mEncoding->run(desc));
            } else {
                trainingData.push_back(this->mEncoding->debugRun(desc));
            }
        } else {
            trainingData.push_back(desc);
        }
    }

    logger.report("Starting training.");
    debug.report("Starting training.");

    // Permute data
    cv::Mat permutedData;
    cv::Mat permutedLabels;
    Shuffler::shuffle(trainingData,
                      trainingLabels,
                      permutedData,
                      permutedLabels);

    debug.inform("Training...");
    logger.inform("Training...");
    try {
        if(mDebugMode) {
            this->mClassification->debugTrain(permutedData,
                                              permutedLabels);
        } else {
            this->mClassification->train(permutedData,
                                         permutedLabels);
        }
    } catch(MLError &e) {
        logger.report(e.what());
        debug.report(e.what());
        throw;
    }

    debug.inform("Training done!");
    logger.inform("Training done!");
}


void PipeLine::optimize(const std::vector<std::pair<std::string, int32_t>> &input) const {
    FileLogger logger(mPipelineConfig.dynamicCast<PipelineConfig>()->logFile());
    ConsoleLogger debug;

    generateDescriptors(input,
                        logger,
                        debug);

    // Load descriptors with corresponding labels
    std::vector<std::pair<std::string, int32_t>> filesWithLabels = FileUtil::getFilesFromLabelFile(mPipelineConfig->descriptorLabelFile(),
                                                                                               mPipelineConfig->maxDescriptors());

    if(mDebugMode) {
        if(!this->mDimensionalityReduction.empty() && !this->mEncoding.empty()) {
            debug.inform("Performing dimensionality reduction and encoding.");
            logger.inform("Performing dimensionality reduction and encoding.");
        } else if(!this->mDimensionalityReduction.empty()) {
            debug.inform("Performing dimensionality reduction.");
            logger.inform("Performing dimensionality reduction.");
        } else if(!this->mEncoding.empty()) {
            debug.inform("Performing encoding.");
            logger.inform("Performing encoding.");
        }
    }

    std::vector<std::pair<cv::Mat, int32_t>> encodedDescriptorsWithLabels;
    for(size_t idx = 0; idx < filesWithLabels.size(); ++idx) {
        cv::Mat desc = FileUtil::loadBinary(filesWithLabels[idx].first);
        int32_t label = filesWithLabels[idx].second;
        if(!this->mDimensionalityReduction.empty() && !this->mEncoding.empty()) {
            if(!mDebugMode) {
                encodedDescriptorsWithLabels.push_back(std::make_pair(this->mEncoding->run(this->mDimensionalityReduction->run(desc)), label));
            } else {
                encodedDescriptorsWithLabels.push_back(std::make_pair(this->mEncoding->debugRun(this->mDimensionalityReduction->debugRun(desc)), label));
            }
        } else if(!this->mDimensionalityReduction.empty()) {
            if(!mDebugMode) {
                encodedDescriptorsWithLabels.push_back(std::make_pair(this->mDimensionalityReduction->run(desc), label));
            } else {
                encodedDescriptorsWithLabels.push_back(std::make_pair(this->mDimensionalityReduction->debugRun(desc), label));
            }
        } else if(!this->mEncoding.empty()) {
            if(!mDebugMode) {
                encodedDescriptorsWithLabels.push_back(std::make_pair(this->mEncoding->run(desc), label));
            } else {
                encodedDescriptorsWithLabels.push_back(std::make_pair(this->mEncoding->debugRun(desc), label));
            }
        } else {
            encodedDescriptorsWithLabels.push_back(std::make_pair(desc, label));
        }
    }
    if(mDebugMode) {
        debug.inform("Data size:", filesWithLabels.size());
    }

    cv::Ptr<MLConfig> mlConfig;
    try {
        mlConfig = config_cast<MLConfig>(this->mClassification->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mClassification->mConfig->identifier();
        throw MLError(s.str(), currentMethod, currentLine);
    }

    if(mlConfig->folds()) {
        logger.inform("Starting crossvalidation.");
        debug.inform("Starting crossvalidation.");

        // Creates randomized indices for n folds of training and test files
        auto crossvalIndices = CrossValidation::createFolds(encodedDescriptorsWithLabels.size(), mlConfig->folds());
        debug.inform("Built indices, crossvalidating...");
        logger.inform("Built indices, crossvalidating...");
        try {
            if(!mDebugMode) {
                this->mClassification->optimize(crossvalIndices,
                                                encodedDescriptorsWithLabels);
            } else {
                this->mClassification->debugOptimize(crossvalIndices,
                                                     encodedDescriptorsWithLabels);
            }
        } catch(MLError &e) {
            logger.report(e.what());
            debug.report(e.what());
            throw;
        }
    } else {
        throw MLError("Missing fold info. Aborting crossvalidation.");
    }

    debug.inform("Crossvalidation done!");
    logger.inform("Crossvalidation done!");
}


cv::Mat PipeLine::run(const std::string &input)
{
    FileLogger logger(mPipelineConfig.dynamicCast<PipelineConfig>()->logFile());
    ConsoleLogger debug;

    //Load image file
    cv::Mat inputMat;
    try {
        inputMat = FileUtil::loadImage(input);
        logger.inform("Processing file:", input);
    } catch(IOError &e) {
        logger.report(e.what());
        throw;
    }

    //Skip empty images
    if(inputMat.empty()) {
        logger.report("Unable to open file:", input, "Aborting.");
        return cv::Mat();
    } else {
        mCurrentInput = inputMat.clone();
    }

    return run(inputMat);
}

cv::Mat PipeLine::run(const cv::Mat &inputMat)
{
    FileLogger logger(mPipelineConfig.dynamicCast<PipelineConfig>()->logFile());
    ConsoleLogger debug;

    mCurrentInput = inputMat.clone();
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
        } else {
            prep = this->mPreprocessing[0].first->debugTrain(inputMat, prepMask);
        }
        // Process additional steps
        for(size_t idx = 1; idx < this->mPreprocessing.size(); ++idx) {
            if(!this->mPreprocessing[idx].second.empty()) {
                prepMask = this->mPreprocessing[idx].second->create(prep);
                if(cv::countNonZero(prepMask) == 0) {
                    debug.warn("Empty preprocessing mask generated. Neglecting.");
                    prepMask = cv::Mat::ones(prep.size(), prep.type());
                }
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

    /*********************************
     * FEATURE EXTRACTION
     *********************************/
    std::vector<cv::KeyPoint> keypoints;
    cv::Mat features;
    cv::Mat featureMask;

    if(!this->mFeatureDetection.first.empty()) {
        if(!this->mFeatureDetectMask.empty()) {
            featureMask = this->mFeatureDetectMask;
        } else if(!this->mFeatureDetection.second.empty()) {
            featureMask = this->mFeatureDetection.second->create(prep);
            // Check if an all zero mask was generated, in that case, neglect it
            if(cv::countNonZero(featureMask) == 0) {
                debug.warn("Empty mask file generated. Neglecting.");
                featureMask = cv::Mat1b::ones(prep.size());
            }
        } else {
            featureMask = cv::Mat1b::ones(prep.size());
        }
        if(!this->mDebugMode) {
            keypoints = this->mFeatureDetection.first->detect(prep, featureMask);
            features = this->mFeatureExtraction.first->compute(prep, keypoints);
            prep.release();
        } else {
            keypoints = this->mFeatureDetection.first->debugDetect(prep, featureMask);
            features = this->mFeatureExtraction.first->debugCompute(prep, keypoints);
            prep.release();
        }
    } else {
        features = prep;
    }

    if(!features.empty()) {
        /*********************************
         * POSTPROCESSING
         *********************************/
        cv::Mat post;
        if(!this->mPostprocessing.empty()) {
            // First postprocessing step
            if(!this->mDebugMode) {
                post = this->mPostprocessing[0]->train(features);
            } else {
                post = this->mPostprocessing[0]->debugTrain(features);
            }
            // Process additional steps
            for(size_t idx = 1; idx < this->mPreprocessing.size(); ++idx) {
                if(!this->mDebugMode) {
                    post = this->mPostprocessing[idx]->train(post);
                } else {
                    post = this->mPostprocessing[idx]->debugTrain(post);
                }
            }
        } else {
            post = features;
        }

        cv::Ptr<FeatureConfig> config;
        try {
            config = config_cast<FeatureConfig>(this->mFeatureExtraction.first->mConfig);
        } catch(std::bad_cast) {
            std::stringstream s;
            s << "Wrong config type: " << this->mFeatureExtraction.first->mConfig->identifier();
            throw FeatureExError(s.str(), currentMethod, currentLine);
        }
        if(config->augment() && !post.empty()) {
            logger.debug("Truncating augmentation data.");
            debug.debug("Truncating augmentation data.");
            post = post.colRange(0, post.cols - 2);
        } else {
            return cv::Mat();
        }

        /*********************************
         * DIMENSIONALITY REDUCTION
         *********************************/
        cv::Mat reduced;
        // Apply dimensionality reduction
        if(!this->mDimensionalityReduction.empty()) {
            if(!this->mDebugMode) {
                reduced = this->mDimensionalityReduction->run(post);
                features.release();
            } else {
                reduced = this->mDimensionalityReduction->debugRun(post);
                features.release();
            }
        } else {
            reduced = post;
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
                result = this->mClassification->predict(encoded);
            } else {
                result = this->mClassification->debugPredict(encoded);
            }
        } else {
            result = encoded;
        }

        return result;
    } else {
        return cv::Mat();
    }
}


}
