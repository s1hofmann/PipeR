#pragma once

#include "../pipeline/ConfigContainer.h"
#include <opencv2/core/core.hpp>

namespace pl {


class DBScanConfig : public ConfigContainer
{
public:
    DBScanConfig(const std::string &identifier);

    virtual ~DBScanConfig();

    int32_t minPoints() const;
    bool setMinPoints(int32_t minPoints);

    double neighborhoodSize() const;
    bool setNeighborhoodSize(double neighborhoodSize);

    virtual std::string toString() const override;
    virtual bool fromJSON(std::string &file) override;

private:
    int32_t mMinPoints;
    double mNeighborhoodSize;
};


}
