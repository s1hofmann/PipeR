#pragma once

#include <string>
#include <set>
#include <iostream>
#include <cmath>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "../../exception/EncodingError.h"
#include "../../pipeline/globals.h"

enum normStrategy {
    NORM_GLOBAL_L2=1,
    NORM_SSR=2,
    NORM_COMPONENT_L2=4,
    NORM_MASS=8
};

/**
 * @brief The EncodingMethod class: A base class which specific encoding methods can be derived from.
 */
class EncodingMethod
{
public:
    virtual ~EncodingMethod();

    /**
     * @brief encode Actual encoding method the VLAD encoding implements
     * @param data {@link cv::Mat} data to encode.
     * @return {@link cv::Mat1f} containing encoded data.
     */
    virtual cv::Mat encode(const cv::Mat &data) = 0;

    /**
     * @brief loadData Method to load neccessary data to perfom encoding. (e.g. clustering data for VLAD encoding).
     * @param fileName {@link std::string} absolute filename of a *.yml file to load data from.
     */
    virtual void loadData(const std::string &fileName) = 0;

    void setNormStrategy(std::vector<normStrategy> &normTypes) {
        mNormType = 0;
        for(auto norm : normTypes) {
            mNormType += static_cast<int>(pow(2.0, static_cast<double>(norm)));
        }
    }

    /**
     * @brief assign Creates an assignment matrix which maps data points to their cluster centers
     * @param data {@link cv::Mat} row-wise data points
     * @param means {@link cv::Mat} row-wise cluster centers
     * @return {@link cv::Mat1b} assignment matrix
     */
    cv::Mat1b assign(const cv::Mat &data,
                     const cv::Mat &means);

    /**
     * @brief normalizeData Normalize data using given NormStrategy type
     * @param data {@link cv::Mat1f} data to normalize
     * @param normType {@link normStrategy} normalization method
     */
    void normalizeData(cv::Mat &data, normStrategy normType);

protected:
    EncodingMethod();
    int mNormType;
};
