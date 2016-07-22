#include "postprocessingstep.h"

namespace pl {


PostProcessingStep::PostProcessingStep(const cv::Ptr<ConfigContainer> config)
    :
        PipelineStep(config)
{
}

PostProcessingStep::~PostProcessingStep()
{
}

}
