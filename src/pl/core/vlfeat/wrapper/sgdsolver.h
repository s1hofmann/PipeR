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

};

}
#endif

