//
// Created by Simon Hofmann on 19.11.15.
//

#include "ConfigContainer.h"


namespace pl {


ConfigContainer::ConfigContainer(const std::string &usage,
                                 const std::string &help)
    :
        mUsageText(usage),
        mHelpText(help)
{

}


ConfigContainer::~ConfigContainer()
{

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
