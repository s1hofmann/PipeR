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

    std::vector<int> idx = Range<int>::unique(0, descriptors.rows);
    cv::randShuffle(idx);

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



}
