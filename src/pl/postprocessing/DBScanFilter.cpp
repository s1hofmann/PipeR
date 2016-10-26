#include "DBScanFilter.h"

namespace pl {

DBScanFilter::DBScanFilter(const cv::Ptr<ConfigContainer> config)
    :
        PostProcessingStep(config)
{
}

DBScanFilter::~DBScanFilter()
{

}


cv::Mat DBScanFilter::runImpl(const bool debugMode, const cv::Mat &input, const cv::Mat &param) const
{
    return this->trainImpl(debugMode, input, param);
}


cv::Mat DBScanFilter::trainImpl(const bool debugMode, const cv::Mat &input, const cv::Mat &param) const
{
    cv::Ptr<DBScanConfig> config;
    try {
        config = config_cast<DBScanConfig>(this->mConfig);
    } catch(std::bad_cast) {
        std::stringstream s;
        s << "Wrong config type: " << this->mConfig->identifier();
        throw PostProcessError(s.str(), currentMethod, currentLine);
    }

    if(input.empty()) {
        throw PostProcessError("Missing parameters, input empty.", currentMethod, currentLine);
    }

    DbScan cl;
    std::vector<std::set<int>> clusters;
    clusters = cl.cluster(input.colRange(input.cols - 2,
                                         input.cols),
                          config->minPoints(),
                          config->neighborhoodSize());

    if(debugMode) {
        debug("Clustering done, detected", clusters.size(), "clusters.");
        debug("Assembling filtered descriptors.");
    }

    cv::Mat1f allDescriptors;
    //Loop through all clusters, assemble descriptors and classify them
    for(size_t cluster = 0; cluster < clusters.size(); ++cluster) {
        cv::Mat1f clusterDescriptor(clusters[cluster].size(), input.cols);
        int i = 0;
        for(auto idx = clusters[cluster].begin(); idx != clusters[cluster].end(); ++idx) {
            input.row(*idx).copyTo(clusterDescriptor.row(i));
            ++i;
        }

        if(!clusterDescriptor.empty()) {
            if(allDescriptors.empty()) {
                allDescriptors = clusterDescriptor.clone();
            } else {
                cv::vconcat(clusterDescriptor, allDescriptors);
            }
        }
    }

    return allDescriptors;
}


}
