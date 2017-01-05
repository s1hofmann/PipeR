#include "metrics.h"
#include <iostream>


namespace pl {


Metrics::Metrics()
{

}

uint32_t Metrics::truePositives(const cv::Mat1d predictions, const cv::Mat1d labels)
{
    cv::Mat intPredictions, intLabels;
    predictions.convertTo(intPredictions, CV_32FC1);
    labels.convertTo(intLabels, CV_32FC1);
    double negativeLabel, positiveLabel;
    cv::minMaxIdx(intLabels, &negativeLabel, &positiveLabel, NULL, NULL);
    cv::Mat1b tp = cv::Mat1b::zeros(predictions.size());
    tp.setTo(1, intPredictions == intLabels);
    tp.setTo(0, intPredictions == static_cast<int>(negativeLabel));

    return cv::countNonZero(tp);
}

uint32_t Metrics::falsePositives(const cv::Mat1d predictions, const cv::Mat1d labels)
{
    cv::Mat intPredictions, intLabels;
    predictions.convertTo(intPredictions, CV_32FC1);
    labels.convertTo(intLabels, CV_32FC1);
    double negativeLabel, positiveLabel;
    cv::minMaxIdx(intLabels, &negativeLabel, &positiveLabel, NULL, NULL);
    cv::Mat1b tp = cv::Mat1b::zeros(predictions.size());
    tp.setTo(1, intPredictions != intLabels);
    tp.setTo(0, intPredictions == static_cast<int>(negativeLabel));

    return cv::countNonZero(tp);
}

uint32_t Metrics::trueNegatives(const cv::Mat1d predictions, const cv::Mat1d labels)
{
    cv::Mat intPredictions, intLabels;
    predictions.convertTo(intPredictions, CV_32FC1);
    labels.convertTo(intLabels, CV_32FC1);
    double negativeLabel, positiveLabel;
    cv::minMaxIdx(intLabels, &negativeLabel, &positiveLabel, NULL, NULL);
    cv::Mat1b tp = cv::Mat1b::zeros(predictions.size());
    tp.setTo(1, intPredictions == intLabels);
    tp.setTo(0, intPredictions == static_cast<int>(positiveLabel));

    return cv::countNonZero(tp);
}

uint32_t Metrics::falseNegatives(const cv::Mat1d predictions, const cv::Mat1d labels)
{
    cv::Mat intPredictions, intLabels;
    predictions.convertTo(intPredictions, CV_32FC1);
    labels.convertTo(intLabels, CV_32FC1);
    double negativeLabel, positiveLabel;
    cv::minMaxIdx(intLabels, &negativeLabel, &positiveLabel, NULL, NULL);
    cv::Mat1b tp = cv::Mat1b::zeros(predictions.size());
    tp.setTo(1, intPredictions != intLabels);
    tp.setTo(0, intPredictions == static_cast<int>(positiveLabel));

    return cv::countNonZero(tp);
}

double Metrics::precision(const cv::Mat1d predictions, const cv::Mat1d labels)
{
    uint32_t tp = truePositives(predictions, labels);
    uint32_t fp = falsePositives(predictions, labels);

    return tp / static_cast<double>(tp + fp);
}

double Metrics::recall(const cv::Mat1d predictions, const cv::Mat1d labels)
{
    uint32_t tp = truePositives(predictions, labels);
    uint32_t fn = falseNegatives(predictions, labels);

    return tp / static_cast<double>(tp + fn);
}

double Metrics::f1(const cv::Mat1d predictions, const cv::Mat1d labels)
{
    double p = precision(predictions, labels);
    double r = recall(predictions, labels);

    if(p + r != 0) {
        return 2 * (p * r) / (p + r);
    }
    return 0;
}


}
