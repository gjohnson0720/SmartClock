#pragma once 

#include <vector>
#include <istream>
#include <string>
#include "ForecastDayData.h"

class ForecastParserBase
{
public:
    ForecastParserBase() = default;
    virtual ~ForecastParserBase() = default;

    virtual std::string GetURL() const = 0;
    virtual std::vector<ForecastDayData> Parse(std::istream& stream) const = 0;
    virtual std::vector<ForecastDayData> Parse(const std::string& str) const = 0;
};