#include "scalespace.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>


namespace pipe {


void LinearScaleSpace::compute(const cv::Mat & img,
                               std::vector<cv::Mat> & scales)
{
    for( int o = 0; o < n_octaves; o++ ) {
        for( int s = 0; s < n_sublevels; s++ ) {
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
    for( int o = 0; o < n_octaves; o++ ) {
        for( int s = 0; s < n_sublevels; s++ ) {
            double f = getScaleFactor(o, s);
            double sigma = sigma_base * f;
            cv::Mat tmp;
            cv::GaussianBlur(img, tmp, cv::Size(), sigma);

            if ( (scale_octave && s == 0)
                 || scale_sublevel){
                 cv::resize(tmp, tmp, cv::Size(), 1.0/f, 1.0/f, cv::INTER_NEAREST);
            }

            scales.push_back(tmp);
        }
    }
}


}
