#include "momprocessor.h"

MomProcessor::MomProcessor(int32_t argc, char *argv[])
{
    pl::ArgumentProcessor ap("mom");
    ap.addArgument("c", "Pipeline config.", false);
    ap.addArgument("b", "Input for batch processing.", false);
    ap.addArgument("octaves", "Octaves", true);
    ap.addArgument("stages", "Substages", true);
    ap.addArgument("window", "Window size", true);
    ap.addArgument("step", "Step size.", true);
    ap.addArgument("thresh", "Threshold", true);
    ap.addSwitch("d", "Debug mode");

    try {
        mArguments = ap.parse(argc, argv);
        if(mArguments["octaves"].empty()) {
            mOctaves = 4;
        } else {
            mOctaves = std::atoi(mArguments["octaves"].c_str());
        }
        if(mArguments["stages"].empty()) {
            mStages = 1;
        } else {
            mStages = std::atoi(mArguments["stages"].c_str());
        }
        if(mArguments["window"].empty()) {
            mWindowSize = 256;
        } else {
            mWindowSize = std::atoi(mArguments["window"].c_str());
        }
        if(mArguments["step"].empty()) {
            mStepSize = mWindowSize;
        } else {
            mStepSize = std::atoi(mArguments["step"].c_str());
        }
        if(mArguments["thresh"].empty()) {
            mThreshold = 0.5;
        } else {
            mThreshold = std::atof(mArguments["thresh"].c_str());
        }
    } catch(const pl::CommandLineError &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << ap.help() << std::endl;
        throw;
    }
}

