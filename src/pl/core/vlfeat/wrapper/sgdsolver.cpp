#include "sgdsolver.h"


VlFeatWrapper::SGDSolver::SGDSolver(cv::Mat1d &data,
        cv::Mat1d &labels,
        double lambda)
    : SVMSolver(VlSvmSolverSgd, data, labels, lambda)
{
}

VlFeatWrapper::SGDSolver::~SGDSolver()
{

}
