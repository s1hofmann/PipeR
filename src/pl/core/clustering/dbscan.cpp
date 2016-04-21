#include "dbscan.h"

#include <iostream>


DbScan::DbScan()
{
}


std::set<int> DbScan::queryNeighborhood(int centerIdx)
{
    return this->distanceMatrix[centerIdx];
}


void DbScan::expandCluster(int currentIdx,
                           std::set<int> &neighboringPoints,
                           double neighborhoodSize,
                           int clusterIdx,
                           int minPoints)
{
    this->clusters[clusterIdx].insert(currentIdx);

    for(auto row = neighboringPoints.begin(); row != neighboringPoints.end(); ++row) {
        //Point has not yet been visited
        if(!isVisited(*row)) {
            //Mark as visited
            setVisited(*row);
            std::set<int> newNeighbors = queryNeighborhood(*row);
            if(newNeighbors.size() >= minPoints) {
                for(auto n = newNeighbors.begin(); n != newNeighbors.end(); ++n) {
                    neighboringPoints.insert(*n);
                }
            }
        }
        if(!isAssigned(*row)) {
            this->clusters[clusterIdx].insert(*row);
            assign(*row);
        }
    }
}


bool DbScan::isAssigned(const int idx)
{
    if(this->alreadyAssigned[idx] == 0) {
        return false;
    }

    return true;
}


void DbScan::assign(const int idx)
{
    this->alreadyAssigned[idx] = 1;
}


bool DbScan::isNoise(const int idx)
{
    if(this->noise[idx] == 0) {
        return false;
    }

    return true;
}


void DbScan::setNoise(const int idx)
{
    this->noise[idx] = 1;
}


bool DbScan::isVisited(const int idx)
{
    if(this->visited[idx] == 0) {
        return false;
    }

    return true;
}


void DbScan::setVisited(const int idx)
{
    this->visited[idx] = 1;
}


void DbScan::init(const double neighborhoodSize)
{
    for(int row = 0; row < this->mData.rows; ++row) {
        int rX = this->mData.at<float>(row, this->mData.cols - 2);
        int rY = this->mData.at<float>(row, this->mData.cols - 1);
        for(int col = row; col < this->mData.rows; ++col) {
            int cX = this->mData.at<float>(col, this->mData.cols - 2);
            int cY = this->mData.at<float>(col, this->mData.cols - 1);

            int dX = cX - rX;
            int dY = cY - rY;

            double distance = sqrt(dX*dX + dY*dY);

            if(distance > 0 && distance <= neighborhoodSize) {
                this->distanceMatrix[row].insert(col);
                this->distanceMatrix[col].insert(row);
            }
        }
    }
}


double DbScan::estimate(const cv::Mat &input)
{
    int clusters = 128;

    int maxIterations = 300;
    double epsilon = 0.001;

    cv::Mat labels;
    cv::Mat1f means;

    cv::kmeans(input,
               clusters,
               labels,
               cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS,
                                maxIterations,
                                epsilon),
               3,
               cv::KMEANS_PP_CENTERS,
               means);

    std::vector<double> meanDist;
    meanDist.resize(clusters);
    std::vector<int> meanPoints;
    meanPoints.resize(clusters);

    for(size_t p = 0; p < input.rows; ++p) {
        double dist = cv::norm(input.row(p), means.row(labels.at<int>(p)), cv::NORM_L2);
        meanDist[labels.at<int>(p)] += dist;
        ++meanPoints[labels.at<int>(p)];
    }

    for(size_t p = 0; p < meanDist.size(); ++p) {
        if(meanPoints[p] > 0) {
            meanDist[p] /= meanPoints[p];
        } else {
            meanDist[p] = 0;
        }
    }

    return cv::mean(meanDist)[0];
}


std::vector<std::set<int>> DbScan::cluster(const cv::Mat1f &data,
                                           const int minPoints,
                                           const int neighborhoodSize)
{
    this->mData = data;
    int cluster = -1;

    double nSize;

    if(neighborhoodSize == -1) {
        //Estimates neighborhood size based on input data
        nSize = this->estimate(data);
    } else {
        nSize = neighborhoodSize;
    }

    //Precalculates distances
    this->init(nSize);

    for(size_t row = 0; row < this->mData.rows; ++row) {
        if(isVisited(row)) {
            continue;
        }

        setVisited(row);

        std::set<int> neighborhood = queryNeighborhood(row);

        if(neighborhood.size() < minPoints) {
            for(auto idx = neighborhood.begin(); idx != neighborhood.end(); ++idx) {
                setNoise(*idx);
            }
        } else {
            //Create new cluster
            this->clusters.push_back(std::set<int>());
            cluster = this->clusters.size() - 1;
            expandCluster(row, neighborhood, nSize, cluster, minPoints);
        }
    }

    return this->clusters;
}

