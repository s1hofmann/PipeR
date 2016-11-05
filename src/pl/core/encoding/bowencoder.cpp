#include "bowencoder.h"

namespace pl {


BOWEncoder::BOWEncoder()
    :
        EncodingMethod()
{
}

cv::Mat BOWEncoder::encode(const cv::Mat &data)
{
    //If there is an empty patch an empty 1xD matrix is returned.
    if(data.empty()) {
        return cv::Mat1f::zeros(1, mMeans.rows);
    }
    cv::Mat1b assignments = assign(data, mMeans);

    cv::Mat1f bowEncoded = cv::Mat1f::zeros(1, mMeans.rows);

    for(size_t y = 0; y < assignments.rows; ++y) {
        cv::Scalar sum = cv::sum(assignments.row(y));

        bowEncoded.at<float_t>(y) = sum[0];
    }

    return bowEncoded;
}

void BOWEncoder::loadData(const std::string &fileName)
{
    cv::FileStorage fs(fileName, cv::FileStorage::READ);
    if ( fs["means"].isNone() || fs["means"].empty() ){
        std::stringstream s;
        s << "loadData(): No node 'means' in file " << fileName << std::endl;
        throw pl::EncodingError(s.str(), currentMethod, currentLine);
    }
    fs["means"] >> mMeans;
    fs.release();
}


}
