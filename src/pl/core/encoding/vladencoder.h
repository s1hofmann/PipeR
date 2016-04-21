#pragma once

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"

#include "encodingmethod.h"
#include "../../pipeline/globals.h"
#include "../../exception/BaseError.h"

#include <unordered_map>

/**
 * @brief The VladEncoder class: Implements the Vector of Linearly Aggregated Descriptors
 */
class VladEncoder : public EncodingMethod
{
public:
    VladEncoder();
    virtual ~VladEncoder();

    /**
     * @brief loadData: Loads clustering data neccessary for encoding.
     * @param file_name: Absolute path to a *.yml file containing the data.
     */
    virtual void loadData(const std::string & fileName);

    /**
     * @brief encode: The actual encode method.
     * @param data: Data to encode.
     * @return cv::Mat1f containing encoded data.
     */
    virtual cv::Mat encode(const cv::Mat & data) override;

private:
    cv::Mat1f means;
};
