#pragma once

#include <thread>
#include <list>
#include "CurlThreadConfig.h"
#include <chrono>

class CurlThread
{
public:  
    CurlThread();
    ~CurlThread();

    void AddUrlToRetrieve(const CurlThreadConfig& config);
    void Start();

private:
    std::thread thread;
    std::list<CurlThreadConfig> configs;

    void Run();
    CurlThreadConfig* FindNextWaitTime();
    std::string RetrieveUrl(const std::string& url);
    std::string RetrieveUrlFromCurl(const std::string& url);
    std::string RetrieveUrlFromFile(const std::string& url);
    std::string GetFilePath(const CurlThreadConfig& config);
    void RetrieveUrl(const CurlThreadConfig& config);
};