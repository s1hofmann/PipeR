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
                           const cv::Mat &param) const
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
    } else if(param.empty()) {
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

    //Here param is supposed to hold label data
    if(!(param.type() == CV_64FC1)) {
        if(debugMode) { debug("Incompatible type of parameter data, converting."); }
        param.convertTo(dParam, CV_64FC1);
    } else {
        dParam = param;
    }

    cv::Mat1d weights = calculateWeights(param);
    double lambda = config->lambda();
    if(debugMode) { debug("Lambda:", lambda); }
    double learningRate = config->learningRate();
    if(debugMode) { debug("Learning rate:", learningRate); }
    double epsilon = config->epsilon();
    if(debugMode) { debug("Epsilon:", epsilon); }
    double multiplier = config->multiplier();
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
    debug("Model size:", model.size());
    bias = solver->getBias();
    debug("Bias:", bias);
    iterations = solver->getIterationCount();
    debug("Iterations:", iterations);

    if(!model.empty()) {
        this->save(model,
                   bias,
                   iterations);
    }

    return cv::Mat();
}


cv::Mat SGDStep::runImpl(const bool debugMode,
                         const cv::Mat &input,
                         const cv::Mat &param) const
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
    debug(classifiers.size(), "classifier(s)");
    cv::Mat1f results(1, classifiers.size());

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
                    results.at<float>(idx) = score;
                } else {
                    double score = input.dot(std::get<0>(classifierData)) + std::get<1>(classifierData);
                    results.at<float>(idx) = score;
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
        debug("Now iteration info found, skipping.");
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