int32_t MomProcessor::run()
{
    // Create pipeline config first
    cv::Ptr<pl::PipelineConfig> pipeCfg = new pl::PipelineConfig("global");
    std::string file = mArguments["c"];
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
    pl::PipeLine textPipe(pipeCfg);
    // Start to end pipeline which does deco classification
    pl::PipeLine decoPipe(pipeCfg);

    // Create a feature detector / descriptor to the pipeline
    cv::Ptr<pl::SiftDetectorConfig> fdCfg = new pl::SiftDetectorConfig("sift");
    cv::Ptr<pl::SiftExtractorConfig> feCfg = new pl::SiftExtractorConfig("sift");
    fdCfg->fromJSON(file);
    feCfg->fromJSON(file);

    // With an additional mask generator
    cv::Ptr<pl::VesselMask> vesselMask = new pl::VesselMask("vessel");
    vesselMask->fromJSON(file);

    cv::Ptr<pl::DBScanConfig> dbscan = new pl::DBScanConfig("dbscan");
    dbscan->fromJSON(file);

    // And attach it to the pipelines
    textPipe.addFeatureDetectionStep(new pl::SiftDetector(fdCfg), vesselMask);
    textPipe.addPostprocessingStep(new pl::DBScanFilter(dbscan));
    textPipe.addFeatureExtractionStep(new pl::SiftExtractor(feCfg), cv::Ptr<pl::MaskGenerator>());
    // Deco pipeline doesn't use a mask generator
    decoPipe.addFeatureDetectionStep(new pl::SiftDetector(fdCfg), cv::Ptr<pl::MaskGenerator>());
    decoPipe.addFeatureExtractionStep(new pl::SiftExtractor(feCfg), cv::Ptr<pl::MaskGenerator>());

    // As well as a dimensionaltiy reduction step
    cv::Ptr<pl::PCAConfig> textPca = new pl::PCAConfig("text_pca");
    textPca->fromJSON(file);
    textPipe.addDimensionalityReductionStep(new pl::PCAStep(textPca));

    cv::Ptr<pl::PCAConfig> decoPca = new pl::PCAConfig("deco_pca");
    decoPca->fromJSON(file);
    decoPipe.addDimensionalityReductionStep(new pl::PCAStep(decoPca));

    // And an encoding technique
    cv::Ptr<pl::VladConfig> textEncoding = new pl::VladConfig("text_encoding");
    textEncoding->fromJSON(file);
    textPipe.addEncodingStep(new pl::VladEncodingStep(textEncoding));

    cv::Ptr<pl::VladConfig> decoEncoding = new pl::VladConfig("deco_encoding");
    decoEncoding->fromJSON(file);
    decoPipe.addEncodingStep(new pl::VladEncodingStep(decoEncoding));

    // Last but not least a classifier
    cv::Ptr<pl::SGDConfig> textCfg = new pl::SGDConfig("text_classifier");
    textCfg->fromJSON(file);
    cv::Ptr<pl::SGDStep> textClassifier = new pl::SGDStep(textCfg);
    textPipe.addClassificationStep(textClassifier);

    cv::Ptr<pl::SGDConfig> decoCfg = new pl::SGDConfig("deco_classifiers");
    decoCfg->fromJSON(file);
    cv::Ptr<pl::SGDStep> decoClassifier = new pl::SGDStep(decoCfg);
    decoPipe.addClassificationStep(decoClassifier);

    // Shows the whole pipeline
    if(debugMode) {
        textPipe.showPipeline();
        decoPipe.showPipeline();
    }

    pl::FileUtil fu;
    if(!mArguments["b"].empty()) {
        try {
            pl::FolderSummary folderSummary(mArguments["b"]);
            std::vector<std::string> files = fu.getFiles(mArguments["b"]);
            for(std::string file : files) {
                pl::FileSummary fileSummary(file);

                cv::Mat input = fu.loadImage(file);
                if(input.empty()) {
                    continue;
                }
                logger.inform("Processing file:", file);
                if(debugMode) {
                    logger.inform("Height:", input.rows, "Width:", input.cols);
                }
                // Add geometry info to summary
                fileSummary.setImageHeight(input.rows);
                fileSummary.setImageWidth(input.cols);

#ifdef MOM_DECO
                // Estimate decoration niveau
                cv::Mat niveauResults = decoPipe.run(input);

                double min, max;
                cv::Point minIdx, maxIdx;
                cv::minMaxLoc(niveauResults, &min, &max, &minIdx, &maxIdx);
                int32_t best = maxIdx.x + 1;
                if(debugMode) {
                    console.debug("Estimated niveau:", best);
                }

                switch(best) {
                case 0:
                    fileSummary.setDecorationNiveau(pl::decorationNiveau::NIVEAU_RICH);
                    break;
                case 1:
                    fileSummary.setDecorationNiveau(pl::decorationNiveau::NIVEAU_GRAPHICAL);
                    break;
                case 2:
                    fileSummary.setDecorationNiveau(pl::decorationNiveau::NIVEAU_STANDARD);
                    break;
                case 3:
                    fileSummary.setDecorationNiveau(pl::decorationNiveau::NIVEAU_NONE);
                    break;
                default:
                    fileSummary.setDecorationNiveau(pl::decorationNiveau::NIVEAU_NONE);
                    break;
                }
#endif

#ifdef MOM_TEXT
                // Process text detection
                if(debugMode) {
                    console.debug("Calculating scale space.");
                }
                pl::GaussianScaleSpace sp(mOctaves, mStages);
                std::vector<cv::Mat> scales;
                try {
                    // TODO Revise scalespace to break on invalid resize
                    sp.compute(input, scales);
                } catch(const cv::Exception) {
                    logger.report("Unable to build scalespace.");
                    return ReturnValues::RETURN_OPENCV_ERROR;
                }

                cv::Mat1f textResult = cv::Mat1f::zeros(input.size());
                // Structuring element to dilate masks
                cv::Mat structuringElement = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));

                if(debugMode) {
                    console.debug("Beginning multi scale detection.");
                }
                for(int32_t idx = scales.size() - 1; idx > -1; --idx) {
                    int32_t windowSize = mWindowSize;
                    int32_t width = scales[idx].cols;
                    int32_t height = scales[idx].rows;

                    if(windowSize > width || windowSize > height) {
                        windowSize = std::min(width, height);
                        if(debugMode) {
                            console.inform("Adjusting window size. New Value:", windowSize);
                        }
                    }

                    cv::Mat1f score = cv::Mat1f::zeros(scales[idx].size());

                    for(size_t r = 0; r < height - windowSize; r += mStepSize) {
                        for(size_t c = 0; c < width - windowSize; c += mStepSize) {
                            cv::Range rows(r, r + windowSize);
                            cv::Range cols(c, c + windowSize);
                            cv::Mat part = scales[idx](rows, cols);
                            if(debugMode) {
                                console.debug("Running text pipe.");
                            }
                            cv::Mat s = textPipe.run(part);
                            if(!s.empty() && s.at<float_t>(0) > 0) {
                                score(rows, cols).setTo(255);
                            }
                        }
                    }
                    if(debugMode) {
                        console.debug("Generating text mask.");
                    }
                    cv::resize(score, score, input.size());
                    cv::dilate(score, score, structuringElement);
                    if(debugMode) {
                        console.debug("Setting text mask.");
                    }
                    textPipe.setFeatureDetectionMask(score);

                    textResult = score;
                    std::stringstream s;
                    if(debugMode) {
                        s << "./debug_mask_level_" << idx << ".png";
                        cv::imwrite(s.str(), textResult);
                    }
                }

//                double maxScore = (mWindowSize / mStepSize) * scales.size();
//                cv::threshold(textResult, textResult, 0.5*maxScore, 255, CV_THRESH_BINARY);

                cv::Mat textMask;
                // Conversion for use with findContours
                textResult.convertTo(textMask, CV_8UC1);
                if(debugMode) {
                // TODO: Write output to temporary file
                    cv::imwrite("./binary.png", textMask);
                }
                std::vector<std::vector<cv::Point>> contours;
                cv::findContours(textMask, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
                for(std::vector<cv::Point> contour : contours) {
                    cv::Rect bbox = cv::boundingRect(contour);
                    // TODO: Start at largest bbox and remove all boxes within it, the proceed to next
                    fileSummary.addTextArea(bbox);
                    cv::rectangle(input, bbox, cv::Scalar(0, 0, 255), 3);
                }
                if(debugMode) {
                // TODO: Write output to temporary file
                    cv::imwrite("./bbox.png", input);
                }
#endif
                folderSummary.addFile(fileSummary);
            }
            folderSummary.save(mArguments["b"], "summary.xml");
        } catch(const pl::ClusterError &e) {
            logger.report(e.what());
            return ReturnValues::RETURN_CLUSTERING_ERROR;
        } catch(const pl::DimensionalityReductionError &e) {
            logger.report(e.what());
            return ReturnValues::RETURN_DIM_ERROR;
        } catch(const pl::EncodingError &e) {
            logger.report(e.what());
            return ReturnValues::RETURN_ENCODING_ERROR;
        } catch(const pl::FeatureExError &e) {
            logger.report(e.what());
            return ReturnValues::RETURN_FEATURE_EX_ERROR;
        } catch(const pl::IOError &e) {
            logger.report(e.what());
            return ReturnValues::RETURN_IO_ERROR;
        } catch(const pl::MLError &e) {
            logger.report(e.what());
            return ReturnValues::RETURN_ML_ERROR;
        } catch(const pl::OCVError &e) {
            logger.report(e.what());
            return ReturnValues::RETURN_OPENCV_ERROR;
        } catch(const cv::Exception &e) {
            logger.report(e.what());
            return ReturnValues::RETURN_OPENCV_ERROR;
        }
        return ReturnValues::RETURN_SUCCESS;
    }
    return ReturnValues::RETURN_SUCCESS;
}
