#pragma once
#ifndef SVM_SOLVER_H
#define SVM_SOLVER_H

extern "C" {
    #include "../vl/svm.h"
}

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace VlFeatWrapper
{

class SVMSolver
{
public:
    virtual ~SVMSolver();

    /**
     * @brief setEpsilon: Set new value for convergence threshold.
     * @param epsilon: New threshold value as double.
     */
    void setEpsilon(double epsilon);

    void setWeights(cv::Mat &weights);

    /**
     * @brief getEpsilon: Get the convergence threshold.
     * @return: Convergence threshold as double.
     */
    double getEpsilon() const;

    /**
     * @brief getBias: Get the bias value.
     * @return: Bias value as double.
     */
    double getBias() const;

    /**
     * @brief setBias
     * @param bias
     */
    void setBias(const double bias);

    /**
     * @brief getBiasLearningRate
     * @return
     */
    double getBiasLearningRate() const;

    /**
     * @brief setBiasLearningRate
     * @param rate
     */
    void setBiasLearningRate(const double rate);

    /**
     * @brief getBiasMultiplier: Get the bias multiplier.
     * @return: Multiplier value as double.
     */
    double getBiasMultiplier() const;

    /**
     * @brief setBiasMultiplier: Sets new value for bias multiplier.
     * @param bias: New multiplier value as double.
     */
    void setBiasMultiplier(double bias);

    /**
     * @brief setMaxIterations: Sets new value for max. iterations
     * @param max: New value
     */
    void setMaxIterations(int32_t max);

    /**
     * @brief getMaxIterations: Get max iterations count.
     * @return
     */
    vl_size getMaxIterations() const;

    /**
     * @brief setStartIterationCount: Sets initial iteration count for a warm start
     * @param count: Iteration count
     * @return
     */
    void setStartIterationCount(const vl_size count) const;

    /**
     * @brief getIterationCount: Returns the initial iteration value for a warm start
     */
    vl_size getIterationCount() const;

    /**
     * @brief getCurrentIterationCount: Get index of current iteration step.
     * @return
     */
    vl_size getCurrentIterationCount() const;

    /**
     * @brief getModel: Get the weight vector w.
     * @return
     */
    double const * getModel() const;

    /**
     * @brief getModelMat: Get the weight vector w as cv::Mat1d.
     * @return
     */
    cv::Mat1d getModelMat() const;

    /**
     * @brief getDiagnosticFrequency: Diagnostic frequency.
     * @return
     */
    double getDiagnosticFrequency() const;

    /**
     * @brief getModelDimension: Get no. of model columns.
     * @return
     */
    vl_size getModelDimension() const;

    /**
     * @brief getSampleCount: Get no. of model rows.
     * @return
     */
    vl_size getSampleCount() const;

    /**
     * @brief getType: Get the SVM solver type.
     * @return
     */
    VlSvmSolverType getType() const;

    /**
     * @brief getScores: Get the scores of the data points.
     * @return
     */
    double const * getScores() const;

    /**
     * @brief getStatistics: Get the solver statistics.
     * @return
     */
    VlSvmStatistics const * getStatistics() const;

    /**
     * @brief getWeights: Get the data weights.
     * @return
     */
    double const * getWeights() const;

    /**
     * @brief getWeightMat: Return weights as \link{cv::Mat1d} object
     * @return
     */
    cv::Mat1d getWeightMat() const;

    /**
     * @brief predict: Make a prediction based on a trained model.
     * @param features: Data to predict
     * @return
     */
    cv::Mat1d predict(cv::Mat1d features) const;

    /**
     * @brief train: Run the SVM solver.
     */
    void train();

    void setModel(const cv::Mat &model);
protected:
    SVMSolver(VlSvmSolverType type, cv::Mat1d &data, cv::Mat1d &labels, double lambda);
    VlSvm *svm;
};

}
#endif
