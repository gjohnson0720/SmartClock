#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <functional>
#include "TimeUtils.h"

struct CurlThreadConfig
{
    std::string url;
    int fetchEverySecs;
    std::function<void(std::string)> urlContentsCallback;
    std::string outputFolder;
    std::string fileExtension;

    CurlThreadConfig(std::string url_, int fetchEverySecs_, std::string outputFolder_, 
        std::string fileExtension_, std::function<void(std::string)> cb_) 
        : url(url_), fetchEverySecs(fetchEverySecs_), urlContentsCallback(cb_), 
            outputFolder(outputFolder_), fileExtension(fileExtension_)
    {
        SetNextTime();
    }

    std::chrono::system_clock::duration GetTimeDelta() const
    {
        return timeToFetchUrlContents - std::chrono::system_clock::now();
    }

    void SetNextTime()
    {
        timeToFetchUrlContents = std::chrono::system_clock::now() + std::chrono::seconds(fetchEverySecs);
    }

private:
    std::chrono::system_clock::time_point timeToFetchUrlContents;
};
