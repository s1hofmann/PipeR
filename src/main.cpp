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
    std::string file = "./test.json";
    pipeCfg->fromJSON(file);

    pl::PipeLine<cv::Mat> pipeLine(pipeCfg, true);

    cv::Ptr<pl::SiftConfigContainer> feCfg = new pl::SiftConfigContainer("sift");
    feCfg->fromJSON(file);

    cv::Ptr<pl::VesselMask> vesselMask = new pl::VesselMask("vessel");
    vesselMask->fromJSON(file);

    pipeLine.addFeatureExtractionStep(new pl::SiftDetector(feCfg), vesselMask);

    cv::Ptr<pl::PCAConfig> pcaCfg = new pl::PCAConfig("pca");
    pcaCfg->fromJSON(file);

    pipeLine.addDimensionalityReductionStep(new pl::PCAStep(pcaCfg));

    cv::Ptr<pl::VladConfig> vladCfg = new pl::VladConfig("vlad");
    vladCfg->fromJSON(file);

    pipeLine.addEncodingStep(new pl::VladEncodingStep(vladCfg));

    cv::Ptr<pl::SGDConfig> sgdCfg = new pl::SGDConfig("sgd");
    sgdCfg->fromJSON(file);
    cv::Ptr<pl::SGDStep> sgd = new pl::SGDStep(sgdCfg);

    pipeLine.addClassificationStep(sgd);

    pipeLine.showPipeline();

    pipeLine.train(filesWithLabels.first, filesWithLabels.second);

    return 0;
}
