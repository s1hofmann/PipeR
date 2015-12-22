#pragma once

#include "clustermethod.h"
#include <iostream>

class KMeansCluster : public ClusterMethod
{
public:
    KMeansCluster() {}
    virtual ~KMeansCluster() {}

    virtual void cluster(cv::Mat data,
                         int clusters,
                         int maxIterations = 100,
                         double epsilon = 0.001);

    virtual int dump(const std::string & file_name);
    virtual int load(const std::string & file_name);

private:
};
