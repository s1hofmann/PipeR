#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "pipeline/PipeLine.h"

int main(int argc, char *argv[]) {
    cv::Mat in = cv::imread(argv[1], CV_LOAD_IMAGE_UNCHANGED);

    pipe::PipeLine<cv::Mat> pipeLine;

    cv::Ptr<pipe::VesselMaskConfig> prCfg = new pipe::VesselMaskConfig();
    cv::Ptr<pipe::PreprocessingStep> pr = new pipe::VesselMask(prCfg, "Hurr durr, I'm a sheep!");

    cv::Ptr<pipe::SiftConfigContainer> feCfg = new pipe::SiftConfigContainer();
    cv::Ptr<pipe::SiftDetector> fe = new pipe::SiftDetector(feCfg, "hallo");

    std::cout << pr->config() << std::endl;

    pipeLine.addPreprocessingStep(pr);

    pipeLine.train(in, cv::Mat());
    pipeLine.showPipeline();

    return 0;
}