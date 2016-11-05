#pragma once

#include "clustermethod.h"
#include <iostream>

class KMeansCluster : public ClusterMethod
{
public:
    KMeansCluster() {}
    virtual ~KMeansCluster() {}

    virtual void cluster(cv::Mat data,
                         int32_t clusters,
                         int32_t maxIterations = 100,
                         double epsilon = 0.001);

    virtual int32_t dump(const std::string & file_name);
    virtual int32_t load(const std::string & file_name);

private:
};
