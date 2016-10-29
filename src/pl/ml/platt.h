#pragma once

#include <opencv2/core/core.hpp>

namespace pl {

// From: Lin et al. "A Note on Platt's Probabilistic Outputs for Support Vector Machines"
void platt_calibrate (const cv::Mat1d &decision,
                      const cv::Mat1i &labels,
                      double A,
                      double B);

double sigmoid_predict(double decision_value,
                       double A,
                       double B);

}
