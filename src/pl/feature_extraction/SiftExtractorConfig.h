//
// Created by Simon Hofmann on 19.11.15.
//


#pragma once

#include "../pipeline/ConfigContainer.h"

namespace pl {


/**
 * @brief The SiftConfigContainer class
 */
class SiftExtractorConfig : public ConfigContainer {
public:
    /**
     * @brief SiftConfigContainer
     * @param nBestFeatures
     * @param nOctaveLayers
     * @param contrastThreshold
     * @param edgeThreshold
     * @param sigma
     */
    SiftExtractorConfig(const std::string &identifier,
                        int nBestFeatures = 0,
                        int nOctaveLayers = 3,
                        double contrastThreshold = 0.04,
                        double edgeThreshold = 10,
                        double sigma = 1.6,
                        bool augment = true);

    /**
     * @brief ~SiftConfigContainer
     */
    virtual ~SiftExtractorConfig();

    /**
     * @brief getBestFeatures
     * @return
     */
    inline int getBestFeatures() const {
        return mBestFeatures;
    }

    /**
     * @brief getOctaves
     * @return
     */
    inline int getOctaves() const {
        return mOctaves;
    }

    /**
     * @brief getContrastThresh
     * @return
     */
    inline double getContrastThresh() const {
        return mContrastThresh;
    }

    /**
     * @brief getEdgeThresh
     * @return
     */
    inline double getEdgeThresh() const {
        return mEdgeThresh;
    }

    /**
     * @brief getSigma
     * @return
     */
    inline double getSigma() const {
        return mSigma;
    }

    virtual std::string toString() const;

    virtual bool fromJSON(std::string &file);

    inline bool augment() const {
        return mAugment;
    }

    inline void setAugment(bool augment) {
        mAugment = augment;
    }

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

    /**
     * @brief mAugment
     */
    bool mAugment;
};


}
