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

    cv::Mat1d predictions = solver->predict(dInput);
    double negativeLabel, positiveLabel;
    cv::minMaxIdx(dParam, &negativeLabel, &positiveLabel, NULL, NULL);
    predictions.setTo(negativeLabel, predictions < 0);
    predictions.setTo(positiveLabel, predictions >= 0);
    predictions = predictions.t();

    if(config->plattScale()) {
        std::pair<double, double> plattParams = Platt::platt_calibrate(predictions, dParam);
        if(debugMode) { debug("Platt parameter A:", plattParams.first); }
        if(debugMode) { debug("Platt parameter B:", plattParams.second); }
        if(!model.empty()) {
            this->save(model,
                       bias,
                       iterations,
                       plattParams.first,
                       plattParams.second);
        }
    }

    if(!model.empty()) {
        this->save(model,
                   bias,
                   iterations);
    }

    return cv::Mat();
}

cv::Mat SGDStep::optimizeImpl(const bool debugMode,
                              const std::pair<std::vector<std::vector<uint32_t>>, std::vector<std::vector<uint32_t>>> &indices,
                              const std::vector<std::pair<cv::Mat, int32_t>> &data) const
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
    std::vector<std::string> losses = config->loss();

//    if(!checkRangeProperties<double>(lambdas) || !checkRangeProperties<double>(learningRates) || !checkRangeProperties<double>(multipliers)) {
//        throw MLError("Config parameters do not span a valid range.", currentMethod, currentLine);
//    }

//    double lambdaStart, lambdaEnd, lambdaInc;
//    lambdaStart = lambdas[0];
//    lambdaEnd = lambdas[1];
//    lambdaInc = lambdas[2];

//    double lrStart, lrEnd, lrInc;
//    lrStart = learningRates[0];
//    lrEnd = learningRates[1];
//    lrInc = learningRates[2];

//    double mulStart, mulEnd, mulInc;
//    mulStart = multipliers[0];
//    mulEnd = multipliers[1];
//    mulInc = multipliers[2];

    double bestLambda = 0;
    double bestLearningRate = 0;
    double bestMultiplier = 0;
    double bestMetric = 0;
    std::string bestLoss;

    std::vector<cv::Mat1d> trainingsDescriptorCache(config->folds());
    std::vector<cv::Mat1d> trainingsLabelCache(config->folds());
    std::vector<cv::Mat1d> testDescriptorCache(config->folds());
    std::vector<cv::Mat1d> testLabelCache(config->folds());

    for(double lambda : lambdas) {
//        for(double lambda = lambdaStart; lambda < lambdaEnd; lambda += lambdaInc) {
        for(double lr : learningRates) {
//            for(double lr = lrStart; lr < lrEnd; lr += lrInc) {
            for(double mul : multipliers) {
                for(std::string loss : losses) {
//                for(double mul = mulStart; mul < mulEnd; mul += mulInc) {
                    if(debugMode) {
                        debug("Lambda:", lambda);
                        debug("Learning rate:", lr);
                        debug("Multiplier:", mul);
                        debug("Loss function:", loss);
                    }

                    double avgMetric = 0;

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
                                                                                                trainingsLabelCache[fold],
                                                                                                lambda);

                        if(debugMode) { debug("Setting parameters."); }
                        // Bias learning rate and multiplier
                        solver->setBiasLearningRate(lr);
                        solver->setBiasMultiplier(mul);
                        // Sample weights
                        cv::Mat1d weights = calculateWeights(trainingsLabelCache[fold]);
                        solver->setWeights(weights);

                        solver->setLoss(config->lossStrToType(loss));

                        if(debugMode) { debug("Training..."); }
                        solver->train();

                        calculateWeights(testLabelCache[fold]);
                        cv::Mat1d predictions = solver->predict(testDescriptorCache[fold]);
                        double negativeLabel, positiveLabel;
                        cv::minMaxIdx(testLabelCache[fold], &negativeLabel, &positiveLabel, NULL, NULL);
                        predictions.setTo(negativeLabel, predictions < 0);
                        predictions.setTo(positiveLabel, predictions > 0);
                        predictions = predictions.t();

                        double p = Metrics::precision(predictions, testLabelCache[fold]);
                        double r = Metrics::recall(predictions, testLabelCache[fold]);
                        double f = Metrics::f1(predictions, testLabelCache[fold]);
                        if(debugMode) {
                            debug("Precision:", p);
                            debug("Recall:", r);
                            debug("F1 score:", f);
                        }
                        avgMetric += f;
                        solver.release();
                    }
                    avgMetric /= config->folds();

                    if(avgMetric > bestMetric) {
                        bestLoss = loss;
                        bestLambda = lambda;
                        bestLearningRate = lr;
                        bestMultiplier = mul;
                        bestMetric = avgMetric;
                    }
                }
            }
        }
    }

    debug("Best metric score:", bestMetric);
    debug("Best loss:", bestLoss);
    debug("Best lambda:", bestLambda);
    debug("Best learning rate:", bestLearningRate);
    debug("Best multiplier:", bestMultiplier);

    config->setLambdas(std::vector<double>({bestLambda}));
    config->setLearningRates(std::vector<double>({bestLearningRate}));
    config->setMultipliers(std::vector<double>({bestMultiplier}));
    config->setLoss(std::vector<std::string>({bestLoss}));

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
        std::tuple<cv::Mat1d, double, vl_size> classifierData;
        std::tuple<cv::Mat1d, double, vl_size, double, double> plattClassifierData;
        try {
            if(config->plattScale()) {
                plattClassifierData = this->loadWithPlatt(classifierFile);
            } else {
                classifierData = this->load(classifierFile);
            }
            if(input.cols != std::get<0>(classifierData).cols) {
                std::stringstream s;
                s << "Data doesn't fit trained model." << std::endl;
                throw MLError(s.str(), currentMethod, currentLine);
            } else {
                if(input.type() != CV_64F) {
                    cv::Mat tmp;
                    input.convertTo(tmp, CV_64F);
                    if(config->plattScale()) {
                        double score = tmp.dot(std::get<0>(classifierData)) + std::get<1>(classifierData);
                        results.at<double>(idx) = Platt::sigmoid_predict(score,
                                                                         std::get<3>(plattClassifierData),
                                                                         std::get<4>(plattClassifierData));
                    } else {
                        double score = tmp.dot(std::get<0>(classifierData)) + std::get<1>(classifierData);
                        results.at<double>(idx) = score;
                    }
                } else {
                    if(config->plattScale()) {
                        double score = input.dot(std::get<0>(classifierData)) + std::get<1>(classifierData);
                        results.at<double>(idx) = Platt::sigmoid_predict(score,
                                                                         std::get<3>(plattClassifierData),
                                                                         std::get<4>(plattClassifierData));
                    } else {
                        double score = input.dot(std::get<0>(classifierData)) + std::get<1>(classifierData);
                        results.at<double>(idx) = score;
                    }
                }
            }
        } catch(MLError) {
            throw;
        }
    }

    if(config->binary()) {
        if(config->plattScale()) {
            double min, max;
            cv::Point minIdx, maxIdx;
            cv::minMaxLoc(results, &min, &max, &minIdx, &maxIdx);
            int32_t best = maxIdx.x;
            results.setTo(0);
            results.at<double>(best) = 1;
        } else {
            results.setTo(1, results > 0);
            results.setTo(-1, results < 0);
        }
    }

    return results;
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


