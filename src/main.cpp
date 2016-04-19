#include <iostream>

#include <opencv2/core/core.hpp>
#include "pipeline/PipeLine.h"

int main(int argc, char *argv[]) {
    // Create pipeline config first
    cv::Ptr<pl::PipelineConfig> pipeCfg = new pl::PipelineConfig("global");
    // TODO config file should be passed as parameter, this should just serve as generic fallback
    std::string file = "./test.json";
    pipeCfg->fromJSON(file);

    // And the actual pipeline object
    pl::PipeLine pipeLine(pipeCfg, pipeCfg->debugMode());

    // A little helper to load files
    // TODO Move to pipeline.execute
    pl::FileUtil fileUtil;

    // Create a feature detector / descriptor to the pipeline
    cv::Ptr<pl::SiftConfigContainer> feCfg = new pl::SiftConfigContainer("sift");
    feCfg->fromJSON(file);

    // With an additional mask generator
    cv::Ptr<pl::VesselMask> vesselMask = new pl::VesselMask("vessel");
    vesselMask->fromJSON(file);

    // And attach it to the pipeline
    pipeLine.addFeatureExtractionStep(new pl::SiftDetector(feCfg), vesselMask);

    // As well as a dimensionaltiy reduction step
    cv::Ptr<pl::PCAConfig> pcaCfg = new pl::PCAConfig("pca");
    pcaCfg->fromJSON(file);
    pipeLine.addDimensionalityReductionStep(new pl::PCAStep(pcaCfg));

    // And an encoding technique
    cv::Ptr<pl::VladConfig> vladCfg = new pl::VladConfig("vlad");
    vladCfg->fromJSON(file);
    pipeLine.addEncodingStep(new pl::VladEncodingStep(vladCfg));

    // Last but not least a classifier
    cv::Ptr<pl::SGDConfig> sgdCfg = new pl::SGDConfig("sgd");
    sgdCfg->fromJSON(file);
    cv::Ptr<pl::SGDStep> sgd = new pl::SGDStep(sgdCfg);
    pipeLine.addClassificationStep(sgd);

    // Shows the whole pipeline
    pipeLine.showPipeline();

    return pipeLine.execute(argc, argv);
}
