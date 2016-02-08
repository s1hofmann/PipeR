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
    shuffledDescriptors.create(descriptors.rows, descriptors.cols, descriptors.type());
    shuffledLabels.create(1, labels.cols, labels.type());

    std::vector<int> idx = Range<int>::random(0, descriptors.rows);

#if USE_TBB
    tbb::parallel_for(int(0), descriptors.rows, [&](int i) {
        descriptors.row(i).copyTo(shuffledDescriptors.row(idx[i]));
        shuffledLabels.at<int>(i) = labels.at<int>(idx[i]);
    }
    );
#else
    for(int i = 0; i < descriptors.rows; ++i) {
        descriptors.row(i).copyTo(shuffledDescriptors.row(idx[i]));
        shuffledLabels.at<int>(i) = labels.at<int>(idx[i]);
    }
#endif
}

void Shuffler::shuffle(const std::vector<std::string> &files,
                       const std::vector<int> &labels,
                       std::vector<std::string> &shuffledFiles,
                       std::vector<int> &shuffledLabels)
{
    shuffledFiles.resize(files.size());
    shuffledLabels.resize(labels.size());

    std::vector<int> idx = Range<int>::random(0, files.size());
#if USE_TBB
        tbb::parallel_for(size_t(0), files.size(), [&](size_t i) {
            shuffledFiles[i] = files[idx[i]];
            shuffledLabels[i] = labels[idx[i]];
        }
        );
#else
    for(int i = 0; i < files.size(); ++i) {
        shuffledFiles[i] = files[idx[i]];
        shuffledLabels[i] = labels[idx[i]];
    }
#endif
}


}
