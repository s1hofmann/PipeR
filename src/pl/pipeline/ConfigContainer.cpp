//
// Created by Simon Hofmann on 19.11.15.
//

#include "ConfigContainer.h"


namespace pl {


ConfigContainer::ConfigContainer(const std::string &identifier,
                                 const std::string &usage,
                                 const std::string &help)
    :
        mIdentifier(identifier),
        mUsageText(usage),
        mHelpText(help),
        mJsonFile(std::string())
{

}

Json::Value ConfigContainer::readJSON(const std::string &file)
{
    Json::Reader reader;
    Json::Value root;

    std::ifstream ifs;
    ifs.open(file, std::ifstream::in);

    bool parsingSuccessfull = reader.parse(ifs, root);

    if(parsingSuccessfull) {
        ifs.close();
        mJsonFile = file;
        return root;
    } else {
        return Json::Value();
    }
}

bool ConfigContainer::writeJSON(const Json::Value &json) const
{
    if(!mJsonFile.empty()) {
        std::ofstream ofs;
        ofs.open(mJsonFile, std::ofstream::out);
        ofs << json;
        ofs.close();
        return true;
    }
    return false;
}

ConfigContainer::~ConfigContainer()
{

}

std::string ConfigContainer::jsonFile() const
{
    return mJsonFile;
}

void ConfigContainer::setJsonFile(const std::string &jsonFile)
{
    mJsonFile = jsonFile;
}

Json::Value ConfigContainer::getConfigFile()
{
    if(!mJsonFile.empty()) {
        return readJSON(mJsonFile);
    }
    return Json::Value();
}

bool ConfigContainer::updateConfigFile(const Json::Value &newConfig) const
{
    if(!newConfig.empty()) {
        return writeJSON(newConfig);
    }
    return false;
}


std::string ConfigContainer::identifier() const
{
    return mIdentifier;
}


std::string ConfigContainer::usage() const
{
    return mUsageText;
}


std::string ConfigContainer::help() const
{
    return mHelpText;
}


}
