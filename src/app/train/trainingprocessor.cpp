#include "trainingprocessor.h"

TrainingProcessor::TrainingProcessor(int32_t argc, char *argv[])
{
    pl::ArgumentProcessor ap("train");
    ap.addArgument("conf", "Pipeline config.", false);
    ap.addArgument("labels", "Label file.", false);
    ap.addArgument("enc", "Encoding", true, {"vlad"});
    ap.addArgument("fdet", "Feature detector.", true, {"sift"});
    ap.addArgument("fex", "Feature descriptor.", false, {"sift"});
    ap.addArgument("fmask", "Feature mask.", true, {"vessel"});
    ap.addArgument("red", "Dimensionality reduction.", true, {"pca"});
    ap.addArgument("learn", "Learning method.", false, {"sgd"});
    ap.addSwitch("d", "Debug mode");

    try {
        mArguments = ap.parse(argc, argv);
    } catch(const pl::CommandLineError &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << ap.help() << std::endl;
        throw;
    }
}

int32_t TrainingProcessor::run()
{
    // Create pipeline config first
    cv::Ptr<pl::PipelineConfig> pipeCfg = new pl::PipelineConfig("global");
    std::string file = mArguments["conf"];
    pipeCfg->fromJSON(file);

    pl::FileLogger logger(pipeCfg->logFile());
    pl::ConsoleLogger console;

    bool debugMode = !mArguments["d"].empty();

    pipeCfg->setDebugMode(debugMode);

    if(debugMode) {
        console.inform("Assembling pipeline(s).");
    }

    // And the actual pipeline objects
    // Pipeline which takes care of preprocessing and feature extraction for text classification
    try {
        pl::PipeLine trainPipe(pipeCfg);

        // Create a feature detector / descriptor to the pipeline
        cv::Ptr<pl::ConfigContainer> fdCfg;
        std::string featureDetector = mArguments["fdet"];
        if(!featureDetector.compare("sift")) {
            fdCfg = new pl::SiftDetectorConfig(featureDetector);
            fdCfg->fromJSON(file);

            if(!mArguments["fmask"].empty()) {
                // With an additional mask generator
                std::string maskType = mArguments["fmask"];
                if(!maskType.compare("vessel")) {
                    cv::Ptr<pl::VesselMask> vesselMask = new pl::VesselMask(maskType);
                    vesselMask->fromJSON(file);
                    trainPipe.addFeatureDetectionStep(new pl::SiftDetector(fdCfg), vesselMask);
                }
            } else {
                // Without mask
                trainPipe.addFeatureDetectionStep(new pl::SiftDetector(fdCfg), cv::Ptr<pl::MaskGenerator>());
            }
        }
        cv::Ptr<pl::ConfigContainer> feCfg;
        std::string featureExtractor = mArguments["fex"];
        if(!featureExtractor.compare("sift")) {
            feCfg = new pl::SiftExtractorConfig(featureExtractor);
            feCfg->fromJSON(file);
            // Without mask
            trainPipe.addFeatureExtractionStep(new pl::SiftExtractor(feCfg), cv::Ptr<pl::MaskGenerator>());
        }

    //    Dimensionality reduction
        std::string reductionMethod = mArguments["red"];
        if(!reductionMethod.compare("pca")) {
            cv::Ptr<pl::PCAConfig> pca = new pl::PCAConfig(reductionMethod);
            pca->fromJSON(file);
            trainPipe.addDimensionalityReductionStep(new pl::PCAStep(pca));
        }

    //    Encoding
        std::string encodingMethod = mArguments["enc"];
        if(!encodingMethod.compare("vlad")) {
            cv::Ptr<pl::VladConfig> encoding = new pl::VladConfig(encodingMethod);
            encoding->fromJSON(file);
            trainPipe.addEncodingStep(new pl::VladEncodingStep(encoding));
        }

    //    Learning algorithm
        std::string learningAlgo = mArguments["learn"];
        if(!learningAlgo.compare("sgd")) {
            cv::Ptr<pl::SGDConfig> sgd = new pl::SGDConfig(learningAlgo);
            sgd->fromJSON(file);
            trainPipe.addClassificationStep(new pl::SGDStep(sgd));
        }

        if(debugMode) {
            trainPipe.showPipeline();
        }
        pl::FileUtil fu;

        std::vector<std::pair<std::string, int32_t>> filesWithLabels = fu.getFilesFromLabelFile(mArguments["labels"]);
        trainPipe.train(filesWithLabels);
    } catch(const pl::ClusterError &e) {
        console.report(e.what());
        logger.report(e.what());
        return ReturnValues::RETURN_CLUSTERING_ERROR;
    } catch(const pl::DimensionalityReductionError &e) {
        console.report(e.what());
        logger.report(e.what());
        return ReturnValues::RETURN_DIM_ERROR;
    } catch(const pl::EncodingError &e) {
        console.report(e.what());
        logger.report(e.what());
        return ReturnValues::RETURN_ENCODING_ERROR;
    } catch(const pl::FeatureExError &e) {
        console.report(e.what());
        logger.report(e.what());
        return ReturnValues::RETURN_FEATURE_EX_ERROR;
    } catch(const pl::IOError &e) {
        console.report(e.what());
        logger.report(e.what());
        return ReturnValues::RETURN_IO_ERROR;
    } catch(const pl::MLError &e) {
        console.report(e.what());
        logger.report(e.what());
        return ReturnValues::RETURN_ML_ERROR;
    } catch(const pl::OCVError &e) {
        console.report(e.what());
        logger.report(e.what());
        return ReturnValues::RETURN_OPENCV_ERROR;
    } catch(const cv::Exception &e) {
        console.report(e.what());
        logger.report(e.what());
        return ReturnValues::RETURN_OPENCV_ERROR;
    } catch(const pl::BaseError &e) {
        console.report(e.what());
        logger.report(e.what());
        return ReturnValues::RETURN_ERROR;
    }
    console.inform("Done.");
    return ReturnValues::RETURN_SUCCESS;
}
