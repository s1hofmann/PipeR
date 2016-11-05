#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "../utils/scalespace.h"


namespace pl {


class VesselFilter {
public:
    /**
     * @brief VesselFilter
     * @param sigma: Initial sigma value for blurring
     * @param octaves: Amount of octaves for scale space
     * @param stages: Amount of substages for scale space
     */
    VesselFilter(const double mSigma = 1,
                 const int32_t mOctaves = 3,
                 const int32_t mStages = 3);

    /**
    * @brief compute: Computes a combined probability map for vessels using a Gaussian scale space
    * @param input: Image to process
    * @param beta: Scale factor for blobness measure
    * @param c: Scale factor for structureness measure
    * @return: Probability map
    */
    cv::Mat compute(const cv::Mat &input,
                    const double beta = 0.5,
                    const double c = 15,
                    const cv::Mat &mask = cv::Mat()) const;

private:
    /**
    * @brief computeHessian: Computes hessian of input
    * @param input: Image to compute hessian for
    * @param dxx: Return parameter, second order partial derivative in x direction
    * @param dyy: Return parameter, second order partial derivative in y direction
    * @param dxy: First order partial derivative in x and y direction
    */
    void computeHessian(const cv::Mat &input,
                        cv::Mat &mDxx,
                        cv::Mat &mDyy,
                        cv::Mat &dxy) const;

    /**
    * @brief computeEigen: Returns both eigenvalues (value1 > value2) and the larger eigenvector.
    * @param input: Input image
    * @param value1: Return parameter, eigenvalue1
    * @param value2: Return parameter, eigenvalue2
    * @param xCoords: Return parameter, x component of larger eigenvector
    * @param yCoords: Return parameter, y component of larger eigenvector
    */
    void computeEigen(const cv::Mat &input,
                      cv::Mat1f &value1,
                      cv::Mat1f &value2,
                      cv::Mat1f &xCoords,
                      cv::Mat1f &yCoords) const;

    /**
    * @brief computeVesselness: Returns a probability map which indicates probability for vessels
    * @param lambda1: Matrix holding larger eigenvalues
    * @param lambda2: Matrix holding smaller eigenvalues
    * @param c: Scaling for blobness measure
    * @param beta: Scaling for structureness measure
    * @return: Vessel probability map
    */
    cv::Mat1f computeVesselness(cv::Mat1f &lambda1,
                                const cv::Mat1f &lambda2,
                                const float_t c,
                                const float_t beta) const;

/**
* DATA
*/
private:
    double mSigma;
    int32_t mOctaves;
    int32_t mStages;

    cv::Mat mDxx, mDyy, mDx, mDy;
    cv::Mat mId;
};


/**
* @brief The Frangi class Vesselness measure as proposed by Frangi et al
*/
class Frangi {
public:
    /**
    * @brief computeVesselness Computes vessel probability based on lambda1 and lambda2, where lambda1 > lambda2
    * @param lambda1 Eigenvalue 1
    * @param lambda2 Eigenvalue 2
    * @param p1 beta value
    * @param p2 c value
    * @return Probability map indicating possible vessels
    */
    static cv::Mat1f computeVesselness(cv::Mat1f &lambda1,
                                       const cv::Mat1f &lambda2,
                                       const float_t p1,
                                       const float_t p2);
};


/**
* @brief The Sato class Vesselness measure as proposed by Sato et al
*/
class Sato {
public:
    /**
    * @brief computeVesselness
    * @param lambda1
    * @param lambda2
    * @param p1
    * @param p2
    * @return
    */
    static cv::Mat1f computeVesselness(cv::Mat1f &lambda1,
                                       const cv::Mat1f &lambda2,
                                       const float_t p1,
                                       const float_t p2);
};


}
