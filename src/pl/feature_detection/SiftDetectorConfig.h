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
                       int nBestFeatures = 0,
                       int nOctaveLayers = 3,
                       double contrastThreshold = 0.04,
                       double edgeThreshold = 10,
                       double sigma = 1.6);

    /**
     * @brief ~SiftConfigContainer
     */
    virtual ~SiftDetectorConfig();

    /**
     * @brief getBestFeatures
     * @return
     */
    int getBestFeatures() const {
        return mBestFeatures;
    }

    /**
     * @brief getOctaves
     * @return
     */
    int getOctaves() const {
        return mOctaves;
    }

    /**
     * @brief getContrastThresh
     * @return
     */
    double getContrastThresh() const {
        return mContrastThresh;
    }

    /**
     * @brief getEdgeThresh
     * @return
     */
    double getEdgeThresh() const {
        return mEdgeThresh;
    }

    /**
     * @brief getSigma
     * @return
     */
    double getSigma() const {
        return mSigma;
    }

    virtual std::string toString() const;

    virtual bool fromJSON(std::string &file);

private:
    /**
     * @brief mBestFeatures
     */
    int mBestFeatures;

    /**
     * @brief mOctaves
     */
    int mOctaves;

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
