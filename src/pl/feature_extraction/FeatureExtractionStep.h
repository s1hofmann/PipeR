//
// Created by Simon Hofmann on 16.11.15.
//


#pragma once

#include "../pipeline/PipelineStep.h"


namespace pl {


/**
 * @brief The FeatureExtractionStep class
 */
class FeatureExtractionStep : public PseudoPipelineStep {
public:
    /**
     * @brief train
     * @param input
     * @param param
     * @return
     */
    virtual cv::Mat compute(const cv::Mat &input,
                            std::vector<cv::KeyPoint> &keypoints) const {
        return cv::Mat();
    }

    /**
     * @brief compute
     * @param input
     * @return
     */
    virtual cv::Mat compute(const cv::Mat &input,
                            const cv::Mat &mask) const {
        return cv::Mat();
    }

    /**
     * @brief debugCompute
     * @param input
     * @param keypoints
     * @return
     */
    virtual cv::Mat debugCompute(const cv::Mat &input,
                                 std::vector<cv::KeyPoint> &keypoints) const {
        return cv::Mat();
    }

    /**
     * @brief debugCompute
     * @param input
     * @return
     */
    virtual cv::Mat debugCompute(const cv::Mat &input,
                                 const cv::Mat &mask) const {
        return cv::Mat();
    }

protected:
    /**
     * @brief FeatureExtractionStep
     * @param config
     * @param info
     */
    FeatureExtractionStep(const cv::Ptr<ConfigContainer> config);

    /**
     * @brief ~FeatureExtractionStep
     */
    virtual ~FeatureExtractionStep();

    cv::Mat augment(cv::Mat &descriptor, std::vector<cv::KeyPoint> &keypoints) const;

private:
    std::vector<std::string> cvExtractors = {
        "FAST",
        "STAR",
        "SIFT",
        "SURF",
        "ORB",
        "BRISK",
        "MSER",
        "GFTT",
        "HARRIS",
        "Dense",
        "SimpleBlob"
    };
};


}

