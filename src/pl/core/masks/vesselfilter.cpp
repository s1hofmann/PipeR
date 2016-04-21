#include "vesselfilter.h"
#include <iostream>

namespace pl {


VesselFilter::VesselFilter(const double sigma,
                           const int octaves,
                           const int stages) {
    this->mSigma = sigma;
    this->mOctaves = octaves;
    this->mStages = stages;

    cv::getDerivKernels(this->mDxx, this->mDyy, 2, 2, 3);
    cv::getDerivKernels(this->mDx, this->mDy, 1, 1, 3);
    this->mId = (cv::Mat1i(3, 1) << 0, 1, 0);
}


cv::Mat VesselFilter::compute(const cv::Mat &input,
                              const double beta,
                              const double c,
                              const cv::Mat &mask) const {
    cv::Mat workingCopy;
    if(input.channels() > 1) {
        cv::cvtColor(input, workingCopy, cv::COLOR_BGR2GRAY);
    } else {
        workingCopy = input;
    }

    GaussianScaleSpace sp(this->mOctaves, this->mStages, this->mSigma);
    std::vector<cv::Mat> scales;
    sp.compute(workingCopy, scales);

    std::vector<cv::Mat1f> filtered;
    filtered.resize(scales.size());

    int oct = 0;
    int st = 0;

    cv::Mat combined;

    for (size_t i = 0; i < scales.size(); ++i) {
        cv::Mat1f eigenValue1, eigenValue2, eigenVectorX, eigenVectorY;
        computeEigen(scales[i], eigenValue1, eigenValue2, eigenVectorX, eigenVectorY);
        filtered[i] = computeVesselness(eigenValue1, eigenValue2, c, beta);

        cv::Mat1f angles;
        cv::phase(eigenVectorX, eigenVectorY, angles);

        //Upscaling factor
        double scale = sp.getScaleFactor(oct, st);

        cv::resize(filtered[i], filtered[i], workingCopy.size(), scale, scale, cv::INTER_NEAREST);

        ++st;
        if (st % this->mStages == 0) {
            ++oct;
            st = 0;
        }
    }

    filtered[0].copyTo(combined);
    for (int i = 1; i < filtered.size(); ++i) {
        combined = cv::max(combined, filtered[i]);
    }

    //Discard all elements which are masked out
    if (!mask.empty()) {
        combined.setTo(0, mask == 0);
    }

    return combined;
}


void VesselFilter::computeHessian(const cv::Mat &input,
                                  cv::Mat &dxx,
                                  cv::Mat &dyy,
                                  cv::Mat &dxy) const {
                                                  cv::sepFilter2D(input, dxx, -1, this->mDxx, this->mId);
                                                  cv::sepFilter2D(input, dyy, -1, this->mId, this->mDyy);
                                                  cv::sepFilter2D(input, dxy, -1, this->mDx, this->mDy);
                                                  }


void VesselFilter::computeEigen(const cv::Mat &input,
                                cv::Mat1f &value1,
                                cv::Mat1f &value2,
                                cv::Mat1f &xCoords,
                                cv::Mat1f &yCoords) const {
                                                      cv::Mat dxx, dyy, dxy;

                                                      computeHessian(input, dxx, dyy, dxy);

                                                      dxx.convertTo(dxx, CV_32FC1);
                                                      dyy.convertTo(dyy, CV_32FC1);
                                                      dxy.convertTo(dxy, CV_32FC1);

                                                      cv::Mat1f difference;
                                                      cv::subtract(dxx, dyy, difference);
                                                      cv::Mat1f root;
                                                      cv::sqrt(difference.mul(difference) + 4 * dxy.mul(dxy), root);

                                                      //First eigenvector components
                                                      cv::Mat1f v2x = 2 * dxy;
                                                      cv::Mat1f v2y = dyy - dxx + root;

                                                      //Normalization
                                                      cv::Mat1f mag;
                                                      cv::sqrt(v2x.mul(v2x) + v2y.mul(v2y), mag);
                                                      cv::Mat1f tmp = v2x.mul(1.0 / mag);
                                                      tmp.copyTo(v2x, mag != 0);

                                                      tmp = v2y.mul(1.0 / mag);
                                                      tmp.copyTo(v2y, mag != 0);

                                                      //Second eigenvector components, orthogonal to the first one
                                                      cv::Mat1f v1x, v1y;
                                                      v1x = v2y.clone();
                                                      v1x *= -1;
                                                      v1y = v2x.clone();

                                                      //Eigenvalues
                                                      cv::Mat1f l1 = 0.5 * (dxx + dyy + root);
                                                      cv::Mat1f l2 = 0.5 * (dxx + dyy - root);

                                                      //Sort in DESCENDING order
                                                      cv::Mat1b check = cv::abs(l1) < cv::abs(l2);
                                                      l1.copyTo(value1);
                                                      l2.copyTo(value1, check);

                                                      l2.copyTo(value2);
                                                      l1.copyTo(value2, check);

                                                      v1x.copyTo(xCoords);
                                                      v2x.copyTo(xCoords, check);

                                                      v1y.copyTo(yCoords);
                                                      v2y.copyTo(yCoords, check);
                                                      }


cv::Mat1f VesselFilter::computeVesselness(cv::Mat1f &lambda1,
                                          const cv::Mat1f &lambda2,
                                          const float c,
                                          const float beta) const {
                                                              //Avoid division by 0
                                                              lambda1.setTo(std::nextafter(0.0, 1.0), lambda1 == 0);

                                                              cv::Mat1f q = lambda2.mul(1 / lambda1);
                                                              cv::Mat1f rb = q.mul(q);
                                                              cv::Mat1f s = lambda1.mul(lambda1) + lambda2.mul(lambda2);

                                                              cv::Mat1f blobness, structureness;

                                                              cv::exp(-rb / (2 * beta * beta), blobness);
                                                              cv::exp(-s / (2 * c * c), structureness);

                                                              cv::Mat1f result = blobness.mul(cv::Mat1f::ones(blobness.size()) - structureness);

                                                              result.setTo(0, lambda1 < 0);

                                                              return result;
                                                              }


cv::Mat1f Frangi::computeVesselness(cv::Mat1f &lambda1,
                                    const cv::Mat1f &lambda2,
                                    const float p1,
                                    const float p2) {
                                                //Avoid division by 0
                                                lambda1.setTo(std::nextafter(0.0, 1.0), lambda1 == 0);

                                                cv::Mat1f q = lambda2.mul(1 / lambda1);
                                                cv::Mat1f rb = q.mul(q);
                                                cv::Mat1f s = lambda1.mul(lambda1) + lambda2.mul(lambda2);

                                                cv::Mat1f blobness, structureness;

                                                cv::exp(-rb / (2 * p1 * p1), blobness);
                                                cv::exp(-s / (2 * p2 * p2), structureness);

                                                cv::Mat1f result = blobness.mul(cv::Mat1f::ones(blobness.size()) - structureness);

                                                result.setTo(0, lambda1 < 0);

                                                return result;
                                                }

cv::Mat1f Sato::computeVesselness(cv::Mat1f &lambda1,
                                  const cv::Mat1f &lambda2,
                                  const float p1,
                                  const float p2) {

}


}
