#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "pipeline/PipeLine.h"

int main(int argc, char *argv[]) {
    pl::FileUtil fileUtil;
    std::pair<std::vector<std::string>, std::vector<int>> filesWithLabels = fileUtil.getFilesFromLabelFile(argv[1]);
    std::cout << filesWithLabels.first.size() << std::endl;

    cv::Ptr<pl::PipelineConfig> pipeCfg = new pl::PipelineConfig("global");
    pipeCfg->setDescriptorDir("/home/sim0n/descriptors");
    pipeCfg->setDescriptorLabelFile("/home/sim0n/labels.dat");

    pl::PipeLine<cv::Mat> pipeLine(pipeCfg, true);

    cv::Ptr<pl::SiftConfigContainer> feCfg = new pl::SiftConfigContainer("sift");

    pipeLine.addFeatureExtractionStep(new pl::SiftDetector(feCfg), new pl::VesselMask());

    cv::Ptr<pl::PCAConfig> pcaCfg = new pl::PCAConfig("pca", 64, 0.001, true);

    pipeLine.addDimensionalityReductionStep(new pl::PCAStep(pcaCfg));

    std::vector<normStrategy> norms = { NORM_COMPONENT_L2, NORM_GLOBAL_L2 };
    cv::Ptr<pl::VladConfig> vladCfg = new pl::VladConfig("vlad", norms, 64);

    pipeLine.addEncodingStep(new pl::VladEncodingStep(vladCfg));

    cv::Ptr<pl::SGDConfig> sgdCfg = new pl::SGDConfig("sgd");
    cv::Ptr<pl::SGDStep> sgd = new pl::SGDStep(sgdCfg);

    pipeLine.addClassificationStep(sgd);

    pipeLine.showPipeline();

    pipeLine.train(filesWithLabels.first, filesWithLabels.second);

    return 0;
}
