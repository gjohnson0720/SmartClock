#pragma once 

#include <vector>
#include <istream>
#include "ForecastDayData.h"

class ForecastParser
{
public:
    ForecastParser(){}
    ~ForecastParser(){}

    static std::vector<ForecastDayData> Parse(std::istream& stream);
};