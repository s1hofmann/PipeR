//
// Created by Simon Hofmann on 19.11.15.
//


#pragma once

#include <string>

namespace pipe {

/**
 * Base class for each steps config class.
 * Every config class has te be derived from
 */
class ConfigContainer {
public:
    ConfigContainer(const std::string &usage = "No usage text provided, I'm sorry.",
                    const std::string &help = "No help text provided, I'm sorry.");

    virtual ~ConfigContainer();

    std::string usage() const;
    std::string help() const;

    virtual std::string toString() const = 0;

private:
    std::string usageText;
    std::string helpText;
};


}
