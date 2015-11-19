//
// Created by Simon Hofmann on 19.11.15.
//


#pragma once

#include <string>

namespace pipe {


class ConfigContainer {
public:
    ConfigContainer(const std::string &usage = "No usage text provided, I'm sorry.",
                    const std::string &help = "No help text provided, I'm sorry.");

    virtual ~ConfigContainer();

    std::string usage() const;
    std::string help() const;

    virtual std::string config() const = 0;

private:
    std::string usageText;
    std::string helpText;
};


}
