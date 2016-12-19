#include "encodingmethod.h"

EncodingMethod::EncodingMethod()
{
}

EncodingMethod::~EncodingMethod()
{

}

cv::Mat1b EncodingMethod::assign(const cv::Mat &data,
                                 const cv::Mat &means)
{
    cv::Mat1b assignmentMap = cv::Mat1b::zeros(means.rows, data.rows);

    cv::BFMatcher matcher;
    std::vector<cv::DMatch> assignments;

    matcher.match(data, means, assignments);

    for(size_t i = 0; i < assignments.size(); ++i) {
        assignmentMap.at<uchar>(assignments[i].trainIdx, assignments[i].queryIdx) = 1;
    }

    return assignmentMap;
}

void EncodingMethod::normalizeData(cv::Mat &data,
                                   normStrategy normType)
{
    switch (normType) {
    case NORM_MASS:
        if(data.cols > 0) {
            data /= data.cols;
        }
        break;

    case NORM_SSR:
        // according to the OpenCV docs this uses signed square root
        cv::pow(data, 0.5, data);
        break;

    case NORM_COMPONENT_L2:
        data += std::nextafter(0.0, 1.0);
        cv::normalize(data, data);
        break;

    case NORM_GLOBAL_L2:
        data += std::nextafter(0.0, 1.0);
        cv::normalize(data, data);
        break;

    default:
        std::stringstream s;
        s << "Unknown normalization method: " << std::endl;
        throw pl::EncodingError(s.str(), currentMethod, currentLine);
    }
}
