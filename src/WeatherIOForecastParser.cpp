#include "WeatherIOForecastParser.h"
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

static void print_date(time_t time);
static void print_time(time_t time);
static std::string get_day_of_week(time_t time);
static std::vector<ForecastDayData> Parse(json& json);

std::string WeatherIOForecastParser::GetURL() const 
{
    return "https://api.weatherbit.io/v2.0/forecast/daily?lat=33.368431650949205&lon=-117.24978188040555&city=Fallbrook%2CCA&postal_code=92028&country=United%20States&days=5&units=I&key=860d2a96df0c47778da57b0a85bd8b69";
}

std::vector<ForecastDayData> WeatherIOForecastParser::Parse(std::istream& stream) const
{
    json data = json::parse(stream);
    return ::Parse(data);
}

std::vector<ForecastDayData> WeatherIOForecastParser::Parse(const std::string& str) const
{
    json data = json::parse(str);
    return ::Parse(data);
}

std::vector<ForecastDayData> Parse(json& json)
{
    auto& dailyForecasts = json["data"];
    std::vector<ForecastDayData> days(dailyForecasts.size());

    int index = 0;
    for (auto it = dailyForecasts.begin(); it != dailyForecasts.end(); ++it)
    {
        auto& date = it.value()["ts"];
        print_date(date);
        auto& minValue = it.value()["min_temp"];
        auto& maxValue = it.value()["max_temp"];
        std::cout << "Min temp " << minValue << " max " << maxValue << std::endl;
        auto& day = it.value()["weather"];
        auto& icon = day["code"];
        auto& phrase = day["description"];
        days[index].MinTemp = minValue;
        days[index].MaxTemp = maxValue;
        days[index].DateTime = date;
        days[index].Day = get_day_of_week(days[index].DateTime);
        std::stringstream s;
        s << "./images/" << icon << ".png";
        days[index].Icon = s.str();
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
