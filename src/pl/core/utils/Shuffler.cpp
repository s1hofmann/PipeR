#include "Shuffler.h"


namespace pl {


Shuffler::Shuffler()
{

}

void Shuffler::shuffle(const cv::Mat &descriptors,
                       const cv::Mat &labels,
                       cv::Mat &shuffledDescriptors,
                       cv::Mat &shuffledLabels)
{
    shuffledDescriptors.create(descriptors.size(), CV_64FC1);
    shuffledLabels.create(labels.size(), CV_64FC1);

    std::vector<int32_t> idx = Range<int32_t>::random(0, descriptors.rows);

#if USE_TBB
    tbb::parallel_for(int32_t(0), descriptors.rows, [&](int32_t i) {
        descriptors.row(i).copyTo(shuffledDescriptors.row(idx[i]));
        labels.row(i).copyTo(shuffledLabels.row(idx[i]));
    }
    );
#else
    for(int32_t i = 0; i < descriptors.rows; ++i) {
        descriptors.row(i).copyTo(shuffledDescriptors.row(idx[i]));
        labels.row(i).copyTo(shuffledLabels.row(idx[i]));
    }
#endif
}

void Shuffler::shuffle(const std::vector<std::string> &files,
                       const std::vector<int32_t> &labels,
                       std::vector<std::string> &shuffledFiles,
                       std::vector<int32_t> &shuffledLabels)
{
    shuffledFiles.resize(files.size());
    shuffledLabels.resize(labels.size());

    std::vector<int32_t> idx = Range<int32_t>::random(0, files.size());
#if USE_TBB
        tbb::parallel_for(size_t(0), files.size(), [&](size_t i) {
            shuffledFiles[i] = files[idx[i]];
            shuffledLabels[i] = labels[idx[i]];
        }
        );
#else
    for(int32_t i = 0; i < files.size(); ++i) {
        shuffledFiles[i] = files[idx[i]];
        shuffledLabels[i] = labels[idx[i]];
    }
#endif
}


}
