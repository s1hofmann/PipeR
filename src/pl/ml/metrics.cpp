#include "metrics.h"


namespace pl {


Metrics::Metrics()
{

}

unsigned int Metrics::truePositives(const cv::Mat1d predictions, const cv::Mat1d labels)
{
    double negativeLabel, positiveLabel;
    cv::minMaxIdx(labels, &negativeLabel, &positiveLabel, NULL, NULL);
    cv::Mat1b tp = cv::Mat1b::zeros(predictions.size());
    tp.setTo(1, predictions == labels);
    tp.setTo(0, predictions == negativeLabel);

    return cv::countNonZero(tp);
}

unsigned int Metrics::falsePositives(const cv::Mat1d predictions, const cv::Mat1d labels)
{
    double negativeLabel, positiveLabel;
    cv::minMaxIdx(labels, &negativeLabel, &positiveLabel, NULL, NULL);

    cv::Mat1b tp = cv::Mat1b::zeros(predictions.size());
    tp.setTo(1, predictions != labels);
    tp.setTo(0, predictions == negativeLabel);

    return cv::countNonZero(tp);
}

unsigned int Metrics::trueNegatives(const cv::Mat1d predictions, const cv::Mat1d labels)
{
    double negativeLabel, positiveLabel;
    cv::minMaxIdx(labels, &negativeLabel, &positiveLabel, NULL, NULL);

    cv::Mat1b tp = cv::Mat1b::zeros(predictions.size());
    tp.setTo(1, predictions == labels);
    tp.setTo(0, predictions == positiveLabel);

    return cv::countNonZero(tp);
}

unsigned int Metrics::falseNegatives(const cv::Mat1d predictions, const cv::Mat1d labels)
{
    double negativeLabel, positiveLabel;
    cv::minMaxIdx(labels, &negativeLabel, &positiveLabel, NULL, NULL);

    cv::Mat1b tp = cv::Mat1b::zeros(predictions.size());
    tp.setTo(1, predictions != labels);
    tp.setTo(0, predictions == positiveLabel);

    return cv::countNonZero(tp);
}

double Metrics::precision(const cv::Mat1d predictions, const cv::Mat1d labels)
{
    double tp = truePositives(predictions, labels);
    double fp = falsePositives(predictions, labels);

    return tp / (tp + fp);
}

double Metrics::recall(const cv::Mat1d predictions, const cv::Mat1d labels)
{
    double tp = truePositives(predictions, labels);
    double fn = falseNegatives(predictions, labels);

    return tp / (tp + fn);
}

double Metrics::f1(const cv::Mat1d predictions, const cv::Mat1d labels)
{
    double p = precision(predictions, labels);
    double r = recall(predictions, labels);

    return 2 * (p * r) / (p + r);
}


}
