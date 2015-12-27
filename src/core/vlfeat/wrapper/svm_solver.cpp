#include "svm_solver.h"
#include <iostream>

VlFeatWrapper::SVMSolver::SVMSolver(VlSvmSolverType type, cv::Mat1d &data, cv::Mat1d &labels, double lambda)
{
    CV_Assert(data.isContinuous());
    CV_Assert(labels.isContinuous());

    vl_size const numData = data.rows;
    vl_size const dimensions = data.cols;

    double * dataPtr = reinterpret_cast<double*>(data.data);
    double * lablePtr = reinterpret_cast<double*>(labels.data);

    this->svm = vl_svm_new(type,
                           dataPtr,
                           dimensions,
                           numData,
                           lablePtr,
                           lambda);
}

VlFeatWrapper::SVMSolver::~SVMSolver()
{
    vl_svm_delete(this->svm);
}

void VlFeatWrapper::SVMSolver::setEpsilon(double epsilon)
{
    vl_svm_set_epsilon(this->svm, epsilon);
}

double VlFeatWrapper::SVMSolver::getEpsilon() const
{
    return vl_svm_get_epsilon(this->svm);
}

void VlFeatWrapper::SVMSolver::setBiasMultiplier(double bias)
{
    vl_svm_set_bias_multiplier(this->svm, bias);
}

void VlFeatWrapper::SVMSolver::setMaxIterations(int max)
{
    vl_svm_set_max_num_iterations(this->svm, max);
}


vl_size VlFeatWrapper::SVMSolver::getMaxIterations() const
{
    return vl_svm_get_max_num_iterations(this->svm);
}

vl_size VlFeatWrapper::SVMSolver::getCurrentIterationCount() const
{
    return this->getStatistics()->iteration;
}

void VlFeatWrapper::SVMSolver::setStartIterationCount(const vl_size count) const
{
    vl_svm_set_iteration_number(this->svm, count);
}

vl_size VlFeatWrapper::SVMSolver::getStartIterationCount() const
{
    return vl_svm_get_iteration_number(this->svm);
}

void VlFeatWrapper::SVMSolver::train()
{
    vl_svm_train(this->svm);
}

double const * VlFeatWrapper::SVMSolver::getModel() const
{
    return vl_svm_get_model(this->svm);
}

cv::Mat1d VlFeatWrapper::SVMSolver::getModelMat() const
{
    return cv::Mat1d(1, getModelDimension(), const_cast<double*>(getModel()));
}

double VlFeatWrapper::SVMSolver::getDiagnosticFrequency() const
{
    return vl_svm_get_diagnostic_frequency(this->svm);
}

vl_size VlFeatWrapper::SVMSolver::getModelDimension() const
{
    return vl_svm_get_dimension(this->svm);
}

vl_size VlFeatWrapper::SVMSolver::getSampleCount() const
{
    return vl_svm_get_num_data(this->svm);
}

VlSvmSolverType VlFeatWrapper::SVMSolver::getType() const
{
    return vl_svm_get_solver(this->svm);
}

double const * VlFeatWrapper::SVMSolver::getScores() const
{
    return vl_svm_get_scores(this->svm);
}

VlSvmStatistics const * VlFeatWrapper::SVMSolver::getStatistics() const
{
    return vl_svm_get_statistics(this->svm);
}

double const * VlFeatWrapper::SVMSolver::getWeights() const
{
    return vl_svm_get_weights(this->svm);
}

cv::Mat1d VlFeatWrapper::SVMSolver::predict(cv::Mat1d features) const
{
    cv::Mat1d model = getModelMat();
    double bias = getBias();

    cv::Mat1d results = model*(features.t())+bias;

    return results.t();
}

double VlFeatWrapper::SVMSolver::getBias() const
{
    return vl_svm_get_bias(this->svm);
}

double VlFeatWrapper::SVMSolver::getBiasMultiplier() const
{
    return vl_svm_get_bias_multiplier(this->svm);
}
