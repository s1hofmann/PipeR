//
// Created by Simon Hofmann on 17.11.15.
//

#include "MaskGenerationStep.h"

namespace pipe {


MaskGenerationStep::MaskGenerationStep(const std::string &info,
                                       const std::string &usage,
                                       const std::string &help)
        :
        PreprocessingStep(info, usage, help) {

}


int MaskGenerationStep::execute() {
    return 0;
}


MaskGenerationStep::~MaskGenerationStep() {

}


}
