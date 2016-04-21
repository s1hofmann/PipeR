#pragma once
#ifndef SDCA_SOLVER_H
#define SDCA_SOLVER_H

#include "svm_solver.h"

namespace VlFeatWrapper
{

class SDCASolver : public SVMSolver
{
public:
    SDCASolver(cv::Mat1d &data, cv::Mat1d &labels, double lambda);
    virtual ~SDCASolver();
};

}
#endif
