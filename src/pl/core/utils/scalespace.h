#pragma once


#include <vector>
#include <opencv2/core/core.hpp>
#include "../../pipeline/globals.h"

namespace pl {


/**
 * @brief The ScaleSpace class
 */
class ScaleSpace {

public:
    /**
     * @brief ScaleSpace
     * @param _n_ocataves
     * @param _n_sublevels
     */
    ScaleSpace(int32_t octaves,
               int32_t sublevels)
        : mOctaves(octaves),
          mSublevels(sublevels)
    {

    }

    /**
     * @brief ~ScaleSpace
     */
    virtual ~ScaleSpace(){}

    /**
     * @brief compute
     * @param img
     * @param scales
     */
    virtual void compute(const cv::Mat & img,
                         std::vector<cv::Mat> & scales) = 0;

    /**
     * @brief getScaleFactor
     * @param o
     * @param s
     * @return
     */
    double getScaleFactor(int32_t o, int32_t s) const {
        return std::pow(2, o + (float_t) s / (float_t) mSublevels );
    }

protected:
    /**
     * @brief mOctaves
     */
    int32_t mOctaves;

    /**
     * @brief mSublevels
     */
    int32_t mSublevels;
};

/**
 * @brief The LinearScaleSpace class
 */
class LinearScaleSpace : public ScaleSpace
{
public:
    /**
     * @brief LinearScaleSpace
     * @param octaves
     * @param sublevels
     */
    LinearScaleSpace(int32_t octaves = 2,
                     int32_t sublevels = 3)
        : ScaleSpace(octaves, sublevels)
    {

    }

    /**
     * @brief compute
     * @param img
     * @param scales
     */
    void compute(const cv::Mat & img,
                 std::vector<cv::Mat> & scales);
};


/**
 * @brief The GaussianScaleSpace class
 */
class GaussianScaleSpace : public ScaleSpace
{
public:
    /**
     * @brief GaussianScaleSpace
     * @param octaves
     * @param sublevels
     * @param sigmaBase
     * @param scaleOctave
     * @param scaleSublevel
     */
    GaussianScaleSpace(int32_t octaves = 4,
                       int32_t sublevels = 3,
                       double sigmaBase = 1.6,
                       bool scaleOctave = true,
                       bool scaleSublevel = false)
        : ScaleSpace(octaves, sublevels),
          mSigmaBase(sigmaBase),
          mScaleOctave(scaleOctave),
          mScaleSublevel(scaleSublevel)
    {

    }

    /**
     * @brief compute
     * @param img
     * @param scales
     */
    void compute(const cv::Mat & img,
                 std::vector<cv::Mat> & scales);

private:
    /**
     * @brief mSigmaBase
     */
    double mSigmaBase;

    /**
     * @brief mScaleOctave
     */
    bool mScaleOctave;

    /**
     * @brief mScaleSublevel
     */
    bool mScaleSublevel;
};


}
