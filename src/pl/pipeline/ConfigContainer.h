//
// Created by Simon Hofmann on 19.11.15.
//


#pragma once

#include <string>
#include "globals.h"
#include "../core/utils/json/json.h"
#include <fstream>

namespace pl {

/**
 * Base class for each steps config class.
 * Every config class has te be derived from
 */
class ConfigContainer {
public:
    /**
     * @brief usage
     * @return
     */
    std::string usage() const;

    /**
     * @brief help
     * @return
     */
    std::string help() const;

    /**
     * @brief identifier
     * @return
     */
    std::string identifier() const;

    /**
     * @brief toString
     * @return
     */
    virtual std::string toString() const = 0;

    /**
     * @brief fromJSON
     * @param file
     * @return
     */
    virtual bool fromJSON(std::string &file) = 0;

protected:
    /**
     * @brief ConfigContainer
     * @param usage
     * @param help
     */
    ConfigContainer(const std::string &identifier,
                    const std::string &usage = "No usage text provided, I'm sorry.",
                    const std::string &help = "No help text provided, I'm sorry.");

    Json::Value readJSON(const std::string &file);

    /**
     * @brief ~ConfigContainer
     */
    virtual ~ConfigContainer();

private:
    /**
     * @brief mUsageText
     */
    std::string mUsageText;

    /**
     * @brief mHelpText
     */
    std::string mHelpText;

    /**
     * @brief mIdentifier
     */
    std::string mIdentifier;
};


}
