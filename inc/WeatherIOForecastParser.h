#pragma once 

#include "ForecastParserBase.h"

class WeatherIOForecastParser : public ForecastParserBase
{
public:
    std::string GetURL() const;
    std::vector<ForecastDayData> Parse(std::istream& stream) const;
    std::vector<ForecastDayData> Parse(const std::string& str) const;
};