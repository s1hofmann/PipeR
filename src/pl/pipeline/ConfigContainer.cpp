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
        mHelpText(help)
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
        return root;
    } else {
        return Json::Value();
    }
}


ConfigContainer::~ConfigContainer()
{

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
