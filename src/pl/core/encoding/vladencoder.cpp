#include "vladencoder.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <chrono>

#if USE_TBB
#include <tbb/parallel_for.h>
#endif

VladEncoder::VladEncoder()
    :
        EncodingMethod()
{

}


VladEncoder::~VladEncoder() {}

void VladEncoder::loadData(const std::string & file_name)
{
    cv::FileStorage fs(file_name, cv::FileStorage::READ);
    if ( fs["means"].isNone() || fs["means"].empty() ){
        std::stringstream s;
        s << "No node 'means' in file: " << file_name << std::endl;
        throw pl::EncodingError(s.str(), currentMethod, currentLine);
    }
    fs["means"] >> mMeans;
    fs.release();
}

cv::Mat VladEncoder::encode(const cv::Mat &data)
{
    //If there is an empty patch an empty 1xD matrix is returned.
    if(data.empty()) {
        return cv::Mat1f::zeros(1, mMeans.cols*mMeans.rows);
    }
    cv::Mat1b assignments = assign(data, mMeans);

    cv::Mat vladEncoded(assignments.rows, data.cols, CV_32F);

#if USE_TBB
    tbb::parallel_for(int(0), assignments.rows, int(1), [&](int cluster) {
#else
    for(size_t cluster = 0; cluster < assignments.rows; ++cluster) {
#endif
        //Storage for every thread
        cv::Mat1f pAccumulator = cv::Mat1f::zeros(1, data.cols);

        cv::Mat indices;
        cv::findNonZero(assignments.row(cluster), indices);

        int entries = indices.rows;

        for(int dataPoints = 0; dataPoints < entries; ++dataPoints) {
            cv::Mat1f pTmp;
            cv::subtract(data.row(indices.at<int>(dataPoints, 0)), mMeans.row(cluster), pTmp);
            cv::add(pAccumulator, pTmp, pAccumulator);
        }

        if(mNormType & NORM_MASS == 1) {
             normalizeData(pAccumulator, NORM_MASS);
        }
        if(mNormType & NORM_COMPONENT_L2 == 1) {
            normalizeData(pAccumulator, NORM_COMPONENT_L2);
        }
        pAccumulator.copyTo(vladEncoded.row(cluster));
    }
#if USE_TBB
    );
#endif

    if(mNormType & NORM_SSR == 1) {
        normalizeData(vladEncoded, NORM_SSR);
    }
    if(mNormType & NORM_GLOBAL_L2 == 1) {
        normalizeData(vladEncoded, NORM_GLOBAL_L2);
    }

    return vladEncoded.reshape(0,1);
}
