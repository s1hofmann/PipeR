//
// Created by Simon Hofmann on 18.11.15.
//


#pragma once

#include "EncodingStep.h"
#include "VladConfig.h"
#include "descriptorpyramid.h"

#include "../core/clustering/kmeanscluster.h"
#include "../core/encoding/vladencoder.h"


namespace pl {


class VladEncodingStep : public EncodingStep {
public:
    VladEncodingStep(const cv::Ptr<ConfigContainer> config);

    virtual ~VladEncodingStep();

    /**
     * @brief runImpl
     * @param debugMode
     * @param input
     * @param param
     * @return
     */
    virtual cv::Mat runImpl(const bool debugMode, const cv::Mat &input, const cv::Mat &param) const;

    /**
     * @brief trainImpl
     * @param debugMode
     * @param input
     * @param param
     * @return
     */
    virtual cv::Mat trainImpl(const bool debugMode, const cv::Mat &input, const cv::Mat &param) const;

private:
    cv::Mat encode(const std::string &encoder, const cv::Mat &data) const;

    cv::Mat encodePyramid(const std::string &encoder, const cv::Mat &data) const;
};


}

