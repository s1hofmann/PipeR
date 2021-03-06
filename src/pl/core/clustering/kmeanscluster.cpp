#include "kmeanscluster.h"

void KMeansCluster::cluster(cv::Mat data,
                            int32_t clusters,
                            int32_t maxIterations,
                            double epsilon)
{
    cv::Mat labels;
    cv::Mat1f means;
    cv::kmeans(data,
               clusters,
               labels,
               cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS,
                                maxIterations,
                                epsilon),
               3,
               cv::KMEANS_PP_CENTERS,
               means);
    params.clear();
    params.push_back(means);
}


int32_t KMeansCluster::dump(const std::string & file_name)
{
    cv::FileStorage fs(file_name, cv::FileStorage::WRITE);

    //Keys have to start with a letter
    fs << "means" << params[0];
    fs.release();
    for(auto iter = params.begin(); iter != params.end(); ++iter) {
        iter->release();
    }

    return 0;
}

int32_t KMeansCluster::load(const std::string & file_name)
{
    cv::FileStorage fs(file_name, cv::FileStorage::READ);

    cv::Mat1f means;
    fs["means"] >> means;
    params.push_back(means);

    fs.release();

    return 0;
}
