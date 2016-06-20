#pragma once

#include "../../pipeline/globals.h"
#include "../../exception/error.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#ifdef USE_TBB
#include <tbb/parallel_for.h>
#endif


/**
 * @brief The RPCA class: PCA with (optional) whitening
 */
class RPCA
{
public:
    RPCA(int n_components=0,
         bool whiten=true,
         float reg=0.001);
    /// construct from saved RPCA
    explicit RPCA(const std::string & path);
    ~RPCA(){}

    /// fit the PCA on the data
    void fit(const cv::Mat1f & descr);
    /// transform the data using this RPCA
    void transform(const cv::Mat1f & descr,
                   cv::Mat1f & out) const;

    /// dump rpca data fields
    void dump(const std::string & path);
    /// load rpca data fields
    void load(const std::string & path);

    bool hasData() const { return this->dataLoaded; }

private:
    /// whiten the data
    /// --> bring covariance matrix to unit
    bool whiten;
    /// number of components
    int n_components;
    /// regularizer on the eigenvalues
    float reg;

    /// mean of the data
    cv::Mat1f mean;
    /// the transformation matrix
    cv::Mat1f components;
    /// explained variance
    cv::Mat1f variance;

    bool dataLoaded = false;
};
