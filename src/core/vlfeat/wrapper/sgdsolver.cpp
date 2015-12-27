#include "sgdsolver.h"


VlFeatWrapper::SGDSolver::SGDSolver(cv::Mat1d &data,
        cv::Mat1d &labels,
        double lambda)
    : SVMSolver(VlSvmSolverSgd, data, labels, lambda)
{
}

void VlFeatWrapper::SGDSolver::setBiasLearningRate(const double rate)
{
    CV_Assert(rate > 0);
    vl_svm_set_bias_learning_rate(this->svm, rate);
}

double VlFeatWrapper::SGDSolver::getBiasLearningRate() const
{
    return vl_svm_get_bias_learning_rate(this->svm);
}

void VlFeatWrapper::SGDSolver::setModel(const cv::Mat &model)
{
    if(!model.type() == CV_64F) {
        cv::Mat1d m;
        model.convertTo(m, CV_64F);
        CV_Assert(m.isContinuous());
        vl_svm_set_model(this->svm, reinterpret_cast<double*>(m.data));
    } else {
        CV_Assert(model.isContinuous());
        vl_svm_set_model(this->svm, reinterpret_cast<double*>(model.data));
    }
}

void VlFeatWrapper::SGDSolver::setBias(const double bias)
{
    vl_svm_set_bias(this->svm, bias);
}

VlFeatWrapper::SGDSolver::~SGDSolver()
{
}
