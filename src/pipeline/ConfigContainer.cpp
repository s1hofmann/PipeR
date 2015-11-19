//
// Created by Simon Hofmann on 19.11.15.
//

#include "ConfigContainer.h"


namespace pipe {


ConfigContainer::ConfigContainer(const std::string &usage,
                                 const std::string &help)
    :
        usageText(usage),
        helpText(help)
{

}


ConfigContainer::~ConfigContainer()
{

}


std::string ConfigContainer::usage() const
{
    return usageText;
}


std::string ConfigContainer::help() const
{
    return helpText;
}


}
