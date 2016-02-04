#pragma once
#ifndef SGDSOLVER_H
#define SGDSOLVER_H

#include "svm_solver.h"

namespace VlFeatWrapper
{

class SGDSolver : public SVMSolver
{
public:
    SGDSolver(cv::Mat1d &data, cv::Mat1d &labels, double lambda);
    virtual ~SGDSolver();

    /**
     * @brief setBiasLearningRate: Sets the bias lerning rate
     * @param rate: Learning rate as double value.
     */
    void setBiasLearningRate(double rate);

    /**
     * @brief getBiasLearningRate: Return the bias learning rate of the SVM.
     * @return: Bias learning rate as double value.
     */
    double getBiasLearningRate() const;

    /**
     * @brief setModel: Sets the training model to warm start an SGD training.
     * @param model: Model data as cv::Mat
     */
    void setModel(const cv::Mat &model);

    /**
     * @brief setBias: Set new bias value. Used for warm starting training
     * @param bias: New value
     */
    void setBias(const double bias);

    //TODO wrap setWeights
};

}
#endif

