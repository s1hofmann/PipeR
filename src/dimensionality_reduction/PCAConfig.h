#pragma once

#include "../pipeline/ConfigContainer.h"

namespace pipe {


class PCAConfig : public ConfigContainer
{
public:
    PCAConfig(int components, double epsilon, bool whiten);

    int getComponents();

    double getEpsilon();

    bool getWhitening();

    virtual std::string toString();

private:
    int mComponents;

    double mEpsilon;

    bool mWhitening;
};


}
