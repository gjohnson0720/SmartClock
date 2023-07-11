#include "ForecastParser.h"
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

static void print_date(time_t time);
static std::string get_day_of_week(time_t time);

std::vector<ForecastDayData> ForecastParser::Parse(std::istream& stream)
{
    json data = json::parse(stream);
    auto& dailyForecasts = data["DailyForecasts"];
    std::vector<ForecastDayData> days(dailyForecasts.size());

    int index = 0;
    for (auto it = dailyForecasts.begin(); it != dailyForecasts.end(); ++it)
    {
        auto& date = it.value()["EpochDate"];
        print_date(date);
        auto& temp = it.value()["Temperature"];
        auto& min = temp["Minimum"];
        auto& minValue = min["Value"];
        auto& max = temp["Maximum"];
        auto& maxValue = max["Value"];
        std::cout << "Min temp " << minValue << " max " << maxValue << std::endl;
        auto& day = it.value()["Day"];
        auto& icon = day["Icon"];
        auto& phrase = day["IconPhrase"];
        days[index].MinTemp = minValue;
        days[index].MaxTemp = maxValue;
        days[index].DateTime = date;
        days[index].Day = get_day_of_week(days[index].DateTime);
        days[index].Icon = icon;
        days[index].Description = phrase;
        ++index;
        // std::cout << it.value() << std::endl; //" : " << it.value() << "\n";
    }
    return days;
}


void print_date(time_t time)
{
	std::tm * ptm = std::localtime(&time);
	char buffer[32];
	// Format: Mo, 15.06.2009 20:20:00
	std::strftime(buffer, 32, "%a, %d.%m.%Y", ptm);
	std::cout << "Date: " << buffer << std::endl;
}


void print_time(time_t time)
{
	std::tm * ptm = std::localtime(&time);
	char buffer[32];
	// Format: Mo, 15.06.2009 20:20:00
	std::strftime(buffer, 32, "%a, %d.%m.%Y %H:%M:%S", ptm);
	std::cout << "Time: " << buffer << std::endl;
}

std::string get_day_of_week(time_t time)
{
	std::tm * ptm = std::localtime(&time);
	char buffer[32];
	// Format: Mo, 15.06.2009 20:20:00
	std::strftime(buffer, 32, "%a", ptm);
	return buffer;
}
