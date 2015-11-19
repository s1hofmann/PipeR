//
// Created by Simon Hofmann on 19.11.15.
//


#pragma once

#include <string>

namespace pipe {


class ConfigContainer {
public:
    ConfigContainer(const std::string &usage = std::string(),
                    const std::string &help = std::string());

    virtual ~ConfigContainer();

    std::string usage() const;
    std::string help() const;

private:
    std::string usageText;
    std::string helpText;
};


}
