#pragma once

#include "../pipeline/ConfigContainer.h"

#include <sstream>
#include <iostream>

namespace pl {


class PCAConfig : public ConfigContainer
{
public:
    PCAConfig(const std::string &identifier,
              const int components,
              const double epsilon = 0.001,
              const bool whiten = true,
              const std::string &path = ".");

    int getComponents() const;

    double getEpsilon() const;

    bool getWhitening() const;

    std::string getPath() const;

    virtual std::string toString() const;

private:
    int mComponents;

    double mEpsilon;

    bool mWhitening;

    std::string mPath;
};


}
