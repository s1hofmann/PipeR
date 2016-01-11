#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "pipeline/PipeLine.h"

int main(int argc, char *argv[]) {
    pl::FileUtil fileUtil;
    std::pair<std::vector<std::string>, std::vector<int>> filesWithLabels = fileUtil.getFilesFromLabelFile(argv[1]);
    std::cout << filesWithLabels.first.size() << std::endl;

    cv::Ptr<pl::PipelineConfig> pipeCfg = new pl::PipelineConfig;
    pipeCfg->setDescriptorDir("/home/sim0n/descriptors");
    pipeCfg->setDescriptorLabelFile("/home/sim0n/labels.dat");
    pipeCfg->setDimensionalityReductionPath("/home/sim0n/pca.yml");
    pipeCfg->setDimensionalityReductionSubset(150000);

    pl::PipeLine<cv::Mat> pipeLine(pipeCfg, true);

    cv::Ptr<pl::SiftConfigContainer> feCfg = new pl::SiftConfigContainer();
    cv::Ptr<pl::SiftDetector> fe = new pl::SiftDetector(feCfg);
    cv::Ptr<pl::MaskGenerator> mask = new pl::VesselMask();

    pipeLine.addFeatureExtractionStep(fe, mask);

    cv::Ptr<pl::PCAConfig> pcaCfg = new pl::PCAConfig(64, 0.001, true);
    cv::Ptr<pl::PCAStep> pca = new pl::PCAStep(pcaCfg);

    pipeLine.addDimensionalityReductionStep(pca);

    std::vector<normStrategy> norms = { NORM_COMPONENT_L2, NORM_GLOBAL_L2 };
    cv::Ptr<pl::VladConfig> vladCfg = new pl::VladConfig(norms, 64);
    cv::Ptr<pl::VladEncodingStep> vlad = new pl::VladEncodingStep(vladCfg);

    pipeLine.addEncodingStep(vlad);

    cv::Ptr<pl::SGDConfig> sgdCfg = new pl::SGDConfig();
    cv::Ptr<pl::SGDStep> sgd = new pl::SGDStep(sgdCfg);

    pipeLine.addClassificationStep(sgd);

    pipeLine.showPipeline();

    pipeLine.train(filesWithLabels.first, filesWithLabels.second);

    return 0;
}
