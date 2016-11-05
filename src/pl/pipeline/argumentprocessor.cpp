#include "argumentprocessor.h"

namespace pl {


ArgumentProcessor::ArgumentProcessor(const std::string &programName)
    :
        mName(programName)
{
    addSwitch("help", "Explains available command line options.");
}

ArgumentProcessor::~ArgumentProcessor()
{

}

void ArgumentProcessor::addArgument(const std::string &arg,
                                    const std::string &desc,
                                    const bool optional,
                                    const std::vector<std::string> allowedValues)
{
    std::string flag = createFlag(arg, optional);
    if(optional) {
        mOptionalArguments.push_back(flag);
        mOptionalArgumentDesc.push_back(desc);
        if(allowedValues.size()) {
            mAllowedValues[flag] = allowedValues;
        }
    } else {
        mArguments.push_back(flag);
        mArgumentDesc.push_back(desc);
        if(allowedValues.size()) {
            mAllowedValues[flag] = allowedValues;
        }
    }
}

void ArgumentProcessor::addSwitch(const std::string &arg,
                                  const std::string &desc)
{
    std::string flag = createFlag(arg, true);
    mSwitches.push_back(flag);
    mSwitchDesc.push_back(desc);
}

std::unordered_map<std::string, std::string> ArgumentProcessor::parse(int32_t argc, char *argv[])
{
    std::vector<std::string> args = toStringVector(argc, argv);

    std::unordered_map<std::string, std::string> argumentMap;

    for(size_t idx = 0; idx < argc; ++idx) {
        std::string currentArgument = args[idx];
        if(notIn(currentArgument, mArguments) &&
           notIn(currentArgument, mOptionalArguments) &&
           notIn(currentArgument, mSwitches)) {
            continue;
        } else {
            size_t nextIdx = idx + 1;
            if(nextIdx >= argc) {
                if(notIn(currentArgument, mSwitches)) {
                    continue;
                } else {
                    argumentMap[parseFlag(currentArgument)] = "true";
                }
            } else {
                std::string nextArgument = args[nextIdx];
                if(!notIn(currentArgument, mArguments) && notIn(nextArgument, {mOptionalArguments, mSwitches})) {
                    if(!mAllowedValues[currentArgument].empty()) {
                        if(!notIn(nextArgument, mAllowedValues[currentArgument])) {
                            argumentMap[parseFlag(currentArgument)] = nextArgument;
                        } else {
                            std::stringstream s;
                            s << "Encountered invalid option: " << currentArgument << " " << nextArgument << std::endl;
                            throw CommandLineError(s.str(), currentMethod, currentLine);
                        }
                    } else {
                        argumentMap[parseFlag(currentArgument)] = nextArgument;
                    }
                } else if(!notIn(currentArgument, mOptionalArguments) && notIn(nextArgument, {mArguments, mSwitches})) {
                    if(!mAllowedValues[currentArgument].empty()) {
                        if(!notIn(nextArgument, mAllowedValues[currentArgument])) {
                            argumentMap[parseFlag(currentArgument)] = nextArgument;
                        } else {
                            std::stringstream s;
                            s << "Encountered invalid option: " << currentArgument << " " << nextArgument << std::endl;
                            throw CommandLineError(s.str(), currentMethod, currentLine);
                        }
                    } else {
                        argumentMap[parseFlag(currentArgument)] = nextArgument;
                    }
                } else if(!notIn(currentArgument, mSwitches) && !notIn(nextArgument, {mArguments, mOptionalArguments})) {
                    argumentMap[parseFlag(currentArgument)] = "true";
                }
            }
        }
    }

    if(argumentMap[parseFlag("--help")].empty()) {
        for(std::string arg : mArguments) {
            if(argumentMap[parseFlag(arg)].empty()) {
                std::stringstream s;
                s << "Missing required argument: " << arg << std::endl;
                throw CommandLineError(s.str(), currentMethod, currentLine);
            }
        }
    } else {
        std::stringstream s;
        s << "Let me help you!" << std::endl;
        throw CommandLineError(s.str());
    }

    return argumentMap;
}

std::string ArgumentProcessor::help()
{
    std::stringstream s;

    s << "Usage: " << mName << " options..." << std::endl;
    s << "Options:" << std::endl;
    s << argumentString(mArguments, mArgumentDesc, false);
    s << argumentString(mOptionalArguments, mOptionalArgumentDesc, true);
    s << switchString(mSwitches, mSwitchDesc);

    return s.str();
}

std::string ArgumentProcessor::createFlag(const std::string &arg, const bool optional) const
{
    std::stringstream f;
    if(optional) {
        f << "--" << arg;
    } else {
        f << "-" << arg;
    }

    return f.str();
}

std::string ArgumentProcessor::parseFlag(const std::string &arg) const
{
    size_t idx = arg.find_first_not_of("-");

    return arg.substr(idx);
}

std::vector<std::string> ArgumentProcessor::toStringVector(int32_t argc, char *argv[]) const
{
    std::vector<std::string> elements(argc);
    for(size_t idx = 0; idx < argc; ++idx) {
        elements[idx] = std::string(argv[idx]);
    }

    return elements;
}

std::string ArgumentProcessor::argumentString(std::vector<std::string> &args,
                                              std::vector<std::string> &desc,
                                              bool optional)
{
    std::stringstream s;
    for(size_t idx = 0; idx < args.size(); ++idx) {
        std::string argument = args[idx];
        std::string description = desc[idx];
        s << argument;
        if(!description.empty()) {
            if(optional) {
                s << " OPTIONAL\t " << description;
            } else {
                s << "\t\t " << description;
            }
        }
        if(mAllowedValues[argument].size()) {
            s << " Values: (";
            for(size_t idx = 0; idx < mAllowedValues[argument].size(); ++idx) {
                if(idx == mAllowedValues[argument].size() - 1) {
                    s << mAllowedValues[argument][idx] << ")" << std::endl;
                } else {
                    s << mAllowedValues[argument][idx] << "|";
                }
            }
        } else {
            s << std::endl;
        }
    }

    return s.str();
}

std::string ArgumentProcessor::switchString(std::vector<std::string> &switches,
                                            std::vector<std::string> &desc)
{
    std::stringstream s;
    for(size_t idx = 0; idx < switches.size(); ++idx) {
        s << switches[idx] << " OPTIONAL";
        if(!desc[idx].empty()) {
            s << "\t " << desc[idx] << std::endl;
        } else {
            s << std::endl;
        }
    }

    return s.str();
}

bool ArgumentProcessor::notIn(const std::string &what,
                              const std::vector<std::string> &where) const
{
    return std::find(where.begin(), where.end(), what) == where.end();
}

bool ArgumentProcessor::notIn(const std::string &what,
                              const std::vector<std::vector<std::string> > &where) const
{
    int32_t sum = 0;
    for(auto elem : where) {
        if(notIn(what, elem)) {
            ++sum;
        }
    }

    return (sum == where.size()) ? true : false;
}


}
