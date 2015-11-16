//
// Created by Simon Hofmann on 16.11.15.
//


#pragma once

#include <string>

namespace pipe {


class PipelineStep {
public:
    PipelineStep(const std::string &info = std::string(),
                 const std::string &usage = std::string(),
                 const std::string &help = std::string());

    virtual ~PipelineStep();

    virtual int execute() = 0;

    std::string info();

    std::string help();
    std::string usage();

private:
    std::string name;
    std::string helpText;
    std::string usageText;
};


}