std::tuple<cv::Mat1d, double, vl_size, double, double> SGDStep::loadWithPlatt(const std::string &fileName) const
{
    cv::FileStorage fs(fileName, cv::FileStorage::READ);

    if ((fs["model"].isNone() || fs["model"].empty()) ||
        (fs["bias"].isNone() || fs["bias"].empty()) ||
        (fs["plattA"].isNone() || fs["plattA"].empty()) ||
        (fs["plattB"].isNone() || fs["plattB"].empty())) {
        std::stringstream s;
        s << "Error. Unable to load classifier data from file: " << fileName << ". Aborting." << std::endl;
        throw MLError(s.str(), currentMethod, currentLine);
    }
    cv::Mat1d model;
    double bias;
    double iterations;
    double plattA;
    double plattB;

    fs["model"] >> model;
    fs["bias"] >> bias;
    fs["plattA"] >> plattA;
    fs["plattB"] >> plattB;

    if(fs["iterations"].isNone() || fs["iterations"].empty()) {
        inform("No iteration info found, skipping. Maybe an old classifier format?");
        iterations = 0;
    } else {
        fs["iterations"] >> iterations;
    }

    fs.release();

    return std::make_tuple(model, bias, static_cast<vl_size>(iterations), plattA, plattB);
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


std::tuple<cv::Mat1d, double, vl_size, double, double> SGDStep::loadWithPlatt() const
{
    cv::Ptr<SGDConfig> config;
    try {
        config = config_cast<SGDConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw MLError(s.str(), currentMethod, currentLine);
    }

    return this->loadWithPlatt(config->classifierFiles()[0]);
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

void SGDStep::save(const cv::Mat1d &model,
                   const double bias,
                   const double iterations,
                   const double plattA,
                   const double plattB) const
{
    cv::Ptr<SGDConfig> config;
    try {
        config = config_cast<SGDConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw MLError(s.str(), currentMethod, currentLine);
    }

    cv::FileStorage fs(config->classifierFiles()[0], cv::FileStorage::WRITE);

    fs << "model" << model;
    fs << "bias" << bias;
    fs << "iterations" << iterations;
    fs << "plattA" << plattA;
    fs << "plattB" << plattB;

    fs.release();
}


}
