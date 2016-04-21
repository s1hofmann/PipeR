#pragma once

#include <unordered_map>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <sstream>
#include <iostream>
#include "globals.h"
#include "../exception/BaseError.h"

namespace pl {


class ArgumentProcessor
{
public:
    ArgumentProcessor(const std::string &programName);
    virtual ~ArgumentProcessor();

    void addArgument(const std::string &arg,
                     const std::string &desc = std::string(),
                     const bool optional = false,
                     const std::vector<std::string> allowedValues = std::vector<std::string>());

    void addSwitch(const std::string &arg,
                   const std::string &desc = std::string());

    std::unordered_map<std::string, std::string> parse(int argc, char *argv[]);

    std::string help();

private:
    std::vector<std::string> mArguments;
    std::vector<std::string> mArgumentDesc;
    std::vector<std::string> mOptionalArguments;
    std::vector<std::string> mOptionalArgumentDesc;
    std::unordered_map<std::string, std::vector<std::string>> mAllowedValues;
    std::vector<std::string> mSwitches;
    std::vector<std::string> mSwitchDesc;

    std::string mName;

    std::string createFlag(const std::string &arg) const;
    std::string parseFlag(const std::string &arg) const;

    std::vector<std::string> toStringVector(int argc, char *argv[]) const;

    std::string argumentString(std::vector<std::string> &args,
                               std::vector<std::string> &desc,
                               bool optional = false);

    std::string switchString(std::vector<std::string> &switches,
                             std::vector<std::string> &desc);

    bool notIn(const std::string &what,
               const std::vector<std::string> &where) const;

    bool notIn(const std::string &what,
               const std::vector<std::vector<std::string>> &where) const;
};


}
