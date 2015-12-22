#pragma once

#include "clustermethod.h"
#include <iostream>

class KMeansCluster : public ClusterMethod
{
public:
    virtual ~KMeansCluster() {}

    virtual void cluster(cv::Mat1f data,
                         int clusters,
                         int maxIterations = 100,
                         double epsilon = 0.001);

    virtual int dump(const std::string & file_name);
    virtual int load(const std::string & file_name);

    static ClusterMethod * create(void) {
        return new KMeansCluster();
    }

private:
    KMeansCluster() {}
};
