#pragma once

#include <string>

struct ForecastDayData
{
    time_t DateTime;
    std::string Day;
    int MinTemp;
    int MaxTemp;
    int Icon;
    std::string Description;
};
