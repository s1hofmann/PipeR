#pragma once

#include <vector>
#include <set>
#include <unordered_map>
#include <opencv2/core/core.hpp>


class DbScan
{
public:
    DbScan();

    std::vector<std::set<int32_t>> cluster(const cv::Mat1f &data,
                                       const int32_t minPoints,
                                       const int32_t neighborhoodSize = -1);

private:
    std::set<int32_t> queryNeighborhood(int32_t centerIdx);

    void expandCluster(int32_t currentIdx,
                       std::set<int32_t> &neighboringPoints,
                       double neighborhoodSize,
                       int32_t clusterIdx,
                       int32_t minPoints);

    bool isAssigned(const int32_t idx);
    void assign(const int32_t idx);

    bool isNoise(const int32_t idx);
    void setNoise(const int32_t idx);

    bool isVisited(const int32_t idx);
    void setVisited(const int32_t idx);

    void init(const double neighborhoodSize);

    double estimate(const cv::Mat &input);

    std::unordered_map<int32_t, std::set<int32_t>> distanceMatrix;

    std::vector<std::set<int32_t>> clusters;

    cv::Mat1f mData;
    std::unordered_map<int32_t, int32_t> visited;
    std::unordered_map<int32_t, int32_t> noise;
    std::unordered_map<int32_t, int32_t> alreadyAssigned;
};

