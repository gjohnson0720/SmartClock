#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <functional>
#include "TimeUtils.h"

struct CurlThreadConfig
{
    std::string url;
    std::chrono::system_clock::time_point timeToFetchUrlContents;
    std::function<void(std::string)> urlContentsCallback;

    CurlThreadConfig(std::string url_, int hour_, int minute_, int second_, std::function<void(std::string)> cb_) : url(url_), urlContentsCallback(cb_)
    {
        timeToFetchUrlContents = TimeUtils::CreateTime(hour_, minute_, second_);
    }

    std::chrono::system_clock::duration GetTimeDelta() const
    {
        auto now = TimeUtils::CreateTime();
        return timeToFetchUrlContents - now;
    }
};
