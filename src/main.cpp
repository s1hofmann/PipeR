#include <iostream>

#include <opencv2/core/core.hpp>
#include "pl/pipeline/PipeLine.h"

int main(int argc, char *argv[]) {
    pl::FileLogger logger("/home/sim0n/pipeline_log.txt");
    logger.warn("hi", "geht's?");
    pl::ArgumentProcessor ap("test");
    ap.addArgument("m", "Operational mode.", false, {"train", "run", "optimize"});
    ap.addArgument("c", "Pipeline config.", false);
    ap.addArgument("i", "Input for one shot processing.", true);
    ap.addArgument("b", "Input for batch processing.", true);
    ap.addSwitch("d", "Debug mode");

    std::unordered_map<std::string, std::string> arguments;
    try {
        arguments = ap.parse(argc, argv);
    } catch(std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    // Create pipeline config first
    cv::Ptr<pl::PipelineConfig> pipeCfg = new pl::PipelineConfig("global");
    std::string file = arguments["c"];
    pipeCfg->fromJSON(file);

    // And the actual pipeline object
    pl::PipeLine pipeLine(pipeCfg);
    if(!arguments["d"].empty()) {
        pipeLine.setDebugMode(true);
    } else {
        pipeLine.setDebugMode(false);
    }

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

    pl::FileUtil fu;
    std::string mode = arguments.at("m");
    if(!mode.compare("train")) {
        if(arguments["i"].empty()) {
            std::cerr << "Labelfile required for training. Aborting." << std::endl;
            return PipeLineReturnValues::RETURN_IO_ERROR;
        } else {
            try {
                std::pair<std::vector<std::string>, std::vector<int>> filesWithLabels = fu.getFilesFromLabelFile(arguments["i"]);
                pipeLine.train(filesWithLabels.first, filesWithLabels.second);
            } catch(pl::IOError &e) {
                std::cerr << e.what();
                return PipeLineReturnValues::RETURN_IO_ERROR;
            }

            return PipeLineReturnValues::RETURN_SUCCESS;
        }
    } else if(!mode.compare("run")) {
        if(!arguments["b"].empty()) {
            try {
                std::vector<std::string> files = fu.getFiles(arguments["b"]);
                for(std::string file : files) {
                    cv::Mat result = pipeLine.run(file);
                    if(!result.empty()) {
                        std::cout << "Result for file " << file << ": " << result << std::endl;
                    }
                }
            } catch(pl::BaseError &e) {
                std::cerr << e.what();
                return PipeLineReturnValues::RETURN_IO_ERROR;
            }

            return PipeLineReturnValues::RETURN_SUCCESS;
        } else if(!arguments["i"].empty()) {
            try {
                std::string file = arguments["i"];
                std::cout << "Result for file " << file << ": " << pipeLine.run(file) << std::endl;
            } catch(pl::BaseError &e) {
                std::cerr << e.what();
                return PipeLineReturnValues::RETURN_IO_ERROR;
            }

            return PipeLineReturnValues::RETURN_SUCCESS;
        }
    } else if(!mode.compare("optimize")) {
        info("Not yet");
        return PipeLineReturnValues::RETURN_SUCCESS;
    }
    return 0;
}
