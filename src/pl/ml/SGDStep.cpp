#include "SGDStep.h"


namespace pl {


SGDStep::SGDStep(const cv::Ptr<ConfigContainer> config)
    :
        MLStep(config)
{
}


SGDStep::~SGDStep()
{
}


cv::Mat SGDStep::trainImpl(const bool debugMode,
                           const cv::Mat &input,
                           const cv::Mat &labels) const
{
    cv::Ptr<SGDConfig> config;
    try {
        config = config_cast<SGDConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw MLError(s.str(), currentMethod, currentLine);
    }

    if(input.empty()) {
        throw MLError("Missing parameters, input empty.", currentMethod, currentLine);
    } else if(labels.empty()) {
        throw MLError("Missing parameters, labels empty.", currentMethod, currentLine);
    }


    cv::Mat1d dInput;
    cv::Mat1d dParam;
    if(!(input.type() == CV_64FC1)) {
        if(debugMode) { debug("Incompatible type of input data, converting."); }
        input.convertTo(dInput, CV_64FC1);
    } else {
        dInput = input;
    }

    if(!(labels.type() == CV_64FC1)) {
        if(debugMode) { debug("Incompatible type of parameter data, converting."); }
        labels.convertTo(dParam, CV_64FC1);
    } else {
        dParam = labels;
    }

    cv::Mat1d weights = calculateWeights(labels);
    double lambda = config->lambdas()[0];
    if(debugMode) { debug("Lambda:", lambda); }
    double learningRate = config->learningRates()[0];
    if(debugMode) { debug("Learning rate:", learningRate); }
    double epsilon = config->epsilon();
    if(debugMode) { debug("Epsilon:", epsilon); }
    double multiplier = config->multipliers()[0];
    if(debugMode) { debug("Multiplier:", multiplier); }
    vl_size iterations = config->iterations();
    if(debugMode) { debug("Iterations:", iterations); }
    vl_size maxIterations = config->maxIterations();
    if(debugMode) { debug("Max. iterations:", maxIterations); }

    cv::Ptr<VlFeatWrapper::SGDSolver> solver = new VlFeatWrapper::SGDSolver(dInput,
                                                                            dParam,
                                                                            lambda);

    // Bias learning rate and multiplier
    if(learningRate > 0) { solver->setBiasLearningRate(learningRate); }
    if(multiplier > 0) { solver->setBiasMultiplier(multiplier); }
    // Sample weights
    if(!weights.empty()) { solver->setWeights(weights); }

    try {
        std::tuple<cv::Mat1d, double, vl_size> warmStartData = this->load(config->classifierFiles()[0]);
        if(!std::get<0>(warmStartData).empty()) {
            solver->setModel(std::get<0>(warmStartData));
        }
        solver->setBias(std::get<1>(warmStartData));
        solver->setStartIterationCount(std::get<2>(warmStartData));
        if(debugMode) { debug("Warm starting training."); }
    } catch(MLError & e) {
        if(debugMode) { debug("Starting training."); }
    }

    // If user defined values for iterations, stopping epsilon and max iterations are present, override settings
    if(iterations > 0) { solver->setStartIterationCount(iterations); }
    if(epsilon > 0) { solver->setEpsilon(epsilon); }
    if(maxIterations > 0) { solver->setMaxIterations(maxIterations); }

    solver->train();

    cv::Mat1d model;
    double bias = 0;

    //Updated classifier data
    model = solver->getModelMat();
    if(debugMode) { debug("Model size:", model.size()); }
    bias = solver->getBias();
    if(debugMode) { debug("Bias:", bias); }
    iterations = solver->getIterationCount();
    if(debugMode) { debug("Iterations:", iterations); }

    if(!model.empty()) {
        this->save(model,
                   bias,
                   iterations);
    }

    return cv::Mat();
}

cv::Mat SGDStep::optimizeImpl(const bool debugMode,
                              const std::pair<std::vector<std::vector<unsigned int>>, std::vector<std::vector<unsigned int>>> &indices,
                              const std::vector<std::pair<cv::Mat, int>> &data) const
{
    cv::Ptr<SGDConfig> config;
    try {
        config = config_cast<SGDConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw MLError(s.str(), currentMethod, currentLine);
    }

    std::vector<double> lambdas = config->lambdas();
    std::vector<double> learningRates = config->learningRates();
    std::vector<double> multipliers = config->multipliers();

    double bestLambda;
    double bestLearningRate;
    double bestMultiplier;
    double bestF = 0;

    for(double lambda : lambdas) {
        for(double lr : learningRates) {
            for(double mul : multipliers) {
                if(debugMode) {
                    debug("Lambda:", lambda);
                    debug("Learning rate:", lr);
                    debug("Multiplier:", mul);
                }

                double avgF = 0;

                std::vector<cv::Mat1d> trainingsDescriptorCache(config->folds());
                std::vector<cv::Mat1d> trainingsLabelCache(config->folds());
                std::vector<cv::Mat1d> testDescriptorCache(config->folds());
                std::vector<cv::Mat1d> testLabelCache(config->folds());

                // Iterate over folds
                for(size_t fold = 0; fold < config->folds(); ++fold) {
                    if(trainingsDescriptorCache[fold].empty() ||
                       trainingsLabelCache[fold].empty()) {
                        if(debugMode) { debug("Rebuilding training cache."); }
                        cv::Mat tmpDesc;
                        cv::Mat tmpIdx;
                        for(auto idx : indices.first[fold]) {
                            tmpDesc.push_back(data[idx].first);
                            tmpIdx.push_back(data[idx].second);
                        }
                        if(tmpDesc.type() != CV_64F) {
                            tmpDesc.convertTo(trainingsDescriptorCache[fold], CV_64F);
                        } else {
                            trainingsDescriptorCache[fold] = tmpDesc;
                        }
                        if(tmpIdx.type() != CV_64F) {
                            tmpIdx.convertTo(trainingsLabelCache[fold], CV_64F);
                        } else {
                            trainingsLabelCache[fold] = tmpIdx;
                        }
                    }
                    if(testDescriptorCache[fold].empty() ||
                       testLabelCache[fold].empty()) {
                        if(debugMode) { debug("Rebuilding test cache."); }
                        cv::Mat tmpDesc;
                        cv::Mat tmpIdx;
                        for(auto idx : indices.second[fold]) {
                            tmpDesc.push_back(data[idx].first);
                            tmpIdx.push_back(data[idx].second);
                        }
                        if(tmpDesc.type() != CV_64F) {
                            tmpDesc.convertTo(testDescriptorCache[fold], CV_64F);
                        } else {
                            testDescriptorCache[fold] = tmpDesc;
                        }
                        if(tmpIdx.type() != CV_64F) {
                            tmpIdx.convertTo(testLabelCache[fold], CV_64F);
                        } else {
                            testLabelCache[fold] = tmpIdx;
                        }
                    }

                    if(debugMode) { debug("Setting up SVM."); }
                    cv::Ptr<VlFeatWrapper::SGDSolver> solver = new VlFeatWrapper::SGDSolver(trainingsDescriptorCache[fold],
                                                                                            trainingsDescriptorCache[fold],
                                                                                            lambda);

                    if(debugMode) { debug("Setting parameters."); }
                    // Bias learning rate and multiplier
                    solver->setBiasLearningRate(lr);
                    solver->setBiasMultiplier(mul);
                    // Sample weights
                    cv::Mat1d weights = calculateWeights(trainingsLabelCache[fold]);
                    solver->setWeights(weights);

                    if(debugMode) { debug("Training..."); }
                    solver->train();

                    cv::Mat1d predictions = solver->predict(testDescriptorCache[fold]);
                    double negativeLabel, positiveLabel;
                    cv::minMaxIdx(testLabelCache[fold], &negativeLabel, &positiveLabel, NULL, NULL);
                    predictions.setTo(negativeLabel, predictions < 0);
                    predictions.setTo(positiveLabel, predictions >= 0);
                    predictions = predictions.t();

                    double f = Metrics::f1(predictions, testLabelCache[fold]);
                    if(debugMode) { debug("F1 score:", f); }
                    avgF += f;
                }
            }
        }
    }
    return cv::Mat();
}


cv::Mat SGDStep::predictImpl(const bool debugMode,
                             const cv::Mat &input) const
{
    cv::Ptr<SGDConfig> config;
    try {
        config = config_cast<SGDConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw MLError(s.str(), currentMethod, currentLine);
    }

    std::vector<std::string> classifiers = config->classifierFiles();
    if(debugMode) { debug(classifiers.size(), "classifier(s)"); }
    cv::Mat1d results(1, classifiers.size());

    for(size_t idx = 0; idx < classifiers.size(); ++idx) {
        std::string classifierFile = classifiers[idx];
        if(debugMode) { debug("Loading classifier", classifierFile); }
        try {
            std::tuple<cv::Mat1d, double, vl_size> classifierData = this->load(classifierFile);
            if(input.cols != std::get<0>(classifierData).cols) {
                std::stringstream s;
                s << "Data doesn't fit trained model." << std::endl;
                throw MLError(s.str(), currentMethod, currentLine);
            } else {
                if(input.type() != CV_64F) {
                    cv::Mat tmp;
                    input.convertTo(tmp, CV_64F);
                    double score = tmp.dot(std::get<0>(classifierData)) + std::get<1>(classifierData);
                    results.at<double>(idx) = score;
                } else {
                    double score = input.dot(std::get<0>(classifierData)) + std::get<1>(classifierData);
                    results.at<double>(idx) = score;
                }
            }
        } catch(MLError) {
            throw;
        }
    }

    if(config->binary()) {
        results.setTo(1, results > 0);
        results.setTo(-1, results < 0);
    }

    return results;
}


std::tuple<cv::Mat1d, double, vl_size> SGDStep::load(const std::string &fileName) const
{
    cv::FileStorage fs(fileName, cv::FileStorage::READ);

    if ((fs["model"].isNone() || fs["model"].empty()) ||
        (fs["bias"].isNone() || fs["bias"].empty())) {
        std::stringstream s;
        s << "Error. Unable to load classifier data from file: " << fileName << ". Aborting." << std::endl;
        throw MLError(s.str(), currentMethod, currentLine);
    }
    cv::Mat1d model;
    double bias;
    double iterations;

    fs["model"] >> model;
    fs["bias"] >> bias;

    if(fs["iterations"].isNone() || fs["iterations"].empty()) {
        inform("No iteration info found, skipping. Maybe an old classifier format?");
        iterations = 0;
    } else {
        fs["iterations"] >> iterations;
    }

    fs.release();

    return std::make_tuple(model, bias, static_cast<vl_size>(iterations));
}


void SGDStep::save(const std::string &fileName,
                   const cv::Mat1d &model,
                   const double bias,
                   const double iterations) const
{
    cv::FileStorage fs(fileName, cv::FileStorage::WRITE);

    fs << "model" << model;
    fs << "bias" << bias;
    fs << "iterations" << iterations;

    fs.release();
}


std::tuple<cv::Mat1d, double, vl_size> SGDStep::load() const
{
    cv::Ptr<SGDConfig> config;
    try {
        config = config_cast<SGDConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw MLError(s.str(), currentMethod, currentLine);
    }

    return this->load(config->classifierFiles()[0]);
}


void SGDStep::save(const cv::Mat1d &model,
                   const double bias,
                   const double iterations) const
{
    cv::Ptr<SGDConfig> config;
    try {
        config = config_cast<SGDConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw MLError(s.str(), currentMethod, currentLine);
    }

    this->save(config->classifierFiles()[0],
               model,
               bias,
               iterations);
}


}
