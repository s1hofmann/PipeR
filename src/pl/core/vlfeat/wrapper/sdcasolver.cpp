#include "sdcasolver.h"

VlFeatWrapper::SDCASolver::SDCASolver(cv::Mat1d &data, cv::Mat1d &labels, double lambda)
    :
        SVMSolver(VlSvmSolverSdca,
                  data,
                  labels,
                  lambda)
{
}

VlFeatWrapper::SDCASolver::~SDCASolver()
{
}
