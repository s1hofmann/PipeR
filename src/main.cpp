#include <iostream>

#include <opencv2/core/core.hpp>
#include "pipeline/PipeLine.h"

int main() {
    pipe::PipeLine<int> pipeLine;
    cv::Ptr<pipe::ConfigContainer> feCfg = new pipe::SiftConfigContainer();
    cv::Ptr<pipe::FeatureExtractionStep> fe = new pipe::SiftDetector(feCfg);

    pipeLine.addFeatureExtractionStep(fe);

    std::cout << fe->help() << std::endl;
    std::cout << fe->usage() << std::endl;

    pipeLine.showPipeline();

    return 0;
}