#include "scalespace.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>


namespace pl {


void LinearScaleSpace::compute(const cv::Mat & img,
                               std::vector<cv::Mat> & scales)
{
    for( int32_t o = 0; o < mOctaves; o++ ) {
        for( int32_t s = 0; s < mSublevels; s++ ) {
            double f = getScaleFactor(o, s);
            cv::Mat tmp;
            cv::resize(img, tmp, cv::Size(), 1.0/f, 1.0/f, cv::INTER_NEAREST);
            scales.push_back(tmp);
        }
    }
}

void GaussianScaleSpace::compute(const cv::Mat & img,
                                 std::vector<cv::Mat> & scales)
{
    for(int32_t o = 0; o < mOctaves; ++o) {
        for(int32_t s = 0; s < mSublevels; ++s) {
            double f = getScaleFactor(o, s);
            double sigma = mSigmaBase * f;
            cv::Mat tmp;
            cv::GaussianBlur(img, tmp, cv::Size(), sigma);

            if(((mScaleOctave && s) == 0) || mScaleSublevel) {
                try {
                    int32_t newHeight = static_cast<int32_t>(tmp.rows / f);
                    int32_t newWidth = static_cast<int32_t>(tmp.cols / f);
                    if(newHeight * newWidth <= 0) {
                        inform("Scalespace max. reached. Octave", o, "Sublevel:", s);
                        return;
                    }
                    cv::resize(tmp, tmp, cv::Size(), 1.0/f, 1.0/f, cv::INTER_NEAREST);
                } catch(cv::Exception) {
                    return;
                }
            }

            scales.push_back(tmp);
        }
    }
}


}
