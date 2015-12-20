#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "pipeline/PipeLine.h"

int main(int argc, char *argv[]) {
    cv::Mat in = cv::imread(argv[1], CV_LOAD_IMAGE_UNCHANGED);

    pipe::PipeLine<cv::Mat> pipeLine(true);

    cv::Ptr<pipe::SiftConfigContainer> feCfg = new pipe::SiftConfigContainer();
    cv::Ptr<pipe::SiftDetector> fe = new pipe::SiftDetector(feCfg);

    cv::Ptr<pipe::MaskGenerator> mask = new pipe::VesselMask();

    pipeLine.addFeatureExtractionStep(fe, mask);
    pipeLine.showPipeline();

    pipeLine.train(in);

    return 0;
}
