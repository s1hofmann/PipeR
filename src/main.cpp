#include <iostream>

#include <opencv2/core/core.hpp>
#include "pipeline/PipeLine.h"
#include "preprocessing/ImageProcessingStep.h"
#include "preprocessing/MaskGenerationStep.h"
#include "feature_extraction/SiftDetector.h"
#include "encoding/VladEncoder.h"

int main() {
    pipe::PipeLine<int> pipeLine;
    cv::Ptr<pipe::ImageProcessingStep> pre = new pipe::ImageProcessingStep();
    cv::Ptr<pipe::MaskGenerationStep> pre2 = new pipe::MaskGenerationStep("Mask generation", "I'm another stupid test!", "to see if it works");
    cv::Ptr<pipe::FeatureExtractionStep> fe = new pipe::SiftDetector();
    cv::Ptr<pipe::EncodingStep> en = new pipe::VladEncoder();

    pipeLine.addPreprocessingStep(pre);
    pipeLine.addPreprocessingStep(pre2);
    pipeLine.addFeatureExtractionStep(fe);
    pipeLine.addEncodingStep(en);

    pipeLine.showPipeline();
    return 0;
}