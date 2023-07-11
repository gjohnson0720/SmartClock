#pragma once

#include <chrono>

class TimeUtils
{
public:
    static std::chrono::system_clock::time_point CreateTime(int hour, int minute, int second);
    static std::chrono::system_clock::time_point CreateTime();
};