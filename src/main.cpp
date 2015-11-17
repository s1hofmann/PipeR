#include <iostream>

#include <opencv2/core/core.hpp>
#include "pipeline/PipeLine.h"
#include "preprocessing/ImageProcessingStep.h"
#include "preprocessing/MaskGenerationStep.h"

int main() {
    pipe::PipeLine pipeLine;
    cv::Ptr<pipe::ImageProcessingStep> pre = new pipe::ImageProcessingStep("Image preprocessing", "I'm just a simple test", "to see if it works");
    cv::Ptr<pipe::MaskGenerationStep> pre2 = new pipe::MaskGenerationStep("Mask generation", "I'm another stupid test!", "to see if it works");

    pipeLine.addPreprocessingStep(pre);
    pipeLine.addPreprocessingStep(pre2);

    pipeLine.showPipeline();
    return 0;
}