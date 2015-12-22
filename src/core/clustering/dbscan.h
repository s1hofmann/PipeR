#pragma once

#include <vector>
#include <set>
#include <unordered_map>
#include <opencv2/core/core.hpp>

namespace puhma {


class DbScan
{
public:
    DbScan();

    std::vector<std::set<int>> cluster(const cv::Mat1f &data,
                                       const int minPoints,
                                       const int neighborhoodSize = -1);

private:
    std::set<int> queryNeighborhood(int centerIdx);

    void expandCluster(int currentIdx,
                       std::set<int> &neighboringPoints,
                       double neighborhoodSize,
                       int clusterIdx,
                       int minPoints);

    bool isAssigned(const int idx);
    void assign(const int idx);

    bool isNoise(const int idx);
    void setNoise(const int idx);

    bool isVisited(const int idx);
    void setVisited(const int idx);

    void init(const double neighborhoodSize);

    double estimate(const cv::Mat &input);

    std::unordered_map<int, std::set<int>> distanceMatrix;

    std::vector<std::set<int>> clusters;

    cv::Mat1f mData;
    std::unordered_map<int, int> visited;
    std::unordered_map<int, int> noise;
    std::unordered_map<int, int> alreadyAssigned;
};


}
