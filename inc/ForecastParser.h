#pragma once 

#include <vector>
#include <istream>
#include <string>
#include "ForecastDayData.h"

class ForecastParser
{
public:
    ForecastParser(){}
    ~ForecastParser(){}

    static std::vector<ForecastDayData> Parse(std::istream& stream);
    static std::vector<ForecastDayData> Parse(const std::string& str);
};