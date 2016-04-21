#pragma once

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <vector>
#include <string>

class ClusterMethod
{
public:
    ClusterMethod(){}
    virtual ~ClusterMethod(){}

    /**
     * @brief cluster: Perform clustering
     */
    virtual void cluster(cv::Mat data,
                         int clusters,
                         int maxIterations = 100,
                         double epsilon = 0.001) = 0;

    /**
     * @brief dump: Write clustering result to *.yml or *.xml file
     * @param filename: Path to *.yml or *.xml file
     * @return
     */
    virtual int dump(const std::string & path) = 0;

    /**
     * @brief load: Load cluster data from a *.yml or *.xml file
     * @param path: Absolute path to *.yml or *.xml file
     * @return
     */
    virtual int load(const std::string & path) = 0;

    std::vector<cv::Mat1f> getParams() const {
        return params;
    }

protected:
    std::vector<cv::Mat1f> params;
};
