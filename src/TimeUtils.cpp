#include "TimeUtils.h"

std::chrono::system_clock::time_point TimeUtils::CreateTime(int hour, int minute, int second)
{
    tm t = tm();
    t.tm_hour = hour;
    t.tm_min = minute;
    t.tm_sec = second;
    t.tm_year = 1970 - 1900;
    t.tm_mon = 0;
    t.tm_mday = 1;
    time_t tt = mktime(&t);
    return std::chrono::system_clock::from_time_t(tt);
}

std::chrono::system_clock::time_point TimeUtils::CreateTime()
{
    auto now = std::chrono::system_clock::now();
    time_t tnow = std::chrono::system_clock::to_time_t(now);
    tm *t = std::localtime(&tnow);
    return CreateTime(t->tm_hour, t->tm_min, t->tm_sec);
}