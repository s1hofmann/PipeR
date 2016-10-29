#pragma once

#include <opencv2/core/core.hpp>
#include "../pipeline/globals.h"

namespace pl {

class Platt {
public:
    Platt();
    virtual ~Platt();

    // From: Lin et al. "A Note on Platt's Probabilistic Outputs for Support Vector Machines"
    static std::pair<double, double> platt_calibrate(const cv::Mat1d decision,
                                                     const cv::Mat1i labels);

    static double sigmoid_predict(double decision_value,
                                  double A,
                                  double B);
};

}
