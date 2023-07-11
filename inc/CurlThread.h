#pragma once

#include <thread>
#include <vector>
#include "CurlThreadConfig.h"
#include <chrono>

class CurlThread
{
public:  
    CurlThread(const std::vector<CurlThreadConfig>& config);
    ~CurlThread();

    void Start();

private:
    std::thread thread;
    std::vector<CurlThreadConfig> configs;

    void Run();
    const CurlThreadConfig* FindNextWaitTime();
    std::string RetrieveUrl(std::string url);
    std::string RetrieveUtlFromCurl(std::string url);
    std::string RetrieveUtlFromFile(std::string url);
};