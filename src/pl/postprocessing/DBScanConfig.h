#pragma once

#include "../pipeline/ConfigContainer.h"
#include <opencv2/core/core.hpp>

namespace pl {


class DBScanConfig : public ConfigContainer
{
public:
    DBScanConfig(const std::string &identifier);

    virtual ~DBScanConfig();

    int minPoints() const;
    void setMinPoints(int minPoints);

    double neighborhoodSize() const;
    void setNeighborhoodSize(double neighborhoodSize);

    virtual std::string toString() const override;
    virtual bool fromJSON(std::string &file) override;

private:
    int mMinPoints;
    double mNeighborhoodSize;
};


}
