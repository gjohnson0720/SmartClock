#pragma once

#include <string>

struct ForecastDayData
{
    time_t DateTime;
    std::string Day;
    int MinTemp;
    int MaxTemp;
    std::string Icon;
    std::string Description;

    bool operator==(const ForecastDayData& other) const
    {
        return DateTime == other.DateTime && Day == other.Day && 
                MinTemp == other.MinTemp && MaxTemp == other.MaxTemp &&
                Icon == other.Icon && Description == other.Description;
    }
};
