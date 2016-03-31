#include "SGDStep.h"


namespace pl {


SGDStep::SGDStep(const cv::Ptr<SGDConfig> config)
    :
        MLStep(config)
{
}


SGDStep::~SGDStep()
{
}


cv::Mat SGDStep::train(const cv::Mat &input,
                       const cv::Mat &param) const
{
    if(input.empty() || param.empty()) {
        exit(-1);
    }

    cv::Mat1d dInput;
    cv::Mat1d dParam;
    if(!input.type() == CV_64FC1) {
        input.convertTo(dInput, CV_64FC1);
    } else {
        dInput = input;
    }

    //Here param is supposed to hold label data
    if(!param.type() == CV_64FC1) {
        param.convertTo(dParam, CV_64FC1);
    } else {
        dParam = param;
    }

    cv::Mat1d weights = calculateWeights(param);
    double lambda = this->mConfig.dynamicCast<SGDConfig>()->lambda();
    double learningRate = this->mConfig.dynamicCast<SGDConfig>()->learningRate();
    double epsilon = this->mConfig.dynamicCast<SGDConfig>()->epsilon();
    double multiplier = this->mConfig.dynamicCast<SGDConfig>()->multiplier();
    double bias = this->mConfig.dynamicCast<SGDConfig>()->bias();
    vl_size iterations = this->mConfig.dynamicCast<SGDConfig>()->iterations();
    vl_size maxIterations = this->mConfig.dynamicCast<SGDConfig>()->maxIterations();

    cv::Mat1d model = this->mConfig.dynamicCast<SGDConfig>()->model();

    cv::Ptr<VlFeatWrapper::SGDSolver> solver = new VlFeatWrapper::SGDSolver(dInput,
                                                                            dParam,
                                                                            lambda);

    if(!model.empty()) { solver->setModel(model); }
    if(bias > 0) { solver->setBias(bias); }

    if(learningRate > 0) { solver->setBiasLearningRate(learningRate); }
    if(epsilon > 0) { solver->setEpsilon(epsilon); }
    if(multiplier > 0) { solver->setBiasMultiplier(multiplier); }
    if(iterations > 0) { solver->setStartIterationCount(iterations); }
    if(maxIterations > 0) { solver->setMaxIterations(maxIterations); }
    if(!weights.empty()) { solver->setWeights(weights); }

    solver->train();

    //Updated classifier data
    model = solver->getModelMat();
    bias = solver->getBias();

    if(!model.empty()) {
        std::string fileName = this->mConfig.dynamicCast<SGDConfig>()->classifierFile();
        this->save(fileName,
                   model,
                   bias);
    }

    return cv::Mat();
}


cv::Mat SGDStep::run(const cv::Mat &input,
                     const cv::Mat &param) const
{
    std::string inputFile = this->mConfig.dynamicCast<SGDConfig>()->classifierFile();
    std::pair<cv::Mat1d, double> classifierData = this->load(inputFile);
}


cv::Mat SGDStep::debugTrain(const cv::Mat &input,
                            const cv::Mat &param) const
{
    if(input.empty() || param.empty()) {
        std::cerr << "SGDStep::train: Missing parameters, aborting." << std::endl;
        exit(-1);
    }

    cv::Mat1d dInput;
    cv::Mat1d dParam;
    if(!input.type() == CV_64FC1) {
        debug("Incompatible type of input data, converting.");
        input.convertTo(dInput, CV_64FC1);
    } else {
        dInput = input;
    }

    if(!param.type() == CV_64FC1) {
        debug("Incompatible type of parameter data, converting.");
        param.convertTo(dParam, CV_64FC1);
    } else {
        dParam = param;
    }

    double lambda = this->mConfig.dynamicCast<SGDConfig>()->lambda();
    debug(("Lambda:", lambda));
    double learningRate = this->mConfig.dynamicCast<SGDConfig>()->learningRate();
    debug(("Learning rate:", learningRate));
    double epsilon = this->mConfig.dynamicCast<SGDConfig>()->epsilon();
    debug(("Epsilon:", epsilon));
    double multiplier = this->mConfig.dynamicCast<SGDConfig>()->multiplier();
    debug(("Multiplier:", multiplier));
    double bias = this->mConfig.dynamicCast<SGDConfig>()->bias();
    debug(("Bias:", bias));
    vl_size iterations = this->mConfig.dynamicCast<SGDConfig>()->iterations();
    debug(("Iterations:", iterations));
    vl_size maxIterations = this->mConfig.dynamicCast<SGDConfig>()->maxIterations();
    debug(("Max. iterations:", maxIterations));

    cv::Mat1d model = this->mConfig.dynamicCast<SGDConfig>()->model();

    cv::Ptr<VlFeatWrapper::SGDSolver> solver = new VlFeatWrapper::SGDSolver(dInput,
                                                                            dParam,
                                                                            lambda);

    if(!model.empty()) { solver->setModel(model); }

    if(bias > 0) { solver->setBias(bias); }
    if(learningRate > 0) { solver->setBiasLearningRate(learningRate); }
    if(epsilon > 0) { solver->setEpsilon(epsilon); }
    if(multiplier > 0) { solver->setBiasMultiplier(multiplier); }
    if(iterations > 0) { solver->setStartIterationCount(iterations); }
    if(maxIterations > 0) { solver->setMaxIterations(maxIterations); }

    solver->train();
}


cv::Mat SGDStep::debugRun(const cv::Mat &input,
                          const cv::Mat &param) const
{

}


std::pair<cv::Mat1d, double> SGDStep::load(const std::string &fileName) const
{
    cv::FileStorage fs(fileName, cv::FileStorage::READ);

    if ((fs["model"].isNone() || fs["model"].empty()) ||
        (fs["bias"].isNone() || fs["bias"].empty())) {
        std::cout << "Error, unable to load classifier data from file: " << fileName << ". Aborting." << std::endl;
        //TODO: Define proper exit codes
        exit(-1);
    }

    cv::Mat1d model;
    double bias;

    fs["model"] >> model;
    fs["bias"] >> bias;

    fs.release();

    return std::make_pair(model, bias);
}


void SGDStep::save(const std::string &fileName,
                   const cv::Mat1d &model,
                   const double bias) const
{
    cv::FileStorage fs(fileName, cv::FileStorage::WRITE);

    fs << "model" << model;
    fs << "bias" << bias;

    fs.release();
}


}
