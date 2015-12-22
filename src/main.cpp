#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "pipeline/PipeLine.h"

int main(int argc, char *argv[]) {
    cv::Mat in = cv::imread(argv[1], CV_LOAD_IMAGE_UNCHANGED);

    pl::PipeLine<cv::Mat> pipeLine(true);

    cv::Ptr<pl::SiftConfigContainer> feCfg = new pl::SiftConfigContainer();
    cv::Ptr<pl::SiftDetector> fe = new pl::SiftDetector(feCfg);

    cv::Ptr<pl::MaskGenerator> mask = new pl::VesselMask();

    cv::Ptr<pl::PCAConfig> pcaCfg = new pl::PCAConfig(64, 0.001, true);
    cv::Ptr<pl::PCAStep> pca = new pl::PCAStep(pcaCfg, "huhu");

    pipeLine.addFeatureExtractionStep(fe, mask);
    pipeLine.addDimensionalityReductionStep(pca);
    pipeLine.showPipeline();

    pipeLine.train(in);

    return 0;
}
