//
// Created by Simon Hofmann on 19.11.15.
//


#pragma once

#include "../pipeline/ConfigContainer.h"

namespace pl {


/**
 * @brief The SiftConfigContainer class
 */
class SiftDetectorConfig : public ConfigContainer {
public:
    /**
     * @brief SiftConfigContainer
     * @param nBestFeatures
     * @param nOctaveLayers
     * @param contrastThreshold
     * @param edgeThreshold
     * @param sigma
     */
    SiftDetectorConfig(const std::string &identifier,
                       int32_t nBestFeatures = 0,
                       int32_t nOctaveLayers = 3,
                       double contrastThreshold = 0.04,
                       double edgeThreshold = 10,
                       double sigma = 1.6,
                       bool augment = true);

    /**
     * @brief ~SiftConfigContainer
     */
    virtual ~SiftDetectorConfig();

    virtual std::string toString() const;

    virtual bool fromJSON(std::string &file);

    int32_t bestFeatures() const;
    bool setBestFeatures(int32_t bestFeatures);

    int32_t octaves() const;
    bool setOctaves(int32_t octaves);

    double contrastThresh() const;
    bool setContrastThresh(double contrastThresh);

    double edgeThresh() const;
    bool setEdgeThresh(double edgeThresh);

    double sigma() const;
    bool setSigma(double sigma);

private:
    /**
     * @brief mBestFeatures
     */
    int32_t mBestFeatures;

    /**
     * @brief mOctaves
     */
    int32_t mOctaves;

    /**
     * @brief mContrastThresh
     */
    double mContrastThresh;

    /**
     * @brief mEdgeThresh
     */
    double mEdgeThresh;

    /**
     * @brief mSigma
     */
    double mSigma;
};


}
